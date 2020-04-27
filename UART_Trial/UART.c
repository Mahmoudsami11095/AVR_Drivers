/*
 * UART.c
 *
 *  Created on: ١٨‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "UART.h"

#define FCPU 1000000

void UART_init(const UART_Config *UART_Configuration)
{
	uint16 ubrrVal = 0;

	/*select mode and config the frame*/
	UCSRC |= (1<<URSEL) ;
	//number of bits used
	UCSRC &= ~(1<<UCSZ1 | 1<<UCSZ0);
	UCSRC |=  ((UART_Configuration->DataBit_Num)<<UCSZ0);

	//parity type
	UCSRC &= ~(1<<UPM1 | 1<<UPM0);
	UCSRC |= ((UART_Configuration->Parity_Mode)<<UPM0);

	//stop bits
	UCSRC &= ~(1<<USBS);
	UCSRC |= (UART_Configuration->Stopbit_Num<<USBS);

	//uart mode
	UCSRC &= ~(1<<UMSEL);
	UCSRC |= (UART_Configuration->Uartmode<<UMSEL);
	DDRB |= (UART_Configuration->Uartmode<<PB0 ); // make this pin output for clock ( tx uart)

	//Clock Polarity
	UCSRC &= ~(1<<UCPOL);
	UCSRC |= ( (UART_Configuration->ClkPol & UART_Configuration->Uartmode )<<UCPOL);

	/*select baud rate*/
	switch (UART_Configuration->SpeedMode)
	{
	case ASYNC_NORMAL_SPEED:
		UCSRA &= ~(1<<U2X);
		break;
	case ASYNC_DOUBLE_SPEED:
		UCSRA |= (1<<U2X);
		break;
	default:
		UCSRA &= ~(1<<U2X);
		break;
	}
	//ubrrVal = (((F_CPU / (UART_Configuration->Baudrate * (UART_Configuration->doubleSpeed)))) - 1);
	ubrrVal = ((F_CPU / (UART_Configuration->Baudrate * ((UART_Configuration->SpeedMode)))) - 1);
	//ubrrVal = (((F_CPU / (9600 * 8UL))) - 1);
	UBRRH &= ~0x8F;
	UBRRH |= (uint8) ((ubrrVal>>8) & 0x0F);
	UBRRL = (uint8) ubrrVal;

	/*enable or disable interrupts*/
	UCSRB &= ~(1<<RXCIE | 1<<TXCIE);
	UCSRB |= (UART_Configuration->IntMode<<TXCIE);

 	/*enable uart module*/
	UCSRB &= ~((1<<TXEN)|(1<<RXEN));
	UCSRB |= (UART_Configuration->uartEnable<<TXEN);
}

void UART_send(uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;
}

void UART_recieve(uint8 *PTR_data)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	*PTR_data = UDR;
}
