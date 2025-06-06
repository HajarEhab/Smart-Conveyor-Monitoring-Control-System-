Smart Conveyor Monitoring & Control System (Proteus Simulation)  
Project Overview  
this project simulates a smart conveyor system using an ARM Cortex-M microcontroller . the system measures conveyor speed using timer capture , controls motor speed via a potentiometer , detects passing objects , and displays all relevant information on an LCD . it also includes an emergency stop feature triggered by an interrupt .  

System Requirements & Constraints  
1. Speed Measurement (Timer Capture + Function Generator)  
● Use a function generator in Proteus to simulate pulse signals.  
● Measure the time between two rising edges using Timer Input Capture mode.  
● Do not use interrupts for pulse edge detection.  

2. Motor Speed Control (Potentiometer + PWM)  
● Connect a potentiometer to an ADC channel.  
● Generate a PWM signal based on the ADC value to control motor speed.  
● Display the motor speed (as a percentage) on the LCD.  

3. Object Detection (Software-Based Edge Detection)  
● Simulate an IR sensor as a digital input.  
● Implement falling-edge detection in software only (polling; no interrupt).  
● Count each passing object and update the display.  

4. Emergency Stop (Interrupt-Based Button)  
● Use a push button to simulate an emergency stop.  
● Detect button press via external interrupt only.  
● On trigger, stop the motor and show “EMERGENCY STOP” message on LCD.  
● No debouncing required.  

5. Display Interface  
● Use a 16x2 LCD to display:  
○ Conveyor speed  
○ Motor speed (PWM %)  
○ Object count  
○ Emergency status  
