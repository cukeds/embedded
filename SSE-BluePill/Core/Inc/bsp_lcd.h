#ifndef BSP_LCD_H
#define BSP_LCD_H
#include "../ECUAL/I2C_LCD/I2C_LCD.h"
#include <string.h>
#include "defines.h"
#include "cmsis_gcc.h"

typedef struct {
	boolean (*condition)();
	uint8_t setup_time;
	uint8_t* seconds;
} BSP_LCD_SetupParams_TypeDef;


void BSP_LCD_Init(BSP_LCD_SetupParams_TypeDef *params);


void BSP_LCD_Clear();

void BSP_LCD_SetCursor(uint8_t col, uint8_t row);

void BSP_LCD_SendMessage(char* message, uint8_t col, uint8_t row, boolean clear);
int BSP_LCD_ADD_STATUS(uint8_t symbol[8], boolean default_value);

void BSP_LCD_UPDATE_STATUS(uint8_t idx, boolean value);

void BSP_LCD_DISPLAY_STATUS();


#endif
