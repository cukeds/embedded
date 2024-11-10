#include "bsp_lcd.h"

extern uint8_t motion[5];

void Initializing(BSP_LCD_SetupParams_TypeDef *params){

	char time[5];
	BSP_LCD_SendMessage("Initializing: ", 0, 0, true);
 	itoa(params->setup_time - *(params->seconds), time, 10);
	BSP_LCD_SendMessage(time, 0, 1, false);
}

void BSP_LCD_Init(BSP_LCD_SetupParams_TypeDef *params){
	I2C_LCD_Init(LCD);
	  while(params->condition()){
		  Initializing(params);
		  HAL_Delay(1000);
	  }
}


void BSP_LCD_Clear(){
	I2C_LCD_Clear(LCD);
}

void BSP_LCD_SetCursor(uint8_t col, uint8_t row){
 	I2C_LCD_SetCursor(LCD, col, row);
}

void BSP_LCD_SendMessage(char* message, uint8_t col, uint8_t row, bool clear){
	if(clear){
		BSP_LCD_Clear();
	}
	BSP_LCD_SetCursor(col, row);
 	I2C_LCD_WriteString(LCD, message);
}




