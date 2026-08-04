#ifndef INC_TCP_TELEMETRY_BRIDGE_H_
#define INC_TCP_TELEMETRY_BRIDGE_H_

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void TCP_Bridge_Init(uint16_t port);
void TCP_Bridge_Process(void);
void TCP_Bridge_Send(const uint8_t *data, uint16_t len);
bool TCP_Bridge_IsConnected(void);

#endif /* INC_TCP_TELEMETRY_BRIDGE_H_ */
