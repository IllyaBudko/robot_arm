#ifndef _SERVOS_H_
#define _SERVOS_H_

#include "stm32f411xe.h"

#define MOV_AVG_BUF_SZ    7

struct servo_ctrl_block
{
  /*
    Add servo name later
  char servo_name[15];
  */
  
  /*
    Do this next version with moving average buffer on heap
    for runtime size allocation, make a moving average buffer
    control block with opaque pointer, just an idea
  
    for now just use fixed size sample number
  
  uint8_t moving_average_samples;
  
  */
  uint8_t adc_mov_avg_buffer_idx;
  uint8_t adc_mov_avg_buffer_size;
  uint16_t adc_mov_avg_buffer[MOV_AVG_BUF_SZ];
  uint16_t adc_mov_avg;
  
  uint32_t pos_lower_limit;
  uint32_t pos_upper_limit;
  
  uint32_t pos_start;
  uint32_t pos_current;
};

//add more params
void Servo_Init(struct servo_ctrl_block * servo);
















#endif /*_SERVOS_H_*/
