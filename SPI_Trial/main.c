/*
 * main.c
 *
 *  Created on: Ù¢Ù â€�/Ù Ù¢â€�/Ù¢Ù Ù¢Ù 
 *      Author: som3a
 */


#include "SPI.h"

int main (void)
{

    SPI_Config spiConfig = {MSB,LEVEL_LOW,TRAILING_EDGE,F_CPU_4_NS,INT_ON};
	SPI_Masterinit(&spiConfig);
	SREG |= (1<<7);
	while(1)
	{
		SPI_send (0xAA);
	}
	return 0;
}
