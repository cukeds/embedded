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
#include "i2c.h"
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
uint8_t config_register;
uint16_t button=0;
volatile unsigned long handledInterruptsLCD = 0;
volatile unsigned long toHandleInterruptsLCD = 0;
volatile unsigned long handledInterruptsRF = 0;
volatile unsigned long toHandleInterruptsRF = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void received_message();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH] = {0,};
uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7};
bool RetFalse(){
	return false;
}
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
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  BSP_LCD_SetupParams_TypeDef lcd_params;
  //lcd_params.condition = BSP_HCSR501_Ready;
  //lcd_params.setup_time = (uint8_t) HCSR501_SETUP_SECONDS + HCSR501_SETUP_MINUTES*60;
  //lcd_params.seconds = &motion[4];
  lcd_params.condition = RetFalse;
  lcd_params.setup_time = 0;
  lcd_params.seconds = 0;


  BSP_ENCODER_Init();
//  BSP_RC522_Init();
  BSP_LCD_Init(&lcd_params);
  BSP_LCD_SendMessage("Hola", 0, 0, true);


  BSP_RF_Params_TypeDef rf_params = {0};
  rf_params.channel = NRF24L01P_CHANNEL;
  rf_params.rate = NRF24L01P_RATE;
  rf_params.retransmit_count = NRF24L01P_RETRANSMIT_COUNT;
  BSP_RF_Init(&rf_params);
  BSP_RF_Sending();
  HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
  uint8_t last_state = 0;
  uint8_t waiting = 1;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  button = BSP_ENCODER_GetSwitch();
	  if(button && waiting){
		  tx_data[0] = BSP_ENCODER_GetDirection() > 0 ? 1 : 2;
		  tx_data[1] = (uint8_t) BSP_ENCODER_GetCount() & 0xFF; // 0..7
		  tx_data[2] = (uint8_t) (BSP_ENCODER_GetCount() >> 8) & 0xFF;// 8..15
		  tx_data[3] = (uint8_t) (BSP_ENCODER_GetCount() >> 16) & 0xFF;// 16..23
		  tx_data[4] = (uint8_t) (BSP_ENCODER_GetCount() >> 24) & 0xFF;// 24..31
		  HAL_GPIO_TogglePin(GPIOC, LED_Pin);
		  BSP_RF_SendMessage(tx_data);
		  HAL_GPIO_TogglePin(GPIOC, LED_Pin);
		  waiting = 1;
	  }

	  if(handledInterruptsRF != toHandleInterruptsRF){
		  handledInterruptsRF = toHandleInterruptsRF;
		  if(rx_data[7] == 1 && last_state != 1){
			  last_state = 1;
			  BSP_LCD_SendMessage("No one there", 0, 0, true);
		  }else if(rx_data[7] == 2 && last_state != 2){
			  last_state = 2;
			  BSP_LCD_SendMessage("SOMEONE there", 0, 0, true);
		  }else if(rx_data[7] == 0 && last_state != 0){
			  last_state = 0;
			  BSP_LCD_SendMessage("No connection", 0, 0, true);
		  }
		  waiting = 1;
	  }


	  //
	  //00001010
//	  HAL_Delay(100); // 100ms
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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


void received_message()
{
	HAL_GPIO_TogglePin(GPIOC, LED_Pin);
	toHandleInterruptsRF += BSP_RF_IrqHandler();
	BSP_RF_ReadData(rx_data);
	HAL_GPIO_TogglePin(GPIOC, LED_Pin);

}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//	if(GPIO_Pin == GPIO_PIN_13){
//		BSP_HCSR501_Init();
//	}
//	if(GPIO_Pin == HCSR501_PIN){
//		toHandleInterruptsLCD++;
//
//	}
	if(GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER)
	{
		received_message();
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
