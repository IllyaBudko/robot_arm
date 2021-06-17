
#include "my_maths.h"

uint32_t map (uint32_t value, uint32_t In_Min, uint32_t In_Max, uint32_t Out_Min, uint32_t Out_Max)
{
  return (value - In_Min) * (Out_Max - Out_Min) / (In_Max - In_Min) + Out_Min;
}