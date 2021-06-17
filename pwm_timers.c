
#include "pwm_timers.h"

void PWM_TIM3_Init(void)
{
  /*
  
  need to setup gpios for timer pwm outputs
  
  and enable clock for tim3
  
  */
  
  
  /*TIM3 counter reg*/
  TIM3->ARR = 9999;
  /*TIM3 prescaler reg*/
  TIM3->PSC = 31;
  
  /*TIM3 edge aligned*/
  TIM3->CR1 &= ~(0x03 << 5);
  
  /*autoreload enable*/
  TIM3->CR1 |= TIM_CR1_ARPE;
  
  /*direction, cleared to be sure*/
  TIM3->CR1 &= ~(1 << 4);
  
  /*channel direction*/
  TIM3->CCMR1 &= ~(0x03 << 0);
  TIM3->CCMR1 &= ~(0x03 << 8);
  TIM3->CCMR2 &= ~(0x03 << 0);
  TIM3->CCMR2 &= ~(0x03 << 8);
  
  /*4 channels setup for pwm*/
  TIM3->CCMR1 |= (0x06 << 4); //ch1
  TIM3->CCMR1 |= (0x06 << 12); //ch2
  TIM3->CCMR2 |= (0x06 << 4); //ch3
  TIM3->CCMR2 |= (0x06 << 12); //ch4
  
  /*preload enable*/
  TIM3->CCMR1 |= TIM_CCMR1_OC1PE; //ch1
  TIM3->CCMR1 |= TIM_CCMR1_OC2PE; //ch2
  TIM3->CCMR2 |= TIM_CCMR2_OC3PE; //ch3
  TIM3->CCMR2 |= TIM_CCMR2_OC4PE; //ch4
  
  /*
  
  need to setup channels polarity, CCxP bits in TIM_CCER
  
  and output enable, CCxE bit in TIM_CCER
  
  */
  
  
  
  
  
  
}

void PWM_TIM3_Start(void)
{
  
}




