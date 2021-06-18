
#include "servos.h"
#include "my_maths.h"


/*
  V1.0
*/
void Servo_Init(struct servo_ctrl_block * servo, uint8_t timer_channel)
{
  servo->adc_input_start = 0;
  servo->adc_input_end   = 256;
  
  servo->pwm_pos_lower_limit = 500U;
  servo->pwm_pos_upper_limit = 1000U;
  
  servo->pwm_pos_at_rest = 750U;
  servo->pwm_pos_current = 750U;
  
  uint8_t adc_ma_buf_sz = sizeof(servo->adc_mov_avg_buffer);
  uint8_t adc_ma_buf_var_sz = sizeof(servo->adc_mov_avg_buffer[0]);
  
  servo->adc_mov_avg_buffer_size = ((adc_ma_buf_sz / adc_ma_buf_var_sz) - adc_ma_buf_var_sz);
  servo->adc_mov_avg_buffer_idx  = 0;
  servo->adc_mov_avg_value       = 0;
}

void Servo_Update_Position(struct servo_ctrl_block * servo, TIM_TypeDef * timer, volatile uint32_t timer_channel)
{
  uint16_t temp_pos_current = 0;
  temp_pos_current = (uint16_t)map(servo->adc_mov_avg_value,\
                                   servo->adc_input_start,\
                                   servo->adc_input_end,\
                                   servo->pwm_pos_lower_limit,\
                                   servo->pwm_pos_upper_limit);
  
  servo->pwm_pos_current = temp_pos_current;
  switch(servo->timer_channel)
  {
    case TIM_CH1:
      timer->CCR1 = servo->pwm_pos_current;
      break;
    case TIM_CH2:
      timer->CCR2 = servo->pwm_pos_current;
      break;
    case TIM_CH3:
      timer->CCR3 = servo->pwm_pos_current;
      break;
    case TIM_CH4:
      timer->CCR4 = servo->pwm_pos_current;
      break;
    default:
      while(1);
  }    
  
  servo->adc_mov_avg_buffer_idx ++;
  if(servo->adc_mov_avg_buffer_idx == servo->adc_mov_avg_buffer_size)
  {
    servo->adc_mov_avg_buffer_idx = 0;
  }
}














