/*
 * SPI.c
 *
 *  Created on: Ù¢Ù â€�/Ù Ù¢â€�/Ù¢Ù Ù¢Ù 
 *      Author: som3a
 */

#include "SPI.h"

ISR(SPI_vect)
{
	_delay_ms(1000);
}

void SPI_Masterinit(const SPI_Config *SPI_Configuration)
{

    //SPIE SPE DORD MSTR CPOL CPHA SPR1 SPR0 SPCR

	/*select mode master */
	SPCR |= (1 << MSTR) ;

	//Data order
	SPCR &= ~(1<<DORD) ;
	SPCR |= ( SPI_Configuration->DataOrder << DORD);

	//Clock Polarity CPOL Leading Edge Trailing Edge
	SPCR &= ~(1<<CPOL);
	SPCR |= ( SPI_Configuration->ClkPolarity <<CPOL);

	// Clock Phase
	SPCR &= ~(1<<CPHA);
	SPCR |= ( SPI_Configuration->ClkPhase <<CPHA);

	//SPI Clock Rate for normal speed
	SPCR &= ~(1<<SPR1 & 1<<SPR0);
	SPCR |= ((0x03 & SPI_Configuration->ClkRate) <<SPR0 );
	//SPI Clock Rate for double speed
	//we must select 3rd bit first and shift it to LSB in the byte then another shift for specified bit
	SPSR &= ~(1<<SPI2X);
	//SPSR |= (((0x04 & SPI_Configuration->ClkRate)>>2) <<SPI2X );


	/*enable or disable interrupts*/
	SPCR &= ~(1<<SPIE);
	SPCR |= (SPI_Configuration->IntMode <<SPIE);

	// SPI pins
	SET_BIT(DDRB,PB4); // SS output
	SET_BIT(DDRB,PB5); // MOSI output
	CLEAR_BIT(DDRB,PB6); // MISO input
	SET_BIT(DDRB,PB7); // SCK output

 	/*enable SPI module*/
	SPCR |= (1<<SPE);
}

void SPI_Slaveinit(const SPI_Config *SPI_Configuration)
{

    //SPIE SPE DORD MSTR CPOL CPHA SPR1 SPR0 SPCR

	/*select mode  slave*/
	SPCR &= ~(1<<MSTR) ;

	//Data order
	SPCR &= ~(1<<DORD) ;
	SPCR |= ( SPI_Configuration->DataOrder << DORD);

	//Clock Polarity CPOL Leading Edge Trailing Edge
	SPCR &= ~(1<<CPOL);
	SPCR |= ( SPI_Configuration->ClkPolarity <<CPOL);

	// Clock Phase
	SPCR &= ~(1<<CPHA);
	SPCR |= ( SPI_Configuration->ClkPhase <<CPHA);

	//SPI Clock Rate for normal speed
	SPCR &= ~(1<<SPR1 & 1<<SPR0);
	SPCR |= ((0x03 & SPI_Configuration->ClkRate) <<SPR0 );
	//SPI Clock Rate for double speed
	//we must select 3rd bit first and shift it to LSB in the byte then another shift for specified bit
	SPSR &= ~(1<<SPI2X);
	SPSR |= (((0x04 & SPI_Configuration->ClkRate)>>2) <<SPI2X );


	/*enable or disable interrupts*/
	SPCR &= ~(1<<SPIE);
	SPCR |= (SPI_Configuration->IntMode <<SPIE);

	// SPI pins
	CLEAR_BIT(DDRB,PB4); // SS output
	CLEAR_BIT(DDRB,PB5); // MOSI output
	SET_BIT(DDRB,PB6); // MISO input
	CLEAR_BIT(DDRB,PB7); // SCK output

 	/*enable SPI module*/
	SPCR |= (1<<SPE);
}

void SPI_send(const uint8 data)
{
	SPDR = data; //send data by SPI
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

void SPI_recieve(uint8 *PTR_data)
{
	while(BIT_IS_CLEAR(SPSR,SPIF)){}
	*PTR_data = SPDR;
}
