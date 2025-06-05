//
// Created by Admin on 5/15/2025.
//
#include "Gpio.h"
#include "LCD.h"
#include <stdint.h>

void delay_ms(unsigned int ms) {
    for (unsigned int i = 0; i < ms * (1000000/1000); i++) {

    }
}

void LCD_Write8Bit(uint8 port, uint8 data) {
    for (uint8_t i = 0; i < 8; i++) {
        uint8_t bit = (data >> i) & 0x01;
        GPIO_WritePin(port, i, bit);
    }
}

void LCD_SendCommand(uint8 copy_u8Command) {
    GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, 0);  // RS = 0 for command
    GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, 0);  // RW = 0 for write
    GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, 1);

    LCD_Write8Bit(LCD_DATA_PORT, copy_u8Command);

    delay_ms(2);

    GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, 0);
    delay_ms(10);
}

void LCD_SendData(uint8 copy_u8Data) {
    GPIO_WritePin(LCD_RS_PORT, LCD_RS_PIN, 1);  // RS = 1 for data
    GPIO_WritePin(LCD_RW_PORT, LCD_RW_PIN, 0);
    GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, 1);

    LCD_Write8Bit(LCD_DATA_PORT, copy_u8Data);

    delay_ms(2);

    GPIO_WritePin(LCD_E_PORT, LCD_E_PIN, 0);
    delay_ms(10);
}

void LCD_Init(void) {
    // Configure control pins
    GPIO_Init(LCD_RS_PORT, LCD_RS_PIN,GPIO_OUTPUT, GPIO_PUSH_PULL);
    GPIO_Init(LCD_RW_PORT, LCD_RW_PIN,GPIO_OUTPUT, GPIO_PUSH_PULL);
    GPIO_Init(LCD_E_PORT,  LCD_E_PIN,GPIO_OUTPUT,  GPIO_PUSH_PULL);
    // Configure Data pins
    for (int i = 0; i < 8; i++) {
        GPIO_Init(LCD_DATA_PORT, i,GPIO_OUTPUT, GPIO_PUSH_PULL);
    }

    delay_ms(30);
    LCD_SendCommand(LCD_FunctionSet8bit);
    LCD_SendCommand(LCD_DisplayOn);
    LCD_SendCommand(LCD_ClearDisplay);
    LCD_SendCommand(LCD_EntryMode);
}

void LCD_Clear_Display(void) {
    LCD_SendCommand(LCD_ClearDisplay);
}

void LCD_SetCursorLocation(uint8 row, uint8 col) {
    if (col < 16) {
        switch (row) {
        case 0:
            LCD_SendCommand(DDR_ADDRESS + col);
            break;
        case 1:
            LCD_SendCommand(DDR_ADDRESS + 0x40 + col);
            break;
        }
    }
}

void LCD_WriteString(uint8 *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}
