#include <bsp_hcsr501.h>


static boolean allow_readings = False;

inline void BSP_HCSR501_Init(){
	allow_readings = True;
}

inline void BSP_HCSR501_OffTime(){
	allow_readings = False;
}

uint8_t BSP_HCSR501_Read(){
	if(!allow_readings){
		return HCSR501_INITIALIZING;
	}
	return HAL_GPIO_ReadPin(HCSR501_PORT, HCSR501_PIN);
}

boolean BSP_HCSR501_Ready(){
	return allow_readings;
}

