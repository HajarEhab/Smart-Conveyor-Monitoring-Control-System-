//
// Created by Admin on 5/8/2025.
//

#ifndef EXTI_H
#define EXTI_H
#include "Std_Types.h"
#include "EXTI_private.h"
// Trigger Types
#define EXTI_RISING_EDGE     0
#define EXTI_FALLING_EDGE    1
#define EXTI_BOTH_EDGES      2

// Port Sources (SYSCFG_EXTICR values)
#define EXTI_PORT_A      0x0
#define EXTI_PORT_B      0x1
#define EXTI_PORT_C      0x2
#define EXTI_PORT_D      0x3
#define EXTI_PORT_E      0x4

void Exti_Init(uint8 PortName, uint8 PinNumber, uint8 TriggerType);
void Exti_Enable(uint8 PinNumber);
void Exti_Disable(uint8 PinNumber);
#endif //EXTI_H
