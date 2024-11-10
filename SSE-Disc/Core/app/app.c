#include "app.h"

APP_DATA_Struct app_data = {
	    .noPresenceSeconds = 0,
		.stationStatus = StationOff,
	    .rx_data = {0,},
	    .tx_data = {0,},
	};

static APP_FLAGS_Struct app_flags;
void app(){
	if(app_flags.message_received){
		APP_MESSAGE_RECEIVED();
		APP_PARSE_COMMAND();
	}
	if(app_flags.message_to_send){
		APP_SEND_MESSAGE();
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

void APP_SET_MESSAGE_RECEIVED(uint8_t message[NRF24L01P_PAYLOAD_LENGTH]){
	memcpy(app_data.rx_data, message, NRF24L01P_PAYLOAD_LENGTH);
}

void APP_SETFLAG(APP_FLAGS_Enum flag, boolean value){
	switch(flag){
		case MESSAGE_RECEIVED:
		{
			app_flags.message_received = value;
		}
		case MESSAGE_TO_SEND:
		{
			app_flags.message_to_send = value;
		}
		default:
		{
			return;
		}
	}

}


void APP_PARSE_COMMAND(){

	if(app_data.rx_data[0] != WORK_STATION){
		return;
	}

    if(memcmp(app_data.rx_data + 1, TURN_ON_WS_COMMAND, NRF24L01P_PAYLOAD_LENGTH - 1) == 0){
    		BSP_START_PRESENCE_COUNTER();
    		BSP_RELAY_ON();
    		app_data.noPresenceSeconds = 0;

    } else if(memcmp(app_data.rx_data + 1, TURN_OFF_WS_COMMAND, NRF24L01P_PAYLOAD_LENGTH - 1) == 0){
    		BSP_STOP_PRESENCE_COUNTER();
        	BSP_RELAY_OFF();
    }

}


APP_DATA_Struct* GET_APP_DATA(){
	return &app_data;
}
