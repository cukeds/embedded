
#include "bsp_encoder.h"

static uint32_t counter = 0;
static int16_t previous_count = 0;
static int16_t bsp_count = 0;
static int16_t direction = 0;
static int16_t speed = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	counter = __HAL_TIM_GET_COUNTER(htim);
	bsp_count = (int16_t) counter;

	if(bsp_count > previous_count){
		direction = ENCODER_DIRECTION_RIGHT;
	}
	else if(bsp_count < previous_count){
		direction = ENCODER_DIRECTION_LEFT;
	}
	previous_count = bsp_count;
}

void BSP_ENCODER_Init(){
	HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL); // For 2 channels
}

inline int16_t BSP_ENCODER_GetCount(){
	return bsp_count;
}
inline int16_t BSP_ENCODER_GetSpeed(){
	static int16_t speed_count = 0;
	if(GetMS() % 500 == 0){
		speed = (bsp_count - speed_count)*2; // speed in counts/sec
		speed_count = bsp_count;
	}
	return speed;
}
inline int16_t BSP_ENCODER_GetDirection(){
	return direction;
}
inline int16_t BSP_ENCODER_GetSwitch(){
	return HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_PIN);
}
void BSP_ENCODER_WriteSpeed(int16_t _speed){
	speed = _speed;
}
