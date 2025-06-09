#include "timer_ic.h"
#include "Gpio.h"
#include "Rcc.h"
#include "Std_Types.h"
#include "LCD.h"
#include "ADC.h"
#include "ADC_Private.h"
#include "Bit_Operations.h"

#include "PWM.h"
#include "IR_sensor/IR_sensor.h"
#include "EXTI.h"
#define continous_conv 1
#define sampling_time 4
#define resolution 0
#define align 0
#define prescaler 1

#define POT_PORT    GPIO_A
#define POT_PIN     1
#define POT_CHANNEL 1

#define THRESHOLD   2048
#include "Rcc_Private.h"
// LED Configuration - adjust according to your board
#define LED_PORT    GPIO_A
#define PULSES_PER_REV    1      // PULSES PER MOTOR REVOLUTION
#define TIMER_FREQ_HZ       1000000 // 1 MHz timer freq, Each tick = 1 µs → 1e-6 seconds
#define LED0_PORT GPIO_C
#define LED1_PORT GPIO_D
#define LED0_PIN  0
#define DISTANCE_PER_PULSE   0.1f         // 10 cm per pulse
#define MOTOR               9 //A9
#define EMERGENCY_BTN       3 //A3

void float_to_string(float num, char* str) {
    int int_part = (int)num;
    int frac_part = (int)((num - int_part) * 100);  // 2 decimal places

    // Handle negative numbers if needed
    if (frac_part < 0) frac_part = -frac_part;
    if (int_part < 0) {
        *str++ = '-';
        int_part = -int_part;
    }

    // Convert to string manually
    int i = 0;
    char temp[6];

    // Integer part
    do {
        temp[i++] = (int_part % 10) + '0';
        int_part /= 10;
    } while (int_part && i < 5);

    // Reverse it
    for (int j = i - 1; j >= 0; --j)
        *str++ = temp[j];

    *str++ = '.';

    // Fraction part (2 digits)
    *str++ = (frac_part / 10) + '0';
    *str++ = (frac_part % 10) + '0';

    *str = '\0';  // Null-terminate the string
}

// Modified emergency variables
volatile int emergency_flag = 0;
volatile int emergency_state = 0;  // 0 = normal, 1 = emergency

void EXTI3_IRQHandler(void) {
    // Clear interrupt pending bit
    SET_BIT(EXTI->PR, 3);  // Writing 1 clears it

    // Simple debounce delay
    for(volatile int i = 0; i < 50000; i++);

    // Toggle emergency state
    emergency_state = !emergency_state;
    emergency_flag = 1;
}

