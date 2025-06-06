#include "Bit_Operations.h"
#include "RCC.h"
#include "Gpio.h"
#include"LCD.h"
#include "ADC.h"
#include "ADC_Private.h"
#include "EXTI.h"
#define MOTOR               4 //A0
#define EMERGENCY_BTN       3 //A3


int emergency_flag = 0;
void EXTI3_IRQHandler(void) {
    // Clear interrupt pending bit
    SET_BIT(EXTI->PR, 3);  // Writing 1 clears it

    // Set flag
    emergency_flag = 1;
}

int main()
{
    Rcc_Init();
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_SYSCFG);
    // Initialize LCD
    LCD_Init();
    GPIO_Init(GPIO_A, MOTOR , GPIO_OUTPUT, GPIO_PUSH_PULL);
    GPIO_Init(GPIO_A, EMERGENCY_BTN, GPIO_INPUT, GPIO_PULL_UP);
    Exti_Init(EXTI_PORT_A, EMERGENCY_BTN, EXTI_FALLING_EDGE);
    // testing with a led
    GPIO_WritePin(GPIO_A, MOTOR, HIGH);

    while (1) {
        // tested LCD working
        // Set initial messages
        LCD_SetCursorLocation(0, 0);
        LCD_WriteString((uint8 *)"Motor Speed:");  // Display static text temporarily to be modified later
        //delay_ms(2000); // Wait to view the message
        LCD_SetCursorLocation(1, 0);
        LCD_WriteString((uint8 *)"PWM = 75%");  // Display static text temporarily to be modified later
        if (emergency_flag) {
            GPIO_WritePin(GPIO_A, MOTOR, LOW);  // Turn off motor
            LCD_Clear_Display();
            LCD_WriteString((uint8 *)"EMERGENCY STOP");
            delay_ms(1000);
            emergency_flag = 0;
            LCD_Clear_Display();
            GPIO_WritePin(GPIO_A, MOTOR, HIGH);  // Turn on motor again

        }


    }
    return 0;
}