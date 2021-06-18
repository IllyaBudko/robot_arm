#ifndef _SERVOS_H_
#define _SERVOS_H_

#include "stm32f411xe.h"

struct servo_ctrl_block
{
  uint8_t servo_name[15];
  
  uint8_t moving_average_samples;
  


};
















#endif /*_SERVOS_H_*/
