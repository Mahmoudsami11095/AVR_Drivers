/*
 * main.c
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "PWM.h"

int main (void)
{
	PWM_ConfigChannel PWM_Configuration = {PWM_WGMODE_PHASE_CORRECT,PWM_PHASE_CORRECT_COMODE_OC0_CLEAR_UP_SET_DOWN,PWM_PHASE_F_CPU_1024_510,PWM_NO_INTERRUPT};

	g_PWM_Configuration = &PWM_Configuration;

	PWM_init();


	while(1)
	{
		PWM_start(64);
		_delay_ms(2000);
		PWM_start(128);
		_delay_ms(2000);
		PWM_start(128+64);
		_delay_ms(2000);
		PWM_start(255);
		_delay_ms(4000);
		PWM_stop();
		_delay_ms(4000);

	}
	return 0;
}

