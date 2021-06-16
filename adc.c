
#include <stdint.h>

#include "adc.h"


void ADC1_Init(void)
{
  //Turn on GPIOA Clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  //Turn on Clock to ADC
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  //Set 5 pins to analog in GPIOA
  GPIOA->MODER |= 0x3FF << 0;
  GPIOA->PUPDR |= 0x3FF << 0;
  
  //ADC prescaler, PCLK/2
  //ADC->CCR |= (0x03 << 16);
  //8-bit ADC
  ADC1->CR1 |= (0x02 << 24);
  //scan mode enable
  ADC1->CR1 |= (0x01 << 8);
  
  /*ADC periph trigger settings*/
  ADC1->CR2 |= (0x01 << 28); // trigger detection on rising edge
  ADC1->CR2 |= (0x06 << 24); //TIM2 TRGO
  
  //ADC data alignment right
  ADC1->CR2 &= ~ADC_CR2_ALIGN;
  
  //ADC end of conversion selection, overrun only in DMA, check ref man
  ADC1->CR2 |= ADC_CR2_EOCS;
  
  //Do DMA config here
  ADC1->CR2 |= ADC_CR2_DDS;
  ADC1->CR2 |= ADC_CR2_DMA;
  
  //ADC sampling cycles, 3 cycles per, just zero both sampling registers
  ADC1->SMPR1 = 0x00000000;
  ADC1->SMPR2 &= ~0x07FFF;
  
  //ADC, select number of conversions, 5
  ADC1->SQR1 |= (0x4 << 20);
  
  //ADC sequence selection, for now just one after the other
  ADC1->SQR3 |= (1 << 5);
  ADC1->SQR3 |= (2 << 10);
  ADC1->SQR3 |= (3 << 15);
  ADC1->SQR3 |= (4 << 20);
  
  //ADC set to continuous mode
  ADC1->CR2 |= ADC_CR2_CONT;

}
void ADC1_DMA_Init(uint16_t * adc_data)
{
  
  ////Needs to be double-checked
  // DMA2 Clock enable
  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
  
  /*Channel 0 selected for ADC1, as per ref manual.
    bits cleared to make sure proper channel is selected*/
  DMA2_Stream0->CR &= ~(7 << 25);
  
  //mem data size
  DMA2_Stream0->CR |= (0x01 << 13);
  //periph data size
  DMA2_Stream0->CR |= (0x01 << 11);
  //Set memory increment mode
  DMA2_Stream0->CR |= DMA_SxCR_MINC;
  /*DMA2 configured in circular mode, will change later,
    after timer trigger gets setup for adc conversion trigger*/
  DMA2_Stream0->CR |= DMA_SxCR_CIRC;
  
  //Clear direction bit to make sure periph to mem data transfer is accomplished
  DMA2_Stream0->CR &= ~(0x03 << 6);
  
  //number of data transfers = 5
  DMA2_Stream0->NDTR = 5;
  
  DMA2_Stream0->PAR = (uint32_t)(&(ADC1->DR));
  DMA2_Stream0->M0AR = (uint32_t)adc_data;
  
  /*Cleared for use of direct mode in DMA transfer,
    might change later to be used with FIFO*/
  DMA2_Stream0->FCR &= ~DMA_SxFCR_DMDIS;
}

void ADC1_TIM_TRGO_Init(void)
{
  //Do TIM2 setup here
}

void ADC1_Start(void)
{
  //Start DMA before periph, as per DMA guide
  DMA2_Stream0->CR |= (1 << 0);
  
  //ADC ON here
  ADC1->CR2 |= ADC_CR2_ADON;
  ADC1->CR2 |= ADC_CR2_SWSTART;
}

