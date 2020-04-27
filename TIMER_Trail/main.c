/*
 * main.c
 *
 *  Created on: ٢٥‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "TIMER.h"


int main (void)
{
	uint8 tick = 0;
	uint8 tick2 = 0;

	Gpt_ConfigChannel GPTconfig = {GPT_WGMODE_CTC,GPT_COMODE_NORMAL,T2_F_CPU_1024,GPT_NO_INTERRUPT};

	g_Gpt_Configuration = &GPTconfig;

	TIMER2_init();

	DDRD = 0xFF;
	PORTD = 0x00;

	TIMER2_start(255);

	while(1)
	{
		switch(g_Gpt_Configuration->WGMode)
		{
		case GPT_WGMODE_NORMAL:
			while(BIT_IS_CLEAR(TIFR,TOV2)){}
			tick++;
			if(tick == 4)
			{
				PORTD ^= 0xFF;
				tick2++;
				tick = 0;
			}
			SET_BIT(TIFR,TOV2);
			if(tick2 == 6)
			{
				TIMER2_stop();
				tick2 = 0;
			}
			break;
		case GPT_WGMODE_CTC:
			while(BIT_IS_CLEAR(TIFR,OCF2)){}
			tick++;
			if(tick == 4)
			{
				PORTD ^= 0xFF;
				tick2++;
				tick = 0;
			}
			SET_BIT(TIFR,OCF2);
			if(tick2 == 6)
			{
				TIMER2_stop();
				tick2 = 0;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
