#include "defines.h"

#define SET_FIELD(struct_ptr, field, value) ((struct_ptr)->field = (value))

#define PRESENCE_CUTOFF 80 //cm
#define WORK_STATION 1
#define TURN_ON_WS_COMMAND ((uint8_t[NRF24L01P_PAYLOAD_LENGTH - 1]){1, 0, 0, 0, 0, 0, 0})
#define TURN_OFF_WS_COMMAND ((uint8_t[NRF24L01P_PAYLOAD_LENGTH - 1]){0, 0, 0, 0, 0, 0, 0})
#define SEND_DATA_PERIOD 5 // in seconds


typedef enum {
	StationOff = 0,
	StationOn
} APP_STATION_STATUS_Enum;
