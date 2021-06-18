
#include "servos.h"
#include "my_maths.h"


/*
  V1.0
  
  V2.0
  Add servo name
*/
void Servo_Init(struct servo_ctrl_block * servo)
{
  servo->adc_input_start = 0;
  servo->adc_input_end   = 256;
  
  servo->pwm_pos_lower_limit = 500U;
  servo->pwm_pos_upper_limit = 1000U;
  
  servo->pwm_pos_at_rest = 750U;
  servo->pwm_pos_current = 750U;
  
  size_t adc_ma_buf_sz = sizeof(servo->adc_mov_avg_buffer);
  size_t adc_ma_buf_var_sz = sizeof(servo->adc_mov_avg_buffer[0]);
  
  servo->adc_mov_avg_buffer_size = ((adc_ma_buf_sz / adc_ma_buf_var_sz) - adc_ma_buf_var_sz);
  servo->adc_mov_avg_buffer_idx  = 0;
  servo->adc_mov_avg_value       = 0;
}

uint16_t Servo_Update_Position(struct servo_ctrl_block * servo)
{
  uint16_t temp_pos_current = 0;
  temp_pos_current = (uint16_t)map(servo->adc_mov_avg_value,\
                                   servo->adc_input_start,\
                                   servo->adc_input_end,\
                                   servo->pwm_pos_lower_limit,\
                                   servo->pwm_pos_upper_limit);
  
  servo->pwm_pos_current = temp_pos_current;
  
  
  servo->adc_mov_avg_buffer_idx ++;
  if(servo->adc_mov_avg_buffer_idx == servo->adc_mov_avg_buffer_size)
  {
    servo->adc_mov_avg_buffer_idx = 0;
  }
}














