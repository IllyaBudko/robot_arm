
#include "my_maths.h"

#define MA_SAMPLE_NUM 10U

uint32_t map (uint32_t value, uint32_t In_Min, uint32_t In_Max, uint32_t Out_Min, uint32_t Out_Max)
{
  return (value - In_Min) * (Out_Max - Out_Min) / (In_Max - In_Min) + Out_Min;
}

uint32_t moving_average(void)
{
    ADC1_Mov_Avg -= ADC1_Samples[idx];
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  ADC1_Samples[idx] = HAL_ADC_GetValue(&hadc1);
    adc1_raw = ADC1_Samples[idx];
    ADC1_Samples[idx] = ADC1_Samples[idx] & 0xFFFFFFFFU;
	  ADC1_Mov_Avg += ADC1_Samples[idx];
	  ADC1_Value = ADC1_Mov_Avg / SAMPLE_NUM;
}