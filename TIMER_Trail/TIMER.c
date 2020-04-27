/*
 * TIMER.c
 *
 *  Created on: ٢٥‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "TIMER.h"

 Gpt_ConfigChannel *g_Gpt_Configuration;

void TIMER0_init (void)
{
	//Waveform Generation Mode (normal or compare)
	TCCR0 &= 0xBF;
	TCCR0 |= ((0x01 & g_Gpt_Configuration->WGMode)<<WGM00) ;

	TCCR0 &= 0xF7;
	TCCR0 |= ((0x02 & g_Gpt_Configuration->WGMode)<<WGM01) ;

	//Compare Output Mode
	TCCR0 &= 0xCF;
	TCCR0 |= (g_Gpt_Configuration->COMode<<COM00) ;

	//Timer/Counter Interrupt
	TIMSK &= 0xFB;
	TIMSK |= (g_Gpt_Configuration->Int_Mode<<TOIE0) ;

	//non PWM mode
	TCCR0 |= (1<<FOC0) ;
}

void TIMER0_start (const uint8 Gpt_Value)
{
	switch(g_Gpt_Configuration->WGMode)
	{
	case GPT_WGMODE_NORMAL:
		// initial value
		TCNT0 = Gpt_Value;
		break;
	case GPT_WGMODE_CTC:
		// compare value
		OCR0 = Gpt_Value;
		break;
	default:
		// initial value
		TCNT0 = Gpt_Value;
		break;
	}

	//clock
	TCCR0 &= 0xF8;
	TCCR0 |= (g_Gpt_Configuration->Clock<<CS00) ;
}

void TIMER0_stop (void)
{
	//clock = 0;
	TCCR0 &= 0xF8;
}

void TIMER2_init (void)
{
	//Waveform Generation Mode (normal or compare)
	TCCR2 &= 0xBF;
	TCCR2 |= ((0x01 & g_Gpt_Configuration->WGMode)<<WGM20) ;

	TCCR2 &= 0xF7;
	TCCR2 |= ((0x02 & g_Gpt_Configuration->WGMode)<<WGM21) ;

	//Compare Output Mode
	TCCR2 &= 0xCF;
	TCCR2 |= (g_Gpt_Configuration->COMode<<COM20) ;

	//Timer2/Counter2 Interrupt
	TIMSK &= 0x3F;
	TIMSK |= (g_Gpt_Configuration->Int_Mode<<TOIE2) ;

	//non PWM mode
	TCCR2 |= (1<<FOC2) ;
}

void TIMER2_start (const uint8 Gpt_Value)
{
	switch(g_Gpt_Configuration->WGMode)
	{
	case GPT_WGMODE_NORMAL:
		// initial value
		TCNT2 = Gpt_Value;
		break;
	case GPT_WGMODE_CTC:
		// compare value
		OCR2 = Gpt_Value;
		break;
	default:
		// initial value
		TCNT2 = Gpt_Value;
		break;
	}

	//clock
	TCCR2 &= 0xF8;
	TCCR2 |= (g_Gpt_Configuration->Clock<<CS20) ;
}

void TIMER2_stop (void)
{
	//clock = 0;
	TCCR2 &= 0xF8;
}
