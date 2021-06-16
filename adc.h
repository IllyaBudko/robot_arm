#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f411xe.h"

//function prototypes
void ADC1_Init(void);
void ADC1_DMA_Init(uint16_t * adc_data);
void ADC1_TIM_TRGO_Init(void);
void ADC1_Start(void);


#endif /*_ADC_H_*/
