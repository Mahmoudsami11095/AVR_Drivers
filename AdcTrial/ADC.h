/*
 * ADC.h
 *
 *  Created on: ١٤‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

extern volatile uint16 g_adcValue;

typedef enum {
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	ADC_10X_0_0,
	ADC_10X_1_0,
	ADC_200X_0_0,
	ADC_200X_1_0,
	ADC_10X_2_2,
	ADC_10X_3_2,
	ADC_200X_2_2,
	ADC_200X_3_2,
	ADC_1X_0_1,
	ADC_1X_1_1,
	ADC_1X_2_1,
	ADC_1X_3_1,
	ADC_1X_4_1,
	ADC_1X_5_1,
	ADC_1X_6_1,
	ADC_1X_7_1,
	ADC_1X_0_2,
	ADC_1X_1_2,
	ADC_1X_2_2,
	ADC_1X_3_2,
	ADC_1X_4_2,
	ADC_1X_5_2,
	ADC_VBG,
	ADC_GND
}channel_num;

typedef enum {
	AREF,
	AVCC,
	Reserved,
	INTERNAL
}VRef_type;

typedef enum {
	DF2=1,
	DF4,
	DF8,
	DF16,
	DF32,
	DF64,
	DF128
}Prescaler_type;

typedef enum {
	INT_OFF,
	INT_ON
}Interrupt_Mode;

typedef enum {
	RIGHT_ADJUSTMENT,
	LEFT_ADJUSTMENT
}Data_Mode;

typedef enum {
	TRIGGER_OFF,
	TRIGGER_ON
}AutoTrigger_Mode;

typedef struct
{
	VRef_type VRef;
	Prescaler_type Divitionfactor;
	Interrupt_Mode IntMode;
	Data_Mode Adjustment;
	AutoTrigger_Mode TriggerMode;
}ADC_Config;

void ADC_init(const ADC_Config *ADC_Configuration);

void ADC_startConvertion (channel_num chnum);

uint16 ADC_readValue(void);

extern ADC_Config AdcConfg;

#endif /* ADC_H_ */
