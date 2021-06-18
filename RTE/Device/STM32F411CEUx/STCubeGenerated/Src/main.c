/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "main.h"
#include "my_maths.h"

#include "adc.h"
#include "pwm_timers.h"
#include "servos.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void ADC1_Init(void);
/* USER CODE BEGIN PFP */

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
  struct adc_data adc_dma_read_values = {0,0,0,0};
  struct servo_ctrl_block servo1;
  struct servo_ctrl_block servo2;
  struct servo_ctrl_block servo3;
  struct servo_ctrl_block servo4;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  
  Servo_Init(&servo1,TIM_CH1);
  Servo_Init(&servo1,TIM_CH2);
  Servo_Init(&servo1,TIM_CH3);
  Servo_Init(&servo1,TIM_CH4);
  
  ADC1_Init();
  ADC1_DMA_Init(&adc_dma_read_values);
  ADC1_TIM_TRGO_Init();
  ADC1_Start();
  
  PWM_TIM3_Init();
  PWM_TIM3_Start();
  
  /* USER CODE BEGIN Init */
  
  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    moving_average(&servo1,adc_dma_read_values.adc_data_value_1);
    moving_average(&servo1,adc_dma_read_values.adc_data_value_2);
    moving_average(&servo1,adc_dma_read_values.adc_data_value_3);
    moving_average(&servo1,adc_dma_read_values.adc_data_value_4);
    
    Servo_Update_Position(&servo1, TIM3, TIM_CH1);
    Servo_Update_Position(&servo2, TIM3, TIM_CH2);
    Servo_Update_Position(&servo3, TIM3, TIM_CH3);
    Servo_Update_Position(&servo4, TIM3, TIM_CH4);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void TIM2_IRQHandler(void)
{
  if(TIM2->DIER & 0x01)
  {
    if(TIM2->SR & 0x01)
    {
      TIM2->SR &= ~(1 << 0);  
    }
  }
  GPIOB->ODR |= (1 << 12);
  GPIOB->ODR &= ~(1 << 12);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  //No need Reset values good 
}

/* USER CODE BEGIN 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
