#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f411xe.h"

volatile struct adc_data
{
  uint16_t adc_data_value_1;
  uint16_t adc_data_value_2;
  uint16_t adc_data_value_3;
  uint16_t adc_data_value_4;
};

//function prototypes
void ADC1_Init(void);
void ADC1_DMA_Init(struct adc_data * adc_dma_value);
void ADC1_TIM_TRGO_Init(void);
void ADC1_Start(void);


#endif /*_ADC_H_*/
