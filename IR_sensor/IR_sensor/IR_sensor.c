//
// Created by Karim_ebrahim on 6/7/2025.
//
#include "IR_sensor.h"
#include "Gpio.h"

// === Static IR Detection Variables ===

static uint8 prev_state = 1;
static uint16 object_count = 0;

// === IR Sensor Logic ===
void IR_Sensor_Init(void) {
    Gpio_Init(IR_SENSOR_GPIO_PORT, IR_SENSOR_PIN, GPIO_INPUT, GPIO_PULL_UP);
    prev_state = Gpio_ReadPin(IR_SENSOR_GPIO_PORT, IR_SENSOR_PIN);
    object_count = 0;
}
void IR_Sensor_Manage(void) {
    uint8 current_state = Gpio_ReadPin(IR_SENSOR_GPIO_PORT, IR_SENSOR_PIN);

    if (prev_state == 1 && current_state == 0) {

            object_count++;

    }

    prev_state = current_state;
}

uint16 IR_Sensor_GetCount(void) {
    return object_count;
}

void IR_Sensor_ResetCount(void) {
    object_count = 0;
}



void utoa(uint16 num, char* str) {
    uint8 i = 0;
    char temp[6];

    if (num == 0) {
        str[i++] = '0';
    } else {
        while (num > 0) {
            temp[i++] = (num % 10) + '0';
            num /= 10;
        }
    }

    // Reverse the string
    for (uint8 j = 0; j < i; ++j) {
        str[j] = temp[i - j - 1];
    }
    str[i] = '\0';
}







