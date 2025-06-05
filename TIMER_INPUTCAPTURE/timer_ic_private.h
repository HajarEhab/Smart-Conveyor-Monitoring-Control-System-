//
// Created by hagar on 04/06/2025.
//

#ifndef TIMER_IC_PRIVATE_H
#define TIMER_IC_PRIVATE_H
#include "Std_Types.h"
#include "Bit_Operations.h"

#define TIM2_BASE       0x40000000
#define RCC_BASE        0x40023800

#define RCC_APB1ENR     (*((volatile uint32*)(RCC_BASE + 0x40)))
#define RCC_AHB1ENR     (*((volatile uint32*)(RCC_BASE + 0x30)))

#define TIM2_CR1        (*((volatile uint32*)(TIM2_BASE + 0x00)))
#define TIM2_CCMR1      (*((volatile uint32*)(TIM2_BASE + 0x18)))
#define TIM2_CCER       (*((volatile uint32*)(TIM2_BASE + 0x20)))
#define TIM2_CNT        (*((volatile uint32*)(TIM2_BASE + 0x24)))
#define TIM2_PSC        (*((volatile uint32*)(TIM2_BASE + 0x28)))
#define TIM2_ARR        (*((volatile uint32*)(TIM2_BASE + 0x2C)))
#define TIM2_CCR1       (*((volatile uint32*)(TIM2_BASE + 0x34)))
#define TIM2_DIER       (*((volatile uint32*)(TIM2_BASE + 0x0C)))
#define TIM2_SR         (*((volatile uint32*)(TIM2_BASE + 0x10)))
#define TIM2_EGR        (*((volatile uint32*)(TIM2_BASE + 0x14)))

// GPIOA base address and registers
#define GPIOA_MODER     (*((volatile uint32*)(0x40020000 + 0x00)))
#define GPIOA_AFRL      (*((volatile uint32*)(0x40020000 + 0x20)))

#define TIM2_EN         (1 << 0)
#define GPIOA_EN        (1 << 0)
#endif //TIMER_IC_PRIVATE_H
