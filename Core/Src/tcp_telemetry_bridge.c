#include "tcp_telemetry_bridge.h"
#include "lwip/tcp.h"
#include "lwip.h"

static struct tcp_pcb *g_tcp_server_pcb = NULL;
static struct tcp_pcb *g_client_pcb = NULL;

static err_t tcp_bridge_accept_cb(void *arg, struct tcp_pcb *newpcb, err_t err);
static err_t tcp_bridge_recv_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void  tcp_bridge_err_cb(void *arg, err_t err);

void TCP_Bridge_Init(uint16_t port)
{
    g_tcp_server_pcb = tcp_new();
    if (g_tcp_server_pcb != NULL)
    {
        err_t err = tcp_bind(g_tcp_server_pcb, IP_ADDR_ANY, port);
        if (err == ERR_OK)
        {
            g_tcp_server_pcb = tcp_listen(g_tcp_server_pcb);
            tcp_accept(g_tcp_server_pcb, tcp_bridge_accept_cb);
        }
    }
}

static err_t tcp_bridge_accept_cb(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    LWIP_UNUSED_ARG(arg);
    LWIP_UNUSED_ARG(err);
    g_client_pcb = newpcb;
    tcp_arg(newpcb, NULL);
    tcp_recv(newpcb, tcp_bridge_recv_cb);
    tcp_err(newpcb, tcp_bridge_err_cb);
    return ERR_OK;
}

static err_t tcp_bridge_recv_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (p == NULL)
    {
        tcp_close(tpcb);
        if (g_client_pcb == tpcb) g_client_pcb = NULL;
        return ERR_OK;
    }
    tcp_recved(tpcb, p->tot_len);
    pbuf_free(p);
    return ERR_OK;
}

static void tcp_bridge_err_cb(void *arg, err_t err)
{
    LWIP_UNUSED_ARG(arg);
    LWIP_UNUSED_ARG(err);
    g_client_pcb = NULL;
}

void TCP_Bridge_Process(void)
{
    MX_LWIP_Process();
}

void TCP_Bridge_Send(const uint8_t *data, uint16_t len)
{
    if (g_client_pcb != NULL && data != NULL && len > 0)
    {
        if (tcp_sndbuf(g_client_pcb) >= len)
        {
            tcp_write(g_client_pcb, data, len, TCP_WRITE_FLAG_COPY);
            tcp_output(g_client_pcb);
        }
    }
}

bool TCP_Bridge_IsConnected(void)
{
    return (g_client_pcb != NULL);
}
