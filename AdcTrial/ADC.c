/*
 * ADC.c
 *
 *  Created on: ١٤‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "ADC.h"
volatile uint16 g_adcValue=0;

ISR(ADC_vect)
{
    if (ADMUX & (1<<ADLAR) )
    {
    	g_adcValue = ADC>>6;
    }
    else
    {
    	g_adcValue = ADC;
    }
}

void ADC_init(const ADC_Config *ADC_Configuration){
	// ADCMUX Single CH0
	ADMUX = ADMUX & 0xE0;
	//VREF internal vref=2.5v
	ADMUX = ADMUX | (ADC_Configuration->VRef<<REFS0);
	// LEFT ADCJUst
	ADMUX = ADMUX | (ADC_Configuration->Adjustment<<ADLAR);
	//ADC PRESCALER 1MHZ/8
	ADCSRA = ADCSRA | (ADC_Configuration->Divitionfactor<<ADPS0);
	//interrupt
	ADCSRA = ADCSRA | (ADC_Configuration->IntMode<<ADIE);
	//Free Running (not trigger)
	ADCSRA = ADCSRA | (ADC_Configuration->TriggerMode<<ADATE);
	SFIOR &= ~(0xE0);
	//ADC Enable
	ADCSRA = ADCSRA | (1<<ADEN);
}



uint16 ADC_readValue(void)
{
	uint16 retval =0;
	//check flag for complete conversion
	while (!(ADCSRA & (1<<ADIF))){};
	//clear flag
	ADCSRA = ADCSRA | (1<<ADIF);
	//return value ADC register
    if (ADMUX & (1<<ADLAR) )
    {
    	retval = ADC>>6;
    }
    else
    {
    	retval = ADC;
    }
    return retval;
}

void ADC_startConvertion (channel_num chnum)
{
	// ADCMUX Single CH0
	ADMUX = (ADMUX & 0xE0) |  chnum;

	//start conversion
	ADCSRA = ADCSRA | (1<<ADSC);
}
