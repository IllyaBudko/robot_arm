
#include "my_maths.h"

uint32_t map (uint32_t value, uint32_t In_Min, uint32_t In_Max, uint32_t Out_Min, uint32_t Out_Max)
{
  return ((value - In_Min) * (Out_Max - Out_Min) / (In_Max - In_Min) + Out_Min);
}

//This function is generic to 32 bit variables, use typecasting however logical
uint32_t no_offset_map(uint32_t known_num, uint32_t known_denom, uint32_t unknown_denom)
{
  return ((known_num * unknown_denom) / known_denom);
}

/*
  V1.0
  This function returns moving average value after 
*/

void moving_average(struct servo_ctrl_block * servo, uint16_t adc_value)
{
  uint8_t temp_servo_idx = servo->adc_mov_avg_buffer_idx;
  servo->adc_mov_avg -= servo->adc_mov_avg_buffer[temp_servo_idx];
  servo->adc_mov_avg_buffer[temp_servo_idx] = adc_value;
  
  //filter some numbers off the back
  servo->adc_mov_avg_buffer[temp_servo_idx] = servo->adc_mov_avg_buffer[temp_servo_idx] & 0xFFFFU;
  
  servo->adc_mov_avg += servo->adc_mov_avg_buffer[temp_servo_idx];
  
  //return servo->adc_mov_avg / 7;
  
  servo->adc_mov_avg_value = servo->adc_mov_avg / MOV_AVG_BUF_SZ;
}














