#ifndef _MY_MATHS_H_
#define _MY_MATHS_H_

#include "stm32f411xe.h"
#include "servos.h"

uint16_t map (uint16_t value, uint16_t In_Min, uint16_t In_Max, uint16_t Out_Min, uint16_t Out_Max);

//This function is generic to 32 bit variables, use typecasting however logical
uint16_t no_offset_map(uint16_t known_num, uint16_t known_denom, uint16_t unknown_denom);

void moving_average(struct servo_ctrl_block * servo, uint16_t adc_value);











#endif /*_MY_MATHS_H_*/
