#pragma once

#include <stdbool.h>
#include "defines.h"
#include "Util.h"

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef HCSR04_TIM_INSTANCE;


typedef enum{
	Presence,
	NoPresence,
	Error
} PresenceSensor_Status;

void trigger_exti8_swinterrupt();
void HAL_HCSR04_Callback(TIM_HandleTypeDef *htim);
PresenceSensor_Status BSP_HCSR04_GetPresence(uint8_t cut);
uint8_t HAL_HCSR04_GetDistance();
