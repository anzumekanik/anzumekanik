#ifndef INC_TELEMETRY_PARSER_H_
#define INC_TELEMETRY_PARSER_H_

#include "main.h"

#define RX_BUFFER_SIZE 256

extern uint8_t  g_rx_buffer[RX_BUFFER_SIZE];
extern volatile uint16_t g_rx_index;

void Telemetry_Init(UART_HandleTypeDef *huart);
void Telemetry_OnUartRxByte(UART_HandleTypeDef *huart);
void Telemetry_OnUartError(UART_HandleTypeDef *huart);

#endif /* INC_TELEMETRY_PARSER_H_ */
