#ifndef BSP_HCSR501_H
#define BSP_HCSR501_H

#include "defines.h"
#include "stm32f1xx_hal.h"
#include <stdbool.h>

/* Initializes the module. It waits 1 minute for the device to be ready for use before allowing readings*/
void BSP_HCSR501_Init();

uint8_t BSP_HCSR501_Read();
bool BSP_HCSR501_Ready();

#endif