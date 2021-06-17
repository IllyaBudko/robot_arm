
#include "pwm_timers.h"

void PWM_TIM3_Init(void)
{
  /*
  
  need to setup gpios for timer pwm outputs
  
  */
  
  /*TIM3 clock enable*/
  RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  
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
  
  /*pwm polarity*/
  TIM3->CCER &= ~(0x03 << 1);
  TIM3->CCER &= ~(0x03 << 5);
  TIM3->CCER &= ~(0x03 << 9);
  TIM3->CCER &= ~(0x03 << 13);
  
  /*pwm output enable*/
  TIM3->CCER |= TIM_CCER_CC1E;
  TIM3->CCER |= TIM_CCER_CC2E;
  TIM3->CCER |= TIM_CCER_CC3E;
  TIM3->CCER |= TIM_CCER_CC4E;
  
  /*figure oout default CCR registers later :)*/
  
  
}

void PWM_TIM_Start(void)
{
  /*UG bit needs to be set one time to start pwm, read more about this
    start both timer here*/
  
}




