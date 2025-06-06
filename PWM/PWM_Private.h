#ifndef PWM_PRIVATE_H
#define PWM_PRIVATE_H

#include "Std_Types.h"

#define TIM1_BASE 0x40010000

typedef struct {
    volatile uint32 CR1;
    volatile uint32 CR2;
    volatile uint32 SMCR;
    volatile uint32 DIER;
    volatile uint32 SR;
    volatile uint32 EGR;
    volatile uint32 CCMR1;
    volatile uint32 CCMR2;
    volatile uint32 CCER;
    volatile uint32 CNT;
    volatile uint32 PSC;
    volatile uint32 ARR;
    volatile uint32 RCR;
    volatile uint32 CCR1;
    volatile uint32 CCR2;
    volatile uint32 CCR3;
    volatile uint32 CCR4;
    volatile uint32 BDTR;
    volatile uint32 DCR;
    volatile uint32 DMAR;
} TIM_TypeDef;

#define TIM1 ((volatile TIM_TypeDef *) TIM1_BASE)

#endif
