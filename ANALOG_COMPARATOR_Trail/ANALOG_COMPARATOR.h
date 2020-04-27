/*
 * ANALOG_COMPARATOR.h
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#ifndef ANALOG_COMPARATOR_H_
#define ANALOG_COMPARATOR_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

typedef enum {
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
}AnalogComparatorNegativeInputMode;

typedef enum{
	ACM_DISABLE,
	ACM_ENABLE
}AnalogComparatorMultiplexerMode;

typedef enum{
	AC_ENABLE,
	AC_DISABLE
}AnalogComparatorMode;

typedef enum{
	AC_BG_DISABLE,
	AC_BG_ENABLE
}AnalogComparatorBandgapMode;

typedef enum{
	AC_INT_DISABLE,
	AC_INT_ENABLE
}AnalogComparatorInterruptMode;

typedef enum{
	AC_INT_TOGGLE,
	AC_INT_FALLING=2,
	AC_INT_RISING
}AnalogComparatorInterruptType;

typedef enum{
	AC_IC_DISABLE,
	AC_IC_ENABLE
}AnalogComparatorInputCaptureMode;

typedef struct{
	AnalogComparatorMultiplexerMode ACMultiplexerMode;
	AnalogComparatorBandgapMode ACBandgapMode;
	AnalogComparatorNegativeInputMode ACNegativeInputMode;
	AnalogComparatorInterruptMode ACInterruptMode;
	AnalogComparatorInterruptType ACInterruptType;
	AnalogComparatorInputCaptureMode ACInputCaptureMode;
}AnalogCompartorConfiguration;

void ANALOG_COMARTOR_init (const AnalogCompartorConfiguration * ACConfiguration);
void ANALOG_COMARTOR_Start ();
uint8 ANALOG_COMARTOR_Output ();
void ANALOG_COMARTOR_Stop ();


extern AnalogCompartorConfiguration ACConfig;

#endif /* ANALOG_COMPARATOR_H_ */
