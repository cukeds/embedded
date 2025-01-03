#include "app.h"
#include <stdio.h>
static APP_DATA_Struct app_data = {
	    .user = NULL,
	    .rx_data = {0,},
	    .tx_data = {0,},
		.motion_status = False,
		.motion_activity = 0,
	};

static APP_FLAGS_Struct app_flags = {
		.waiting_for_user = True,
		.is_card_cooldown = False,
	    .message_received = False,
	    .message_to_send = False,
		.update_motion = False,
		.button_pressed = False,
};


static APP_USER_Struct app_users[2] = {
    {.serial_number = 0xD3, .name = "Juan Degiovanni", .work_station = 1,.present = False, .total_time_inactive = 0, .total_time_active =0, .longest_time_inactive = 0},
    {.serial_number = 0xAA, .name = "Fran Gomez", .work_station = 2,.present = False, .total_time_inactive = 0, .total_time_active =0, .longest_time_inactive = 0}
};


uint8_t rfidSymbol[8] = {
    0b00000,  // BXXXB
    0b01010,  // XBBBX
    0b10001,  // BXXXB
    0b10101,  // XBBBX
    0b10101,  // BXXXB
    0b10001,  // XBBBX
    0b01010,  // BBXBB
    0b00000   // BBXBB
};

uint8_t motionSymbol[8] = {
    0b00010,  //     *
    0b00101,  //    * *
    0b10010,  //     *
    0b01100,  //   ***
    0b10100,  //     **
    0b00110,  //    * *
    0b01010,  //    *   *
    0b10001   //  *     *
};

uint8_t rfidSymbol_idx;
uint8_t motionSymbol_idx;

void app_init(){
	rfidSymbol_idx = BSP_LCD_ADD_STATUS(rfidSymbol, True);
	motionSymbol_idx = BSP_LCD_ADD_STATUS(motionSymbol, False);

	BSP_LCD_DISPLAY_STATUS();
}

void app(){
	if(app_flags.message_to_send){
		APP_SEND_MESSAGE();
	}
	if(app_flags.message_received){
		APP_MESSAGE_RECEIVED();
		APP_UPDATE_WORKSTATION();

	}
	if(app_flags.waiting_for_user){
		static uint8_t sNum = 1;
		if(!app_flags.is_card_cooldown){
			BSP_RC522_GetSerialNumber(&sNum);
		}else{
			sNum = 1;
			return;
		}
		if(sNum != 1){
			if(!APP_GET_USER_BY_SERIAL_NUMBER(sNum, &app_data.user)){
				return;
			}
			TOGGLE_FIELD(app_data.user, present);
			if(app_data.user->present){
				BSP_LCD_SendMessage("Hola", 0, 0, True);
				BSP_LCD_SendMessage(app_data.user->name, 0, 1, False);
				APP_SEND_COMMAND_TO_WORK_STATION(app_data.user->work_station, TURN_ON_WS_COMMAND);
			}else{
				BSP_LCD_SendMessage("Chau", 0, 0, True);
				BSP_LCD_SendMessage(app_data.user->name, 0, 1, False);
				APP_SEND_COMMAND_TO_WORK_STATION(app_data.user->work_station, TURN_OFF_WS_COMMAND);
			}
			APP_SETFLAG(IS_CARD_COOLDOWN, True);
			BSP_StartCardCooldown();
			BSP_LCD_UPDATE_STATUS(rfidSymbol_idx, False);
		}
	}

	if(app_flags.update_motion){
		BSP_LCD_UPDATE_STATUS(motionSymbol_idx, app_data.motion_status);
		APP_SETFLAG(UPDATE_MOTION, False);
	}

}

void APP_MESSAGE_RECEIVED(){
	BSP_RF_ReadData(app_data.rx_data);
	APP_SETFLAG(MESSAGE_RECEIVED, False);
}

void APP_SEND_MESSAGE(){
	BSP_RF_Sending();
	BSP_RF_SendMessage(app_data.tx_data);
	APP_SETFLAG(MESSAGE_TO_SEND, False);
}

void APP_SET_MESSAGE_TO_SEND(uint8_t message[NRF24L01P_PAYLOAD_LENGTH]){
	memcpy(app_data.tx_data, message, NRF24L01P_PAYLOAD_LENGTH);
}

void APP_SEND_COMMAND_TO_WORK_STATION(uint8_t ws, uint8_t command[NRF24L01P_PAYLOAD_LENGTH-1]){
	uint8_t message[NRF24L01P_PAYLOAD_LENGTH];
	message[0] = ws;
	for(int i = 1; i < NRF24L01P_PAYLOAD_LENGTH; i++){
		message[i] = command[i-1];
	}
	APP_SET_MESSAGE_TO_SEND(message);
	APP_SETFLAG(MESSAGE_TO_SEND, True);
}

void APP_SETFLAG(APP_FLAGS_Enum flag, boolean value){
    boolean* targetFlag = nullptr;

    switch(flag){
        case MESSAGE_RECEIVED:   targetFlag = &app_flags.message_received; break;
        case MESSAGE_TO_SEND:    targetFlag = &app_flags.message_to_send; break;
        case WAITING_FOR_USER:   targetFlag = &app_flags.waiting_for_user; break;
        case IS_CARD_COOLDOWN:   targetFlag = &app_flags.is_card_cooldown; break;
        case UPDATE_MOTION:      targetFlag = &app_flags.update_motion; break;
        case BUTTON_PRESSED:     targetFlag = &app_flags.button_pressed; break;
        default: return; // Return early if flag is invalid
    }

    if (targetFlag) {
        *targetFlag = value;
    }
}


boolean APP_GET_USER_BY_SERIAL_NUMBER(uint8_t sNum, APP_USER_Struct **user){
	for(int i = 0; i < MAX_USER_AMOUNT; i++){
		if(app_users[i].serial_number == sNum){
			*user = &app_users[i];
			return True;
		}
	}
	return False;
}

boolean APP_GET_USER_BY_WORKSTATION(uint8_t ws, APP_USER_Struct **user){
	for(int i = 0; i < MAX_USER_AMOUNT; i++){
		if(app_users[i].work_station == ws){
			*user = &app_users[i];
			return True;
		}
	}
	return False;
}

void APP_UPDATE_WORKSTATION(){
	uint8_t ws = app_data.rx_data[0];
	if(!APP_GET_USER_BY_WORKSTATION(ws, &app_data.user)){
		return;
	}
	static uint16_t current_time_inactive = 0;
	current_time_inactive = app_data.rx_data[1] << 8 | app_data.rx_data[2];
	app_data.user->total_time_inactive += current_time_inactive;

    static char puesto[16];  // Adjust size based on your expected message length
    static char inactividad[16];
	sprintf(puesto, "Puesto %d", ws);
	sprintf(inactividad, "Inactividad:%d m", (uint8_t)current_time_inactive);
	BSP_LCD_SendMessage(puesto, 0, 0, True);
	BSP_LCD_SendMessage(inactividad, 0, 1, False);

	if((current_time_inactive) >= INACTIVITY_MAX_MINUTES){
		APP_SEND_COMMAND_TO_WORK_STATION(app_data.user->work_station, TURN_OFF_WS_COMMAND);
		SET_FIELD(app_data.user, present, False);
		app_data.rx_data[0] = 0;
	}
}


inline APP_DATA_Struct* GET_APP_DATA(){
	return &app_data;
}
