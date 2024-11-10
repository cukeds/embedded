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
#include "stm32f1xx_hal.h"

//Put your global defines for all libraries here used in your project
#define STM32F1

// ENCODER
#define ENCODER_DIRECTION_LEFT -1
#define ENCODER_DIRECTION_RIGHT 1
#define ENCODER_PORT GPIOA
#define ENCODER_PIN GPIO_PIN_2
#define DEBOUNCE_DELAY 150

// HCSR501
#define HCSR501_SETUP_MINUTES 0
#define HCSR501_SETUP_SECONDS 1

#define HCSR501_TRIGGER_TIME 3// Seconds

#define HCSR501_FALSE 0
#define HCSR501_TRUE 1
#define HCSR501_INITIALIZING 2
#define HCSR501_PORT GPIOB
#define HCSR501_PIN GPIO_PIN_9
#define HCSR501_SW_EXTI_LINE GPIO_PIN_13


// LCD
#define LCD I2C_LCD_1

// NRF24L01
#define NRF24L01P_SPI                     (&hspi2)

#define NRF24L01P_SPI_CS_PIN_PORT         GPIOA
#define NRF24L01P_SPI_CS_PIN_NUMBER       GPIO_PIN_8

#define NRF24L01P_CE_PIN_PORT             GPIOB
#define NRF24L01P_CE_PIN_NUMBER           GPIO_PIN_12

#define NRF24L01P_IRQ_PIN_PORT            GPIOA
#define NRF24L01P_IRQ_PIN_NUMBER          GPIO_PIN_10

#define NRF24L01P_PAYLOAD_LENGTH          8     // 1 - 32bytes
#define NRF24L01P_ADDRESS				  { 'E', 'S', 'B' }

#define nRF24_WAIT_TIMEOUT         		  (uint32_t)0x000FFFFF

#define NRF24L01P_CHANNEL 90
#define NRF24L01P_RATE _250kbps
#define NRF24L01P_RETRANSMIT_COUNT 3

typedef uint8_t count;
typedef uint8_t widths;
typedef uint8_t length;
typedef uint16_t delay;
typedef uint16_t channel;

//**** TypeDefs ****//

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

typedef enum {
	False = 0,
	True
} boolean;
#endif
