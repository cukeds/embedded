
#pragma once
#include "app_defines.h"
#include "bsp.h"


typedef struct {
    uint16_t noPresenceSeconds;
    APP_STATION_STATUS_Enum stationStatus;
    uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH];
    uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH];
} APP_DATA_Struct;

typedef struct {
    boolean message_received;
    boolean message_to_send;
} APP_FLAGS_Struct;

typedef enum {
    MESSAGE_RECEIVED = 0,
    MESSAGE_TO_SEND
} APP_FLAGS_Enum;

void app();
void APP_MESSAGE_RECEIVED();

void APP_SEND_MESSAGE();

void APP_SET_MESSAGE_TO_SEND(uint8_t message[NRF24L01P_PAYLOAD_LENGTH]);

void APP_SET_MESSAGE_RECEIVED(uint8_t message[NRF24L01P_PAYLOAD_LENGTH]);

void APP_PARSE_COMMAND();

void APP_SETFLAG(APP_FLAGS_Enum flag, boolean value);

APP_DATA_Struct* GET_APP_DATA();
