#ifndef _MY_MATHS_H_
#define _MY_MATHS_H_

#include "stm32f411xe.h"
#include "servos.h"

uint32_t map (uint32_t value, uint32_t In_Min, uint32_t In_Max, uint32_t Out_Min, uint32_t Out_Max);

//This function is generic to 32 bit variables, use typecasting however logical
uint32_t no_offset_map(uint32_t known_num, uint32_t known_denom, uint32_t unknown_denom);

void moving_average(struct servo_ctrl_block * servo, uint16_t adc_value);











#endif /*_MY_MATHS_H_*/
