//
// Created by Admin on 5/8/2025.
//
#include "Exti.h"
#include "Bit_Operations.h"
#include "Std_Types.h"
#include "Exti_Private.h"
#include "Rcc.h"

void Exti_Init(uint8 PortName, uint8 PinNumber, uint8 TriggerType) {
    Rcc_Enable(RCC_SYSCFG);

    // 2. Configure GPIO port selection in SYSCFG_EXTICR
    uint8 regIndex = PinNumber / 4;
    uint8 bitPos = (PinNumber % 4) * 4;

    // Clear and set the appropriate bits in SYSCFG_EXTICR
    SYSCFG->EXTICR[regIndex] &= ~(0x0F << bitPos);
    SYSCFG->EXTICR[regIndex] |= (PortName << bitPos);


    // 4. Configure trigger
    if (TriggerType == EXTI_RISING_EDGE) {
        SET_BIT(EXTI->RTSR, PinNumber);
        CLEAR_BIT(EXTI->FTSR, PinNumber);
    } else if (TriggerType == EXTI_FALLING_EDGE) {
        SET_BIT(EXTI->FTSR, PinNumber);
        CLEAR_BIT(EXTI->RTSR, PinNumber);
    } else if (TriggerType == EXTI_BOTH_EDGES) {
        SET_BIT(EXTI->RTSR, PinNumber);
        SET_BIT(EXTI->FTSR, PinNumber);
    }
    // 5. Enable the corresponding NVIC interrupt
    if (PinNumber <= 4) {
        SET_BIT(NVIC->NVIC_ISER[0], 6 + PinNumber);  // EXTI0_IRQn = 6
    } else if (PinNumber <= 9) {
        SET_BIT(NVIC->NVIC_ISER[0], 23);             // EXTI9_5_IRQn = 23
    } else if (PinNumber <= 15) {
        SET_BIT(NVIC->NVIC_ISER[1], 40 - 32);        // EXTI15_10_IRQn = 40 (ISER[1])
    }
    Exti_Enable(PinNumber);
}

void Exti_Enable(uint8 PinNumber) {
    SET_BIT(EXTI->IMR, PinNumber);
}

void Exti_Disable(uint8 PinNumber) {
    CLEAR_BIT(EXTI->IMR, PinNumber);
}

