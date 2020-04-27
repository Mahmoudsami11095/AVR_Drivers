/*
 * PWM.c
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "PWM.h"

PWM_ConfigChannel *g_PWM_Configuration;

void PWM_init (void)
{
	SET_BIT(DDRB,PB3);

	//Waveform Generation Mode (fast or phase correct)
	TCCR0 &= 0xBF;
	TCCR0 |= ((0x01 & g_PWM_Configuration->PWMMode)<<WGM00) ;

	TCCR0 &= 0xF7;
	TCCR0 |= ((0x02 & g_PWM_Configuration->PWMMode)<<WGM01) ;

	//Compare Output Mode , FAST PWM Mode
	TCCR0 &= 0xCF;
	TCCR0 |= (g_PWM_Configuration->COMode<<COM00) ;

	//Timer/Counter Interrupt
	TIMSK &= 0xFB;
	TIMSK |= (g_PWM_Configuration->Int_Mode<<TOIE0) ;

	//PWM mode
	TCCR0 &= ~(1<<FOC0) ;
}

void PWM_start (const uint8 PWM_Value)
{
	// initial value
	TCNT0 = 0 ;

	// compare value
	OCR0 = PWM_Value;

	//clock
	TCCR0 &= 0xF8;
	TCCR0 |= (g_PWM_Configuration->PWMClock<<CS00) ;
}

void PWM_stop (void)
{
	//clock = 0;
	TCCR0 &= 0xF8;
}
