/*
 * main.c
 *
 *  Created on: ٢٢‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */
#define F_CPU 8000000UL //1MHz Clock frequency
#include "EEPROM_I2C.h"
#include "I2C.h"




int main(void)
{

	TWI_Config twiConfig={PRESCALER_1,2,0x09,GENERAL_CALL_OFF,INT_OFF};
	I2C_init(&twiConfig);
	uint8 ArrOfBytes[1]={0xAA};
	while(1)
	{
		_delay_ms(1000);
		 EEPROM_Write(0x0311 , 0x88 , ArrOfBytes ,1);

	}

	return 0;
}
