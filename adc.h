#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f411xe.h"

struct adc_data
{
  volatile uint16_t adc_data_value_1;
  volatile uint16_t adc_data_value_2;
  volatile uint16_t adc_data_value_3;
  volatile uint16_t adc_data_value_4;
};

//function prototypes
void ADC1_Init(void);
void ADC1_DMA_Init(struct adc_data * adc_dma_value);
void ADC1_TIM_TRGO_Init(void);
void ADC1_Start(void);


#endif /*_ADC_H_*/
