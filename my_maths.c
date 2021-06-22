
#include "my_maths.h"


/*
  map function needs to be rewritten to accomodate for integer truncation
*/
uint16_t map (uint16_t value, uint16_t In_Min, uint16_t In_Max, uint16_t Out_Min, uint16_t Out_Max)
{
  uint16_t new_value = 0;
  new_value = ((value - In_Min) * ((Out_Max - Out_Min) / (In_Max - In_Min)) + Out_Min);
  return new_value;
}

//This function is generic to 32 bit variables, use typecasting however logical
uint16_t no_offset_map(uint16_t known_num, uint16_t known_denom, uint16_t unknown_denom)
{
  return ((known_num * unknown_denom) / known_denom);
}

/*
  V1.0
  This function returns moving average value after 
*/

void moving_average(struct servo_ctrl_block * servo, uint16_t adc_value)
{
  servo->adc_mov_avg -= servo->adc_mov_avg_buffer[servo->adc_mov_avg_buffer_idx];
  servo->adc_mov_avg_buffer[servo->adc_mov_avg_buffer_idx] = adc_value;
  
  //filter some numbers off the back
  servo->adc_mov_avg_buffer[servo->adc_mov_avg_buffer_idx] = servo->adc_mov_avg_buffer[servo->adc_mov_avg_buffer_idx] & 0xFFFFU;
  
  servo->adc_mov_avg += servo->adc_mov_avg_buffer[servo->adc_mov_avg_buffer_idx];
  
  //return servo->adc_mov_avg / 7;
  
  servo->adc_mov_avg_value = servo->adc_mov_avg / MOV_AVG_BUF_SZ;
}














