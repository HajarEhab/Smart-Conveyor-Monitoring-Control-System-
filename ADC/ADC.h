#ifndef ADC_H
#define ADC_H
#include "Gpio.h"
#include "Std_Types.h"

void ADC_Init(uint8 port, uint8 pin, uint8 channel, uint8 prescaler, uint8 mode_of_conversion,uint8 resolution,uint8 align,uint8 sampling_time);
uint16 ADC_Read(void);

#endif