
#pragma once
#include "app_defines.h"
#include "bsp_rf.h"
#include "bsp_hcsr501.h"
#include "bsp_rc522.h"
#include "bsp_lcd.h"
#include "bsp_encoder.h"
#include "bsp.h"

typedef struct {
	uint8_t serial_number;
	char name[30];
	uint8_t work_station;
	boolean present;
	uint16_t total_time_inactive;
	uint16_t total_time_active;
	uint16_t longest_time_inactive;
}APP_USER_Struct;

typedef struct {
	APP_USER_Struct* user;
    uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH];
    uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH];
    boolean motion_status;
    uint8_t motion_activity;
} APP_DATA_Struct;

typedef struct {
    boolean message_received;
    boolean message_to_send;
    boolean is_card_cooldown;
    boolean waiting_for_user;
    boolean update_motion;
    boolean button_pressed;
} APP_FLAGS_Struct;

typedef enum {
    MESSAGE_RECEIVED = 0,
    MESSAGE_TO_SEND,
	WAITING_FOR_USER,
	IS_CARD_COOLDOWN,
	UPDATE_MOTION,
	BUTTON_PRESSED,
} APP_FLAGS_Enum;

typedef enum {
	Idle = 0,
	ReadingCard
} APP_STATES_Enum;

void app();
void app_init();
void APP_MESSAGE_RECEIVED();

void APP_SEND_MESSAGE();

void APP_SET_MESSAGE_TO_SEND(uint8_t message[NRF24L01P_PAYLOAD_LENGTH]);

void APP_SETFLAG(APP_FLAGS_Enum flag, boolean value);
boolean APP_GET_USER_BY_SERIAL_NUMBER(uint8_t sNum, APP_USER_Struct **user);
boolean APP_GET_USER_BY_WORKSTATION(uint8_t ws, APP_USER_Struct **user);
void APP_SEND_COMMAND_TO_WORK_STATION(uint8_t ws, uint8_t command[NRF24L01P_PAYLOAD_LENGTH-1]);
void APP_PARSE_COMMAND();
void APP_UPDATE_WORKSTATION();
APP_DATA_Struct* GET_APP_DATA();

void APP_MENU();
