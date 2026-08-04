#include "telemetry_parser.h"
#include "tcp_telemetry_bridge.h"

uint8_t g_rx_buffer[RX_BUFFER_SIZE];
volatile uint16_t g_rx_index = 0;
static uint8_t g_rx_byte = 0;
static UART_HandleTypeDef *g_huart = NULL;

void Telemetry_Init(UART_HandleTypeDef *huart)
{
    g_huart = huart;
    HAL_UART_Receive_IT(g_huart, &g_rx_byte, 1);
}

void Telemetry_OnUartRxByte(UART_HandleTypeDef *huart)
{
    if (huart->Instance == g_huart->Instance)
    {
        // Live Expressions izlemesi için tampona kaydet
        g_rx_buffer[g_rx_index] = g_rx_byte;
        g_rx_index = (g_rx_index + 1) % RX_BUFFER_SIZE;

        // Gelen veriyi anında TCP Client'a fırlat
        TCP_Bridge_Send(&g_rx_byte, 1);

        // Sonraki bayt için kesmeyi yenile
        HAL_UART_Receive_IT(g_huart, &g_rx_byte, 1);
    }
}

void Telemetry_OnUartError(UART_HandleTypeDef *huart)
{
    if (huart->Instance == g_huart->Instance)
    {
        // Overrun vs. hatalarında kesmeyi tekrar kur
        HAL_UART_Receive_IT(g_huart, &g_rx_byte, 1);
    }
}
