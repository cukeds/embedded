#include "nrf24_hal.h"



// Low level SPI transmit/receive function (hardware depended)
// input:
//   data - value to transmit via SPI
// return: value received from SPI
uint8_t nRF24_LL_RW(uint8_t data) {
	 // Wait until TX buffer is empty
	uint8_t* pRxData = {0,};
	HAL_SPI_TransmitReceive(NRF24L01P_SPI, &data, pRxData, 1, 100);
	// Return received byte
	return *pRxData;
}

void nRF24_CE_L(void){
	HAL_GPIO_WritePin(NRF24L01P_CE_PIN_PORT, NRF24L01P_CE_PIN_NUMBER, GPIO_PIN_RESET);
}

void nRF24_CE_H(void){
	HAL_GPIO_WritePin(NRF24L01P_CE_PIN_PORT, NRF24L01P_CE_PIN_NUMBER, GPIO_PIN_SET);
}


void nRF24_CSN_L(void){
	HAL_GPIO_WritePin(NRF24L01P_SPI_CS_PIN_PORT, NRF24L01P_SPI_CS_PIN_NUMBER, GPIO_PIN_RESET);
}
void nRF24_CSN_H(void){
	HAL_GPIO_WritePin(NRF24L01P_SPI_CS_PIN_PORT, NRF24L01P_SPI_CS_PIN_NUMBER, GPIO_PIN_SET);
}
