/**
* Gpio.c
 *
 *  Created on: 4/15/2025
 
 */

#include <stdint.h>
#include <Std_Types.h>
#include "Gpio.h"
#include "Utils.h"
#include "Bit_Operations.h"
#include "Gpio_Private.h"

void Gpio_Init(uint8 PortName, uint8 PinNumber, uint8 PinMode, uint8 DefaultState) {
    switch (PortName) {
        case GPIO_A:
            // TODO:
            GPIOA_MODER &= ~(0x03 << (PinNumber * 2));// Clear mode bits
            GPIOA_MODER |= (PinMode << (PinNumber * 2)); // Set mode

            if (PinMode == GPIO_INPUT) {
             GPIOA_PUPDR &= ~(0x03 << (PinNumber * 2));// Clear
             GPIOA_PUPDR |= (DefaultState << (PinNumber * 2));
         } else {
             GPIOA_OTYPER  &=~(0x1 << PinNumber);
             GPIOA_OTYPER  |= (DefaultState << (PinNumber));
         }
                break;
        case GPIO_B:
            GPIOB_MODER &= ~(0x03 << (PinNumber * 2));
        GPIOB_MODER |= (PinMode << (PinNumber * 2));

        if (PinMode == GPIO_INPUT) {
            GPIOB_PUPDR &= ~(0x03 << (PinNumber * 2));
            GPIOB_PUPDR |= (DefaultState << (PinNumber * 2));
        } else {
            GPIOB_OTYPER  &=~(0x1 << PinNumber);
            GPIOB_OTYPER  |= (DefaultState << (PinNumber));
            // if (DefaultState == GPIO_PUSH_PULL) {
            //     CLEAR_BIT(GPIOB_OTYPER, PinNumber);
            // }else if (DefaultState == GPIO_OPEN_DRAIN) {
            //     SET_BIT(GPIOB_OTYPER, PinNumber);
            // }
        }
        break;
        case GPIO_C:
            // TODO:
                GPIOC_MODER &= ~(0x03 << (PinNumber * 2));
             GPIOC_MODER |= (PinMode << (PinNumber * 2));

             if (PinMode == GPIO_INPUT) {
                 GPIOC_PUPDR &= ~(0x03 << (PinNumber * 2));
                 GPIOC_PUPDR |= (DefaultState << (PinNumber * 2));
             } else {
                 GPIOC_OTYPER  &=~(0x1 << PinNumber);
                 GPIOC_OTYPER  |= (DefaultState << (PinNumber));
             }
                 break;
        case GPIO_D:
            // TODO:
            GPIOD_MODER &= ~(0x03 << (PinNumber * 2));
            GPIOD_MODER |= (PinMode << (PinNumber * 2));

            if (PinMode == GPIO_INPUT) {
             GPIOD_PUPDR &= ~(0x03 << (PinNumber * 2));
             GPIOD_PUPDR |= (DefaultState << (PinNumber * 2));
          } else {
             GPIOD_OTYPER  &=~(0x1 << PinNumber);
             GPIOD_OTYPER  |= (DefaultState << (PinNumber));
        }
                break;
        default:
            break;
    }

}

uint8 Gpio_WritePin(uint8 PortName, uint8 PinNumber, uint8 Data) {
    switch (PortName) {
        case GPIO_A:
            if (((GPIOA_MODER >> (PinNumber * 2)) & 0x03) != GPIO_OUTPUT)
                return NOK;
        GPIOA_ODR &= ~(1 << PinNumber);// Clear the pin
        GPIOA_ODR |= (Data << PinNumber);// Set the pin
        break;

        case GPIO_B:
            if (((GPIOB_MODER >> (PinNumber * 2)) & 0x03) != GPIO_OUTPUT)
                return NOK;
        GPIOB_ODR &= ~(1 << PinNumber);// Clear the pin
        GPIOB_ODR |= (Data << PinNumber);// Set the pin
        break;

        case GPIO_C:
            if (((GPIOC_MODER >> (PinNumber * 2)) & 0x03) != GPIO_OUTPUT)
                return NOK;
        GPIOC_ODR &= ~(1 << PinNumber);
        GPIOC_ODR |= (Data << PinNumber);
        break;

        case GPIO_D:
            if (((GPIOD_MODER >> (PinNumber * 2)) & 0x03) != GPIO_OUTPUT)
                return NOK;
        GPIOD_ODR &= ~(1 << PinNumber);
        GPIOD_ODR |= (Data << PinNumber);
        break;

        default:
            return NOK;
    }

    return OK;
}

uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNumber) {
    switch (PortName) {
        case GPIO_A:
            return (GPIOA_IDR >> PinNumber) & 0x01;
        case GPIO_B:
            return (GPIOB_IDR >> PinNumber) & 0x01;
        case GPIO_C:
            return (GPIOC_IDR >> PinNumber) & 0x01;
        case GPIO_D:
            return (GPIOD_IDR >> PinNumber) & 0x01;
        default:
           break;
    }
    return 0;
}
