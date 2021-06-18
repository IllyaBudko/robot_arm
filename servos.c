
#include "servos.h"
#include "my_maths.h"


/*
  V1.0
  
  V2.0
  Add servo name
*/
void Servo_Init(struct servo_ctrl_block * servo)
{
  struct servo_ctrl_block temp_servo;
  
  
  
  temp_servo.pos_lower_limit = 500U;
  temp_servo.pos_upper_limit = 1000U;
  
  temp_servo.pos_start = 750U;
  temp_servo.pos_current = 750U;
  
    *servo = temp_servo;
  
  servo->adc_mov_avg_buffer_size = (sizeof(servo->adc_mov_avg_buffer) / sizeof(servo->adc_mov_avg_buffer[0]));
}
