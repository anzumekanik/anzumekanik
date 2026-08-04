#include "status_led.h"
#include "tcp_telemetry_bridge.h"

void StatusLED_Init(void)
{
    // Nucleo kartındaki varsayılan LED durumları
}

void StatusLED_UpdateNetworkStatus(void)
{
    // TCP istemcisi bağlıysa Yeşil LED (PB0) yanar
    if (TCP_Bridge_IsConnected())
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    }
}

void StatusLED_ToggleActivity(void)
{
    // Paket transferinde Mavi LED (PB7) çakar
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
}
