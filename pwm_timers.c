
#include "pwm_timers.h"

void PWM_TIM3_Init(void)
{
  /*
  
  need to setup gpios for timer pwm outputs
  
  */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 
  
  /*GPIOB Pins seup for AF02 for PWM output on TIM3 channels*/
                  /*Pin0       ,  Pin1       ,  Pin4        ,  Pin5*/
  GPIOB->MODER  |= (0x02 << 0) | (0x02 << 2) | (0x02 << 8)  | (0x02 << 10);
  GPIOB->AFR[0] |= (0x02 << 0) | (0x02 << 4) | (0x02 << 16) | (0x02 << 20);
  
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
  
  /*TODO, Add my_maths file pair for no offset map function,
    map wih offset and moving average function. use map function
    delete this after, this is just for now*/
  TIM3->CCR1 = 1000;  // CH3
  TIM3->CCR2 = 1000;  // CH4
  TIM3->CCR3 = 1000;  // CH1
  TIM3->CCR4 = 1000; // CH2
  
}

void PWM_TIM3_Start(void)
{
  /*UG bit needs to be set one time to start pwm, read more about this
    start both timer here*/
  /*set Update generation bit to start pwm mode*/
  TIM3->EGR |= TIM_EGR_UG;
  /*set Counter enable bit to start counter*/
  TIM3->CR1 |= TIM_CR1_CEN;
}




