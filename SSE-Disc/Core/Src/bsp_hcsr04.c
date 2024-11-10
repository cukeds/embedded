#include "bsp_hcsr04.h"


static uint8_t distance;


uint8_t HAL_HCSR04_GetDistance(){
	return distance;
}

void HAL_HCSR04_Callback(TIM_HandleTypeDef *htim){
	static bool Is_First_Captured = false;
	static uint32_t IC_Val1 = 0;
	static uint32_t IC_Val2 = 0;
	static uint32_t Difference = 0;
	if (!Is_First_Captured) // if the first value is not captured
	{
		IC_Val1 = HAL_TIM_ReadCapturedValue(htim, HCSR04_TIM_CHANNEL); // read the first value
		Is_First_Captured = 1;  // set the first captured as true
		// Now change the polarity to falling edge
		__HAL_TIM_SET_CAPTUREPOLARITY(htim, HCSR04_TIM_CHANNEL, TIM_INPUTCHANNELPOLARITY_FALLING);
	}

	else if (Is_First_Captured)   // if the first is already captured
	{
		IC_Val2 = HAL_TIM_ReadCapturedValue(htim, HCSR04_TIM_CHANNEL);  // read second value
		__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

		if (IC_Val2 > IC_Val1)
		{
			Difference = IC_Val2-IC_Val1;
		}

		else if (IC_Val1 > IC_Val2)
		{
			Difference = (0xffff - IC_Val1) + IC_Val2;
		}

		distance = Difference * .034/2;
		Is_First_Captured = false; // set it back to false

		// set polarity to rising edge
		__HAL_TIM_SET_CAPTUREPOLARITY(htim, HCSR04_TIM_CHANNEL, TIM_INPUTCHANNELPOLARITY_RISING);
		__HAL_TIM_DISABLE_IT(&HCSR04_TIM_INSTANCE, TIM_IT_CC1);

	}
}

void HAL_HCSR04_Trigger ()
{
	HAL_GPIO_WritePin(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	DELAY_US(10);  // wait for 10 us
	HAL_GPIO_WritePin(HCSR04_TRIG_PORT, HCSR04_TRIG_PIN, GPIO_PIN_RESET);  // pull the TRIG pin low

	__HAL_TIM_ENABLE_IT(&HCSR04_TIM_INSTANCE, TIM_IT_CC1);
}



PresenceSensor_Status BSP_HCSR04_GetPresence(uint8_t cut){
	if(distance >= cut){
		return NoPresence;
	}else if(distance < cut && distance != 0){
		return Presence;
	}
	return Error;
}

// Interrupts
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &HCSR04_TIM_INSTANCE)  // if the interrupt source is channel1
	{
		HAL_HCSR04_Callback(htim);
	}
}


