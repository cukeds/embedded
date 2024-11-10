/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "defines.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t sNum[5];
uint8_t motion[5];
int16_t button = 0;
double voltage;
uint32_t adc_value;
volatile uint8_t valid = 0;
volatile unsigned long handledInterrupts = 0;
volatile unsigned long toHandleInterrupts = 0;

extern APP_DATA_Struct app_data;

float duty_cycle = 0.0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void received_message();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_4);



  BSP_RF_Params_TypeDef rf_params = {0};
  rf_params.channel = NRF24L01P_CHANNEL;
  rf_params.rate = NRF24L01P_RATE;
  rf_params.retransmit_count = NRF24L01P_RETRANSMIT_COUNT;
  BSP_RF_Init(&rf_params);
  BSP_RF_Listening();
  BSP_RELAY_OFF();
  BSP_STOP_PRESENCE_COUNTER();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  app();


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


inline void received_message()
{
	if(!BSP_RF_IrqHandler())
		return;
	HAL_GPIO_TogglePin(GPIOD, LED_RX_Pin);
	APP_SETFLAG(MESSAGE_RECEIVED, True);
	HAL_GPIO_TogglePin(GPIOD, LED_RX_Pin);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER)
	{
		received_message();
	}

}

#define min(x,y) (((x) <= (y)) ? (x) : (y))
#define max(x,y) (((x) >= (y)) ? (x) : (y))
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	uint8_t distance = HAL_HCSR04_GetDistance();
	duty_cycle =  ((float) max(min(distance, 100), 20) / 100);
	uint32_t pulse_width = 100 * duty_cycle;
	if(htim == &htim2){
		TIM2->CCR2 = pulse_width;
		TIM2->CCR3 = pulse_width;
		TIM2->CCR4 = pulse_width;
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim == &htim3){
		HAL_HCSR04_Trigger();
	}

	if(htim == &htim4){
		static uint16_t counter = 0;
		if(counter < SEND_DATA_PERIOD){
			if(BSP_HCSR04_GetPresence(PRESENCE_CUTOFF) == NoPresence){
				// Count up time not present
				SET_FIELD(&app_data, noPresenceSeconds, app_data.noPresenceSeconds + 1);
			}else if(BSP_HCSR04_GetPresence(PRESENCE_CUTOFF) == Presence){
				// Counter of time to
				SET_FIELD(&app_data, noPresenceSeconds, 0);
 			}

			counter++;
			return;
		}

		static uint8_t message[NRF24L01P_PAYLOAD_LENGTH] = {0,};
		message[0] = WORK_STATION;
		message[1] = (uint8_t) (app_data.noPresenceSeconds >> 8) & 0xFF;  // High byte
		message[2] = (uint8_t) (app_data.noPresenceSeconds & 0xFF);         // Low byte

		APP_SET_MESSAGE_TO_SEND(message);
		APP_SETFLAG(MESSAGE_TO_SEND, True);
		counter = 0;
	}

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
