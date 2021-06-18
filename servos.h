#ifndef _SERVOS_H_
#define _SERVOS_H_

#include "stm32f411xe.h"

struct servo_ctrl_block
{
  uint8_t servo_name[15];
  
  /*
    Do this next version with moving average buffer on heap
    for runtime size allocation, make a moving average buffer
    control block with opaque pointer, just an idea
  
    for now just use fixed size sample number
  
  uint8_t moving_average_samples;
  
  */
  
  uint32_t lower_limit;
  uint32_t upper_limit;
  
  uint32_t start_position;
  uint32_t current_position;
};

void Servo_Init(uint8_t * servo_name,);















#endif /*_SERVOS_H_*/
