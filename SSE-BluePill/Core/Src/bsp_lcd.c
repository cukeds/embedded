#include "bsp_lcd.h"



static boolean status[3];
static int status_index = 0;

void Initializing(BSP_LCD_SetupParams_TypeDef *params){
	char time[5];
	BSP_LCD_SendMessage("Initializing: ", 0, 0, True);
 	itoa(params->setup_time - *(params->seconds), time, 10);
	BSP_LCD_SendMessage(time, 0, 1, False);
}

void BSP_LCD_Init(BSP_LCD_SetupParams_TypeDef *params){
	I2C_LCD_Init(LCD);
	  while(params->condition()){
		  Initializing(params);
	  }
}


void BSP_LCD_Clear(){
	I2C_LCD_Clear(LCD);
}

void BSP_LCD_SetCursor(uint8_t col, uint8_t row){
 	I2C_LCD_SetCursor(LCD, col, row);
}

void BSP_LCD_SendMessage(char* message, uint8_t col, uint8_t row, boolean clear){
	if(clear){
		BSP_LCD_Clear();
	}
	BSP_LCD_SetCursor(col, row);
 	I2C_LCD_WriteString(LCD, message);
	BSP_LCD_DISPLAY_STATUS();
}

int BSP_LCD_ADD_STATUS(uint8_t symbol[8], boolean default_value){
	I2C_LCD_CreateCustomChar(0, status_index, symbol);
	status[status_index] = default_value;
	return status_index++;
}

void BSP_LCD_UPDATE_STATUS(uint8_t idx, boolean value){
	status[idx] = value;
	BSP_LCD_DISPLAY_STATUS();
}

void BSP_LCD_DISPLAY_STATUS(){
	for(int i = 0; i < status_index; i++){
		if(status[i]){
			I2C_LCD_SetCursor(LCD, 16-1 - (i*2), 0);
			I2C_LCD_PrintCustomChar(LCD, i);
		}else{
			I2C_LCD_SetCursor(LCD, 16-1 - (i*2), 0);
			I2C_LCD_WriteChar(LCD, ' ');
		}
	}
}



