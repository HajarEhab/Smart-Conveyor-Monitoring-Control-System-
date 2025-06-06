#include "PWM.h"
#include "Gpio.h"
#include "RCC.h"
#include "PWM_Private.h"
#include "Std_Types.h"

void PWM_Init(uint8 port, uint8 pin) {
    // Example: TIM2, Channel 1 -> PA0 (AF1)
    Gpio_Init(port, pin, GPIO_AF, GPIO_PUSH_PULL);  // You may need to set AF1 manually for PA0

    Rcc_Enable(RCC_TIM1);  // Assuming TIM2 is used

    // Disable timer
    TIM1->CCR1 = 0;

    // Set PWM mode 1 on channel 1
    TIM1->CCMR1 |= (6 << 4);  // PWM mode 1
    TIM1->CCMR1 |= (1 << 3);  // Enable preload

    TIM1->CCER |= (1 << 0);   // Enable output for channel 1

    TIM1->PSC = 84 - 1;  // Assuming 84 MHz clock -> 1 MHz timer clock
    TIM1->ARR = 255 ; // 256 steps for duty cycle resolution (1% each)
    TIM1->CCR1 = 0;      // Initial duty cycle 0%

    TIM1->EGR |= (1 << 0); // Generate update event
    TIM1->CR1 |= (1 << 0); // Enable timer
}

void PWM_SetDutyCycle(uint8 channel, uint8 duty_cycle) {
    if (duty_cycle > 255) duty_cycle = 255;

    TIM1->CCR1 = duty_cycle;  // Channel 1
}
