#ifndef _MY_MATHS_H_
#define _MY_MATHS_H_

#include "stm32f411xe.h"

uint32_t map (uint32_t value, uint32_t In_Min, uint32_t In_Max, uint32_t Out_Min, uint32_t Out_Max);
uint16_t moving_average(uint16_t adc_value);











#endif /*_MY_MATHS_H_*/
