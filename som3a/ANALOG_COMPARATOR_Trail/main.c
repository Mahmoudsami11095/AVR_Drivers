/*
 * main.c
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

#include "ANALOG_COMPARATOR.H"


int main (void)
{
	DDRC = 0xFF;

	AnalogCompartorConfiguration ACConfig ={ACM_ENABLE,AC_BG_DISABLE,ADC3,AC_INT_DISABLE,AC_INT_TOGGLE,AC_IC_DISABLE};

	ANALOG_COMARTOR_init(&ACConfig);

	ANALOG_COMARTOR_Start();

	while(1)
	{
		PORTC = ANALOG_COMARTOR_Output();
	}
	return 0;
}
