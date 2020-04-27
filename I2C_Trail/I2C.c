/*
 * I2C.c
 *
 *  Created on: ٢٢‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "I2C.h"


void I2C_init(const TWI_Config *TWI_Configuration)
{
	//clock -> 400k
	TWBR = TWI_Configuration->BitRate;

	TWSR &= ~(1<<TWPS1 | 1<<TWPS0);
	TWSR |= (TWI_Configuration->Prescaler<<TWPS0);

	//as slave -> slave address last 7 bit
	TWAR = (TWI_Configuration->Address<<TWA0) | (TWI_Configuration->GeneralCall<<TWGCE) ;

	//interrupt
	TWCR &= ~(1<<TWIE);
	TWCR |= (TWI_Configuration->IntMode<<TWIE);

	//Enable i2c
	TWCR |= (1<<TWEN);
}

/*void I2C_send(uint8 address,uint8 data)
{
	//1. Application writes to TWCR to initiate transmission of START
	TWCR |= (1<<TWSTA) | (1<<TWINT);

	//2. TWINT set,	Status code indicates START condition sent.
	 while(BIT_IS_CLEAR(TWCR,TWINT));

	//3. Check TWSR to see if START was	sent.

	//Application loads SLA+W into TWDR,

	 TWDR = address; // (SLA+W)

	// load appropriate control signals into TWCR,
	// making sure that TWINT is written to one, and TWSTA is written to zero
	 TWCR |= (1<<TWEA) | (1<<TWINT);

	//4. TWINT set , Status code indicates SLA+W sent, ACK received.
	 while(BIT_IS_CLEAR(TWCR,TWINT));

	//5. Check TWSR to see if SLA+W was	sent and ACK received.

	// Application loads data into TWDR.
	 TWDR = data; // (Data)

	// loads appropriate control signals into TWCR,
	// making sure that TWINT is written to one
	 TWCR |= (1<<TWEA) | (1<<TWINT);

	//6. TWINT set.	Status code indicates	data sent, ACK received
	 while(BIT_IS_CLEAR(TWCR,TWINT));

	//7. Check TWSR to see if data was sent and ACK received.

	// Application loads appropriate control signals to send STOP into TWCR,
	// making sure that TWINT is written to one
	 TWCR |= (1<<TWSTO) | (1<<TWINT);

	// Enable i2c
	TWCR |= (1<<TWEN);
}
*/

void TWI_start(void)
{
    /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_write(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data; // (SLA+W) or (Data)
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_readWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
