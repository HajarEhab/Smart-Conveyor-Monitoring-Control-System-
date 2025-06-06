#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H
#include "Std_Types.h"

#define ADC_BASE       0x40012300
#define ADC_COMMON     ((ADC_Common_TypeDef *)ADC_BASE)

#define ADC1_BASE  0x40012000
#define ADC1            ((ADC_TypeDef *)ADC1_BASE)
typedef struct {
    volatile uint32 SR;
    volatile uint32 CR1;
    volatile uint32 CR2;
    volatile uint32 SMPR1;
    volatile uint32 SMPR2;
    volatile uint32 JOFR1;
    volatile uint32 JOFR2;
    volatile uint32 JOFR3;
    volatile uint32 JOFR4;
    volatile uint32 HTR;
    volatile uint32 LTR;
    volatile uint32 SQR1;
    volatile uint32 SQR2;
    volatile uint32 SQR3;
    volatile uint32 JSQR;
    volatile uint32 JDR1;
    volatile uint32 JDR2;
    volatile uint32 JDR3;
    volatile uint32 JDR4;
    volatile uint32 DR;
} ADC_TypeDef;


typedef struct {
    volatile uint32 CSR;   // Status register
    volatile uint32 CCR;   // Common control register (contains ADCPRE)
    volatile uint32 CDR;   // Common regular data register for dual mode
} ADC_Common_TypeDef;









#endif //ADC_PRIVATE_H
