#ifndef BSP_H
#define BSP_H

#include "stm32f1xx_hal.h"
#include "app_defines.h"

// Starts the cooldown timer
void BSP_StartCardCooldown(void);
void BSP_Countdown(void);
uint32_t BSP_GetCounter();

#endif // BSP_H
