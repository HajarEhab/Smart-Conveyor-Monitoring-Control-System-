#ifndef TIMER_IC_H
#define TIMER_IC_H

#include "Std_Types.h"

void Timer2_InputCapture_Init(void);      // Initializes Timer2 in input capture mode
uint32 Timer2_GetCapturedValue(void);     // Gets captured value (duration/pulse width)
void Timer2_Enable(void);
void Timer2_Disable(void);
void Timer2_ClearCaptureFlag(void);
uint8 Timer2_IsCaptureFlagSet(void);

#endif
