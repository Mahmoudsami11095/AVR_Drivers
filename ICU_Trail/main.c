/*
 * main.c
 *
 *  Created on: ٢٨‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

ISR(TIMER1_CAPT_vect)
{
	static uint8 count = 0;
	static uint16 High = 0;
	static uint16 period = 0;
	static uint16 High_period = 0;

	count++;
	if (count == 1 )
	{
		TCNT1 = 0;
		CLEAR_BIT(TCCR1B,ICES1);

	}
	else if(count == 2)
	{
		High = ICR1;
		SET_BIT(TCCR1B,ICES1);
	}
	else if(count == 3)
	{
		period = ICR1;
		CLEAR_BIT(TCCR1B,ICES1);

	}
	else if(count == 4)
	{
		High_period = ICR1;
		SET_BIT(TCCR1B,ICES1);
		PORTC = ((float)(High_period - period)/(float)(High_period - High))*100;
		count=0;
	}

}

int main (void)
{
	CLEAR_BIT(DDRD,PD6);

	TCCR1A |= (1<<FOC1A);
	TCCR1B |= (1<<ICES1) | (1<<CS10);
	TCNT1 = 0;
	TIMSK |= (1<<TICIE1);
    DDRC = 0xff;

	SREG |= (1<<7);

	while(1)
	{

	}
	return 0;
}
