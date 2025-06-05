//
// Created by Admin on 5/15/2025.
//

#ifndef LCD_H
#define LCD_H

#include "Gpio.h"

#define LCD_FunctionSet8bit   0x38
#define LCD_DisplayOn         0x0C
#define LCD_ClearDisplay      0x01
#define LCD_EntryMode         0x06
#define DDR_ADDRESS           0x80

#define LCD_RS_PORT GPIO_A
#define LCD_RS_PIN  0

#define LCD_RW_PORT GPIO_A
#define LCD_RW_PIN  1

#define LCD_E_PORT  GPIO_A
#define LCD_E_PIN   2

#define LCD_DATA_PORT GPIO_B   // All 8 data lines connected to GPIOB 0-7

void delay_ms(unsigned int ms);
void LCD_Write8Bit(uint8 port, uint8 data);
void LCD_SendCommand(uint8 copy_u8Command);
void LCD_SendData(uint8 copy_u8Data);
void LCD_Init(void);
void LCD_Clear_Display(void);
void LCD_SetCursorLocation(uint8 row, uint8 col);
void LCD_WriteString(uint8 *str);



#endif //LCD_H
