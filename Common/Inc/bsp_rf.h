#ifndef BSP_RF_H
#define BSP_RF_H

#include "nrf24.h"
#include "defines.h"
#include "Util.h"
#include <stdbool.h>
#include <string.h>

typedef enum class{
    NONE = 0,
    TX,
    RX,
	STANDBY
} BSP_RF_MODE_TypeDef;

typedef struct {
    air_data_rate rate;
    channel channel;
    uint8_t retransmit_count;
} BSP_RF_Params_TypeDef;


void BSP_RF_Init(BSP_RF_Params_TypeDef*);
void BSP_RF_Sending();
void BSP_RF_SendMessage(uint8_t payload[NRF24L01P_PAYLOAD_LENGTH]);
void BSP_RF_Listening();
uint8_t BSP_RF_IrqHandler();
void BSP_RF_ReadData(uint8_t payload[NRF24L01P_PAYLOAD_LENGTH]);
BSP_RF_MODE_TypeDef BSP_RF_GetMode();

#endif
