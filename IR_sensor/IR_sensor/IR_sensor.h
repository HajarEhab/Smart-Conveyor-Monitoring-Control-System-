//
// Created by Karim_ebrahim on 6/7/2025.
//

#ifndef IR_SENSOR_H
#define IR_SENSOR_H
#include "Std_Types.h"

// === CONFIGURATION ===
#define IR_SENSOR_GPIO_PORT    GPIO_A
#define IR_SENSOR_PIN          7

// IR Functions

void IR_Sensor_Init(void);
void IR_Sensor_Manage(void);
uint16 IR_Sensor_GetCount(void);
void IR_Sensor_ResetCount(void);


// Conversion Function
void utoa(uint16 num, char* str);

#endif //IR_SENSOR_H


