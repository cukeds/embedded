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
#define STM32F4

// ENCODER
#define ENCODER_DIRECTION_LEFT -1
#define ENCODER_DIRECTION_RIGHT 1
#define ENCODER_PORT GPIOA
#define ENCODER_PIN GPIO_PIN_2


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
#define NRF24L01P_ADDRESS				  { 'E', 'S', 'B' }

#define NRF24L01P_CHANNEL 90
#define NRF24L01P_RATE	_250kbps
#define NRF24L01P_RETRANSMIT_COUNT 3

typedef uint8_t count;
typedef uint8_t widths;
typedef uint8_t length;
typedef uint16_t delay;
typedef uint16_t channel;

//**** TypeDefs ****//
//1. Power Amplifier function, NRF24_setPALevel()
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

// Defines HCSR04

#define HCSR04_TRIG_PIN GPIO_PIN_8
#define HCSR04_TRIG_PORT GPIOE

#define HCSR04_ECHO_PIN GPIO_PIN_9
#define HCSR04_ECHO_PORT GPIOE

#define HCSR04_TIM TIM1
#define HCSR04_TIM_CHANNEL TIM_CHANNEL_1
#define HCSR04_TIM_INSTANCE htim1
#define HCSR04_TIM_CLK 72

#define HCSR04_SWIER_LINE GPIO_PIN_8

typedef enum {
	False = 0,
	True
} boolean;
#endif
