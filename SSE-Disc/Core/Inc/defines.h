/**
 *  Defines for your entire project at one place
 *
 *	@author 	Tilen MAJERLE
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.net
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H
#include "stm32f4xx_hal.h"

//Put your global defines for all libraries here used in your project
// ENCODER
#define ENCODER_DIRECTION_LEFT -1
#define ENCODER_DIRECTION_RIGHT 1
#define ENCODER_PORT GPIOA
#define ENCODER_PIN GPIO_PIN_2


// HCSR501
#define HCSR501_SETUP_MINUTES 0
#define HCSR501_SETUP_SECONDS 1

#define HCSR501_FALSE 0
#define HCSR501_TRUE 1
#define HCSR501_INITIALIZING 2
#define HCSR501_PORT GPIOB
#define HCSR501_PIN GPIO_PIN_9


// LCD
#define LCD I2C_LCD_1

// nrf24l01p
#define NRF24L01P_SPI                     (&hspi1)

#define NRF24L01P_SPI_CS_PIN_PORT         GPIOA
#define NRF24L01P_SPI_CS_PIN_NUMBER       GPIO_PIN_4

#define NRF24L01P_CE_PIN_PORT             GPIOC
#define NRF24L01P_CE_PIN_NUMBER           GPIO_PIN_4

#define NRF24L01P_IRQ_PIN_PORT            GPIOC
#define NRF24L01P_IRQ_PIN_NUMBER          GPIO_PIN_5

#define NRF24L01P_PAYLOAD_LENGTH          8     // 1 - 32bytes

#define NRF24L01P_CHANNEL 2500
#define NRF24L01P_RATE	_1Mbps
#define NRF24L01P_RETRANSMIT_COUNT 3

typedef uint8_t count;
typedef uint8_t widths;
typedef uint8_t length;
typedef uint16_t delay;
typedef uint16_t channel;

typedef enum
{
    _250kbps = 2,
    _1Mbps   = 0,
    _2Mbps   = 1
} air_data_rate;

typedef enum
{
    _0dBm  = 3,
    _6dBm  = 2,
    _12dBm = 1,
    _18dBm = 0
} output_power;
#endif