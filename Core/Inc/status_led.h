#ifndef INC_STATUS_LED_H_
#define INC_STATUS_LED_H_

#include "main.h"

void StatusLED_Init(void);
void StatusLED_UpdateNetworkStatus(void);
void StatusLED_ToggleActivity(void);

#endif /* INC_STATUS_LED_H_ */