void GPIO_Init(void)
{
    Gpio_Init(LED0_PORT, LED0_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_WritePin(LED0_PORT, LED0_PIN, LOW);
    Gpio_Init(LED1_PORT, LED0_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL);
    Gpio_WritePin(LED1_PORT, LED0_PIN, LOW);
    // Set PB8 and PB9 as output push-pull
    Gpio_Init('B', 8, GPIO_OUTPUT, GPIO_PUSH_PULL);  // PB8
    Gpio_Init('B', 9, GPIO_OUTPUT, GPIO_PUSH_PULL);  // PB9
    Gpio_Init(GPIO_A,7,GPIO_INPUT,GPIO_PULL_UP);
    Gpio_Init(GPIO_A, EMERGENCY_BTN, GPIO_INPUT, GPIO_PULL_UP);
    Exti_Init(EXTI_PORT_A, EMERGENCY_BTN, EXTI_FALLING_EDGE);
    Gpio_WritePin('B', 9, 1);  // Set PB0 HIGH
    Gpio_WritePin('B', 8,0);
}

void Toggle_LED1(void)
{
    static uint8 led_state = HIGH;

    if(led_state == LOW)
    {
        Gpio_WritePin(LED0_PORT, LED0_PIN, HIGH);
        led_state = HIGH;
    }
    else
    {
        Gpio_WritePin(LED0_PORT, LED0_PIN, LOW);
        led_state = LOW;
    }
}

void Toggle_LED2(void)
{
    static uint8 led_state = HIGH;

    if(led_state == LOW)
    {
        Gpio_WritePin(LED1_PORT, LED0_PIN, HIGH);
        led_state = HIGH;
    }
    else
    {
        Gpio_WritePin(LED1_PORT, LED0_PIN, LOW);
        led_state = LOW;
    }
}

int main(void) {
    uint32 prev_capture = 0;
    float frequency = 0.0f;
    uint32 counter = 0;

    // Enable required clocks
    Rcc_Enable(RCC_GPIOA);
    Rcc_Enable(RCC_GPIOB);
    Rcc_Enable(RCC_GPIOC);
    Rcc_Enable(RCC_GPIOD);

    Rcc_Enable(RCC_TIM2);
    Rcc_Enable(RCC_TIM1);

    Rcc_Enable(RCC_ADC1);
    Rcc_Enable(RCC_SYSCFG);
    // Initialize system

    GPIO_Init();
    LCD_Init();
    Timer2_InputCapture_Init();
    ADC_Init(POT_PORT, POT_PIN, POT_CHANNEL, prescaler, continous_conv, resolution, align, sampling_time);
    IR_Sensor_Init();
    PWM_Init(2);         // CH2 = PA9 = TIM1_CH2
    PWM_Start();
    LCD_Clear_Display();

    LCD_SetCursorLocation(0, 0);
    LCD_WriteString((uint8 *)"Speed:");

    LCD_SetCursorLocation(1, 0);
    LCD_WriteString((uint8 *)"Motor:");

    while (1) {
        // Check if emergency flag is set
        if (emergency_flag) {
            emergency_flag = 0;  // Clear the flag

            if (emergency_state == 1) {
                // Enter emergency mode
                LCD_Clear_Display();
                LCD_SetCursorLocation(0, 0);
                LCD_WriteString((uint8 *)"EMERGENCY STOP");
                LCD_SetCursorLocation(1, 0);
                LCD_WriteString((uint8 *)"Press to Resume");

                // Stop PWM in emergency
                PWM_SetDutyCycle(0);
            } else {
                // Exit emergency mode - return to normal
                LCD_Clear_Display();
                LCD_SetCursorLocation(0, 0);
                LCD_WriteString((uint8 *)"Speed:");
                LCD_SetCursorLocation(1, 0);
                LCD_WriteString((uint8 *)"Motor:");
            }
        }

        // Only run normal operation if not in emergency state
        if (emergency_state == 0) {
            uint16 adc_val = ADC_Read();  // 0–4095
            if (adc_val > 4095) adc_val = 4095;

            uint8 pwm_val = ((uint32)adc_val * 255) / 4095;
            uint8 duty_percent = ((uint32)pwm_val * 100 + 127) / 255;
            if (duty_percent > 100) duty_percent = 100;

            PWM_SetDutyCycle(pwm_val);

            if (Timer2_IsCaptureFlagSet()) {
                Timer2_ClearCaptureFlag();

                uint32 curr_capture = Timer2_GetCapturedValue();
                Toggle_LED2();

                uint32 pulse_period = 0;
                if (curr_capture > prev_capture)
                    pulse_period = curr_capture - prev_capture;
                else
                    pulse_period = (0xFFFF - prev_capture) + curr_capture;

                prev_capture = curr_capture;

                if (pulse_period != 0)
                    frequency = (float) TIMER_FREQ_HZ/pulse_period;  // In Hz
                else
                    frequency = 0.0f;
            }

            // Convert values to strings
            char freq_str[10];
            char duty_str[6];
            char count_str[6];

            float_to_string(frequency, freq_str);
            float_to_string((float)duty_percent, duty_str);
            // IR object count
            counter = IR_Sensor_GetCount();
            utoa(counter, count_str);

            // ----------------- LCD Output ------------------

            // First line: SP:<val>m/s CN:<val>
            LCD_SetCursorLocation(0, 0);
            LCD_WriteString((uint8 *)"FQ:");
            LCD_WriteString((uint8 *)freq_str);
            LCD_WriteString((uint8 *)"Hz ");
            LCD_SetCursorLocation(0, 12);  // Leave space before CN
            LCD_WriteString((uint8 *)"CN:");
            LCD_WriteString((uint8 *)count_str);

            // Second line: MOT:<val>%
            LCD_SetCursorLocation(1, 0);
            LCD_WriteString((uint8 *)"MOT:");
            LCD_WriteString((uint8 *)duty_str);
            LCD_WriteString((uint8 *)"%   ");  // Padding spaces

            IR_Sensor_Manage();
        }
        // If in emergency_state == 1, the system stays stuck showing emergency message
        // until button is pressed again
    }
}