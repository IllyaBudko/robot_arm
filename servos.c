
#include "servos.h"
#include "my_maths.h"


/*
  V1.0
*/
void Servo_Init(struct servo_ctrl_block * servo, uint32_t pwm_low_limit, uint32_t pwm_high_limit, uint8_t timer_channel)
{
  servo->adc_input_start = 0;
  servo->adc_input_end   = 4095;
  
  servo->pwm_pos_lower_limit = pwm_low_limit;  // 200 // 500
  servo->pwm_pos_upper_limit = pwm_high_limit; // 1200 // 1000
  
  servo->pwm_pos_at_rest = 750U;
  servo->pwm_pos_current = 750U;
  
  //uint8_t adc_ma_buf_sz = sizeof(servo->adc_mov_avg_buffer);
  //uint8_t adc_ma_buf_var_sz = sizeof(servo->adc_mov_avg_buffer[0]);
  
  servo->adc_mov_avg_buffer_size = MOV_AVG_BUF_SZ;
  servo->adc_mov_avg_buffer_idx  = 0;
  servo->adc_mov_avg             = 0;
  servo->adc_mov_avg_value       = 0;
  
  servo->timer_channel = timer_channel;
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
  uint8_t timer_ch = servo->timer_channel;
  switch(timer_ch)
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














