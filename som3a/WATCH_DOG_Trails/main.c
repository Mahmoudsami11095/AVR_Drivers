/*
 * main.c
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "WATCH_DOG.h"

int main(void)
{
	WatchDogConfigure WDConfig = {WD_TIMEOUT_2_1_S};

	// Enable the Watchdog timer
	WATCHDOG_start(&WDConfig);

	// Configure PD6 as output pin
	DDRD |= (1<<PD6);

	// Toggle the led every reset
	PORTD |= (1<<PD6);
	_delay_ms(1000);
	PORTD &= ~(1<<PD6);

	// Wait until the system reset itself
    while(1);
}

