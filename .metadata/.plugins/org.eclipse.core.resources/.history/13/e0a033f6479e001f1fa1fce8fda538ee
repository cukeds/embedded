#include <bsp_hcsr501.h>


static bool allow_readings = false;

inline void BSP_HCSR501_Init(){
	allow_readings = true;
}

uint8_t BSP_HCSR501_Read(){
	if(!allow_readings){
		return HCSR501_INITIALIZING;
	}
	return HAL_GPIO_ReadPin(HCSR501_PORT, HCSR501_PIN);
}

bool BSP_HCSR501_Ready(){
	return BSP_HCSR501_Read() == HCSR501_INITIALIZING;
}

