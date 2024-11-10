#include "bsp_rc522.h"
#include <string.h>

void BSP_RC522_Init(){
	 MFRC522_Init();
}

uint8_t BSP_RC522_GetSerialNumber(uint8_t* sNum){
	uint8_t status;
	uint8_t str[MAX_LEN];
	status = MFRC522_Request(PICC_REQALL, str);
	status = MFRC522_Anticoll(str);
	if(status == MI_OK){
		memcpy(sNum, str, 5);
	}
	return status;
}

