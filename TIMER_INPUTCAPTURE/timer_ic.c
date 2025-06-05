#include "timer_ic.h"
#include "timer_ic_private.h"

void Timer2_InputCapture_Init(void)
{
    // Enable clock for GPIOA and TIM2
    RCC_AHB1ENR |= GPIOA_EN;
    RCC_APB1ENR |= TIM2_EN;

    // Configure PA0 as alternate function (AF1 for TIM2_CH1)
    GPIOA_MODER &= ~(0x3 << (0 * 2));
    GPIOA_MODER |=  (0x2 << (0 * 2));     // AF mode
    GPIOA_AFRL  &= ~(0xF << (0 * 4));
    GPIOA_AFRL  |=  (0x1 << (0 * 4));     // AF1 = TIM2

    // Timer configuration
    TIM2_PSC = 84 - 1;   // Prescaler to count at 1 MHz
    TIM2_ARR = 0xFFFF;   // Max ARR

    // Configure CH1 as input, mapped to TI1
    TIM2_CCMR1 &= ~(0x03 << 0);
    TIM2_CCMR1 |=  (0x01 << 0);           // CC1S = 01


    // Capture on rising edge
    TIM2_CCER &= ~(1 << 1);               // CC1P = 0
    TIM2_CCER |= (1 << 0);                // CC1E = 1


    TIM2_DIER &= ~(1 << 1);

    // Force timer reset and start
    TIM2_CR1 &= ~(1 << 0);      // Disable timer
    TIM2_CNT = 0;               // Clear counter
    TIM2_CR1 |=  (1 << 0);      // Enable timer
    TIM2_EGR |= (1 << 0);

}

uint32 Timer2_GetCapturedValue(void)
{
    return TIM2_CCR1;
}

void Timer2_Enable(void)
{
    TIM2_CR1 |= (1 << 0);
}

void Timer2_Disable(void)
{
    TIM2_CR1 &= ~(1 << 0);
}
void Timer2_ClearCaptureFlag(void)
{
    // Clear the CC1IF flag (bit 1 in TIM2_SR)
    TIM2_SR &= ~(1 << 1);
}
uint8 Timer2_IsCaptureFlagSet(void)
{
    return (TIM2_SR & (1 << 1)) != 0;
}
