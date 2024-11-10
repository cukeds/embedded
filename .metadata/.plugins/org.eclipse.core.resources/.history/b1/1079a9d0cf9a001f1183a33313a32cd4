#include "bsp_rf.h"
static BSP_RF_Params_TypeDef *params;
static BSP_RF_MODE_TypeDef mode = NONE;
static uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH];
static uint8_t ack[NRF24L01P_PAYLOAD_LENGTH];
static const uint8_t  nRF24_ADDR[] = NRF24L01P_ADDRESS;


void _BSP_RF_ReceiveMessage();

void BSP_RF_Init(BSP_RF_Params_TypeDef* _params)
{
	nRF24_CE_L();

    nRF24_Init();
	nRF24_SetRFChannel(_params->channel);
	nRF24_SetDataRate(_params->rate);
	nRF24_SetCRCScheme(nRF24_CRC_2byte);
	nRF24_SetAddrWidth(3);
	params = _params;
}

void BSP_RF_Sending(){
	nRF24_SetAddr(nRF24_PIPETX, nRF24_ADDR); // program TX address
	nRF24_SetAddr(nRF24_PIPE0, nRF24_ADDR); // program address for pipe#0, must be same as TX (for Auto-ACK)

	// Set TX power (maximum)
	nRF24_SetTXPower(nRF24_TXPWR_0dBm);

	// Configure auto retransmit: 10 retransmissions with pause of 2500s in between
	nRF24_SetAutoRetr(nRF24_ARD_2500us, 10);

	// Enable Auto-ACK for pipe#0 (for ACK packets)
	nRF24_EnableAA(nRF24_PIPE0);

	// Set operational mode (PTX == transmitter)
	nRF24_SetOperationalMode(nRF24_MODE_TX);

	// Clear any pending IRQ flags
	nRF24_ClearIRQFlags();

	// Wake the transceiver
	nRF24_SetPowerMode(nRF24_PWR_UP);
	nRF24_CE_H();
	mode = TX;
}

void BSP_RF_SendMessage(uint8_t payload[NRF24L01P_PAYLOAD_LENGTH]){
		nRF24_TransmitPacket(payload, NRF24L01P_PAYLOAD_LENGTH);
}

void BSP_RF_Listening()
{
	nRF24_SetAddr(nRF24_PIPE1, nRF24_ADDR); // program address for pipe
	nRF24_SetRXPipe(nRF24_PIPE1, nRF24_AA_ON, 10); // Auto-ACK: enabled, payload length: 10 bytes
    nRF24_SetTXPower(nRF24_TXPWR_0dBm);
    nRF24_SetOperationalMode(nRF24_MODE_RX);
    nRF24_ClearIRQFlags();
    nRF24_SetPowerMode(nRF24_PWR_UP);
    nRF24_CE_H();

	mode = RX;
}

void _BSP_RF_ReceiveMessage(){

	uint8_t payload_length = NRF24L01P_PAYLOAD_LENGTH;
	nRF24_ReadPayload(rx_data, &payload_length);
	nRF24_ClearIRQFlags();

}

void BSP_RF_SetAck(uint8_t payload[NRF24L01P_PAYLOAD_LENGTH]){
	memcpy(ack, payload, NRF24L01P_PAYLOAD_LENGTH);
}

uint8_t BSP_RF_IrqHandler(){
	uint8_t ret = 0;
	uint8_t payload_length = NRF24L01P_PAYLOAD_LENGTH;
	if(mode == RX){
		ret = 1;
	}

	_BSP_RF_ReceiveMessage();

	return ret;
}

void BSP_RF_ReadData(uint8_t payload[NRF24L01P_PAYLOAD_LENGTH]){
	memcpy(payload, rx_data, NRF24L01P_PAYLOAD_LENGTH);
}
