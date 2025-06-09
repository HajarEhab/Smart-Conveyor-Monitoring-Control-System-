#include "Std_Types.h"
#include "Gpio.h"
#include "ADC.h"
#include "ADC_Private.h"
#include "RCC.h"

// channel: 0-18 0=>15 external channels, 16-18 => internal channels
// prescaler: 0-7
// mode_of_conversion: 0 for single conversion, 1 for continuous conversion
// resolution: 0 for 12-bit, 1 for 10-bit, 2 for 8-bit, 3 for 6-bit
// align: 0 for right alignment, 1 for left alignment
// sampling_time: 0-7 (0 for 3.5 cycles, 1 for 7.5 cycles, ..., 7 for 601.5 cycles)

void ADC_Init(uint8 port, uint8 pin, uint8 channel, uint8 prescaler, uint8 mode_of_conversion, uint8 resolution, uint8 align, uint8 sampling_time) {
    // 1. Initialize GPIO pin as analog
    Gpio_Init(port, pin, GPIO_ANALOG, GPIO_NO_PULL_DOWN);

    // 2. Enable ADC1 clock
    Rcc_Enable(RCC_ADC1);

    // 3. Reset CR1 and CR2
    ADC1->CR1 = 0;
    ADC1->CR2 = 0;

    // 4. Set resolution (CR1[25:24])
    ADC1->CR1 |= (resolution << 24);

    // 5. Set data alignment (CR2[11])
    if (align)
        ADC1->CR2 |= (1 << 11);
    else
        ADC1->CR2 &= ~(1 << 11);

    // 6. Set continuous or single conversion mode (CR2[1])
    if (mode_of_conversion)
        ADC1->CR2 |= (1 << 1); // Continuous
    else
        ADC1->CR2 &= ~(1 << 1); // Single

    // 7. Enable EOCS (CR2[10]) to end each conversion
    ADC1->CR2 |= (1 << 10);

    // 8. Set ADC prescaler (ADC->CCR[17:16])
    ADC_COMMON->CCR &= ~(0x3 << 16);
    ADC_COMMON->CCR |= ((prescaler & 0x3) << 16); // Only bits 0-3 are valid

    // 9. Set sampling time
    if (channel <= 9) {
        ADC1->SMPR2 &= ~(0x7 << (channel * 3));
        ADC1->SMPR2 |= (sampling_time << (channel * 3));
    } else {
        ADC1->SMPR1 &= ~(0x7 << ((channel - 10) * 3));
        ADC1->SMPR1 |= (sampling_time << ((channel - 10) * 3));
    }

    // 10. Set conversion sequence length = 1
    ADC1->SQR1 &= ~(0xF << 20);

    // 11. Set first conversion in regular sequence
    ADC1->SQR3 &= ~0x1F;
    ADC1->SQR3 |= (channel & 0x1F);

    // 12. Finally, enable ADC (ADON = 1)
    ADC1->CR2 |= (1 << 0);
}

uint16 ADC_Read(void) {
    // Start conversion
    ADC1->CR2 |= (1 << 30); 

    // Wait for conversion to complete (EOC bit = 1)
    while (!(ADC1->SR & (1 << 1)));

    // Read the result
    return ADC1->DR;
}


















