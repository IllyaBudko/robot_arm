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
  uint16_t adc1_data[5];
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


  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  ADC1_Init();

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
  //No need Reset values good 
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

void ADC1_Init(void)
{
  //Turn on GPIOA Clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  //Turn on Clock to ADC
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  //Set 5 pins to analog in GPIOA
  GPIOA->MODER |= 0x3FF << 0;
  GPIOA->PUPDR = 0x00000000;
  
  //ADC prescaler, PCLK/2
  ADC->CCR |= (0x03 << 16);
  //8-bit ADC
  ADC1->CR1 |= (0x02 << 24);
  //scan mode enable
  ADC1->CR1 |= (0x01 << 8);
  //Do timer trigger later, needs setup simple timer for timed adc conversionk trigger
  //ADC1->CR1 |= (0x01 << 28); // trigger detection on rising edge
  //ADC1->CR1 |= (); //select timer trigger here
  
  //ADC data alignment right
  ADC1->CR2 |= ADC_CR2_ALIGN;
  
  //ADC end of conversion selection, overrun only in DMA, check ref man
  ADC1->CR2 |= ADC_CR2_EOCS;
  
  //Do DMA config here
  ADC1->CR2 |= ADC_CR2_DMA;
  
  //ADC sampling cycles, 3 cycles per, just zero both sampling registers
  ADC1->SMPR1 = 0x00000000;
  ADC1->SMPR2 = 0x00000000;
  
  //ADC, select number of conversions, 5
  ADC1->SQR1 |= (5 << 20);
  
  //ADC sequence selection, for now just one after the other
  ADC1->SQR3 = 0x00000000;
  ADC1->SQR3 |= (1 << 5);
  ADC1->SQR3 |= (2 << 10);
  ADC1->SQR3 |= (3 << 15);
  ADC1->SQR3 |= (4 << 20);
  
  //DMA setup for adc here
  //channel0 at stream0
  DMA1_Stream0->CR &= ~(7 << 25);
  //mem data size
  DMA1_Stream0->CR |= (0x01 << 13);
  //periph data size
  DMA1_Stream0->CR |= (0x01 << 11);
  DMA1_Stream0->CR |= DMA_SxCR_MINC;
  DMA1_Stream0->CR |= DMA_SxCR_PINC;
  DMA1_Stream0->CR |= DMA_SxCR_CIRC;
  DMA1_Stream0->CR &= ~(0x03 << 6);
  
  DMA1_Stream0->NDTR = 5;
  DMA1_Stream0->PAR = (uint32_t)(&(ADC1->DR));
  DMA1_Stream0->M0AR = (uint32_t)adc1_data;
  
  DMA1_Stream0->CR |= (1 << 0);
  
  //ADC set to continuous mode
  ADC1->CR2 |= ADC_CR2_CONT;
  //ADC on here
  ADC1->CR2 |= ADC_CR2_ADON;
  
  
}

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
