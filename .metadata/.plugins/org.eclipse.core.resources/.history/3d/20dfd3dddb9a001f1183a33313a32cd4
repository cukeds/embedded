#include "bsp_rf.h"
static BSP_RF_Params_TypeDef *params;
static BSP_RF_MODE_TypeDef mode = NONE;
static uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH];
void BSP_RF_Init(BSP_RF_Params_TypeDef* _params)
{
    params = _params;
    nrf24l01p_init(_params->rate, _params->channel, _params->retransmit_count);
    nrf24l01p_standby();
    mode = STANDBY;
}

void BSP_RF_Sending(){
	if(mode == STANDBY){
		nrf24l01p_tx_init();
	}else if(mode == RX){
		nrf24l01p_standby();
		nrf24l01p_tx_init();
	}
	mode = TX;
}

void BSP_RF_SendMessage(uint8_t payload[NRF24L01P_PAYLOAD_LENGTH])
{
	nrf24l01p_tx_transmit(payload);
}

void BSP_RF_Listening()
{
	if(mode == STANDBY){
		nrf24l01p_rx_init();
	}
	else if(mode == TX){
		nrf24l01p_standby();
		nrf24l01p_rx_init();
	}
	mode = RX;
}

void _BSP_RF_ReceiveMessage(){
	nrf24l01p_rx_receive(rx_data);
	nrf24l01p_clear_rx_dr();
}

uint8_t BSP_RF_IrqHandler(){
	uint8_t ret = 0;
	uint8_t status = nrf24l01p_get_status();
	if(status >> 4 == 1){
		nrf24l01p_clear_max_rt();
	}
	else if(status >> 5 == 1){
		nrf24l01p_clear_tx_ds();
	}
	else if(status >> 6 == 1){
		_BSP_RF_ReceiveMessage();
		ret = 1;
	}

	return ret;
}

void BSP_RF_ReadData(uint8_t payload[NRF24L01P_PAYLOAD_LENGTH]){
	memcpy(payload, rx_data, NRF24L01P_PAYLOAD_LENGTH);
}
