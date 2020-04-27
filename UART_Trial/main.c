/*
 * main.c
 *
 *  Created on: ١٨‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */
#include "UART.h"
#include <util/delay.h>

int main (void)
{

	//DDRB |= (1<<PB0);//

	UART_Config uartConfig = {BIT_8,ODD_PARITY,STOP_BIT_2,SYNC,RISING_EDGE,SYNC_SPEED,115200,INT_OFF,UART_TX_RX_ON};
	UART_init(&uartConfig);
	uint8 i =0;
	while(1)
	{
		i++;
		UART_send(0x55);
		_delay_ms(500);
	}
	return 0;
}

