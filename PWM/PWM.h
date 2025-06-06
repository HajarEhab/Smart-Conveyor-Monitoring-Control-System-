#ifndef PWM_H
#define PWM_H

#include "Std_Types.h"

void PWM_Init(uint8 port, uint8 pin);
void PWM_SetDutyCycle( uint8 duty_cycle);  // 0-255

#endif
