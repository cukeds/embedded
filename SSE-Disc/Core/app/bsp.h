#ifndef BSP_H
#define BSP_H

#include "stm32f4xx_hal.h"
#include "bsp_hcsr04.h"
#include "bsp_relay.h"

// Function prototypes
void BSP_START_PRESENCE_COUNTER(void);
void BSP_STOP_PRESENCE_COUNTER(void);

#endif // BSP_H
