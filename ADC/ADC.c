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

void  ADC_Init(uint8 port, uint8 pin, uint8 channel, uint8 prescaler, uint8 mode_of_conversion,uint8 resolution,uint8 align,uint8 sampling_time) {
    
    //initialize the GPIO pin for analog mode
    Gpio_Init(port, pin, GPIO_ANALOG, GPIO_NO_PULL_DOWN);

    // Enable ADC clock
    Rcc_Enable(RCC_ADC1);

    // Configure ADC1
    ADC1->CR1 = 0; // Reset CR1
    ADC1->CR2 = 0; // Reset CR2
    ADC1->CR2 |= (1 << 0);   // ADON
  
    for (volatile int i = 0; i < 1000; i++); // Delay for ADC stabilization

    ADC1->CR2 |= (mode_of_conversion << 1); // Set mode of conversion
    ADC1->CR1 |= (resolution << 24); // Set resolution
    ADC1->CR2 |= (align << 11); // Set data alignment
    ADC1->CR1 |= (prescaler << 16); // Set prescaler
    if (channel >9){
        ADC1->SMPR1 &= ~(0x7 << (channel * 3)); // Clear previous sampling time for the channel
        ADC1->SMPR1 |=(sampling_time << (channel*3)); // Set sampling time for internal channels
    }
    else
    {
        ADC1->SMPR2 &= ~(0x7 << (channel * 3)); // Clear previous sampling time for the channel
        ADC1->SMPR2 |= (sampling_time << (channel * 3)); // Set sampling time for external channels
    }


    // remove the comment if it didnot work
    ADC1->SQR1 &= ~(0xF << 20);
    ADC1->SQR3 &= ~0x1F;
    ADC1->SQR3 |= channel; // Set the channel in SQR3
    

}
uint16 ADC_Read(void) {
    // Start conversion
    ADC1->CR2 |= (1 << 30); 

    // Wait for conversion to complete (EOC bit = 1)
    while (!(ADC1->SR & (1 << 1)));

    // Read the result
    return ADC1->DR;
}


















