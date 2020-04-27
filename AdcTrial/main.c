/*
 * main.c
 *
 *  Created on: ١٤‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "ADC.h"

int main (void)
{
	ADC_Config AdcConfg = {AVCC,DF8,INT_OFF,RIGHT_ADJUSTMENT,TRIGGER_OFF};
	ADC_init(&AdcConfg);
	SREG |= (1<<7);/* Enable Global Interrupts */

	DDRC = 0xFF;
	DDRD = 0x03;

	while(1)
	{
		ADC_startConvertion(ADC_1X_3_2);
		if( (AdcConfg.IntMode) == INT_OFF)
		{
			g_adcValue = ADC_readValue();
		}
		else
		{
			//value will be set by interrupt
		}
		PORTC =g_adcValue;
		PORTD =g_adcValue>>8;
	}
}
