/*
 * EEPROM_I2C.c
 *
 *  Created on: ٢٣‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */
#include "EEPROM_I2C.h"
#include "I2C.h"

#define EPPROM_WRITE 0
#define EPPROM_READ 1

static uint8 EEPROM_InitTransmition(uint8 SlaveAddress , uint8 InternalLocation);

uint8 EEPROM_Write(uint16 MemoryAddress , uint8 InternalLocation , uint8 ArrOfBytes[] ,uint8 SizeOfBytes)
{
	uint8 ByteNum = 0 ;
	uint8 SlaveAddressW = ( (uint8)((0xA0) | (( MemoryAddress & 0x0700)>>7) )  | EPPROM_WRITE );

    if (EEPROM_InitTransmition( SlaveAddressW  ,  InternalLocation ) != SUCCESS)
    {
        return ERROR;
    }
    for (ByteNum = 0 ; ByteNum < SizeOfBytes; ByteNum++ )
    {
    	TWI_write(ArrOfBytes[ByteNum]);
    	if (TWI_getStatus() != TW_MT_DATA_ACK)
    	    {
    	        return ERROR;
    	    }
    }
    /* Send the Stop Bit */
    TWI_stop();
    return SUCCESS;
}
uint8 EEPROM_Read(uint16 MemoryAddress, uint8 InternalLocation , uint8 ArrOfBytes[] ,uint8 SizeOfBytes)
{
	uint8 ByteNum = 0 ;
	uint8 SlaveAddressW = ( (uint8)((0xA0) | (( MemoryAddress & 0x0700)>>7) )  | EPPROM_WRITE );

    if (EEPROM_InitTransmition( SlaveAddressW ,  InternalLocation ) != SUCCESS)
    {
        return ERROR;
    }

    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_REP_START)
    {
    	return ERROR;
    }

    uint8 SlaveAddressR = ( (uint8)((0xA0) | (( MemoryAddress & 0x0700)>>7) )  | EPPROM_READ );

	TWI_write(SlaveAddressR );
	if (TWI_getStatus() != TW_MT_DATA_ACK)
	    {
	        return ERROR;
	    }

    for (ByteNum = 0 ; ByteNum < SizeOfBytes ; ByteNum++ )
    {

    	ArrOfBytes[ByteNum] = TWI_readWithACK();
        if (TWI_getStatus() != TW_MR_DATA_ACK)
            {
        	return ERROR;
            }
    }

    /* Send the Stop Bit */
    TWI_stop();
    return SUCCESS;
}



uint8 EEPROM_InitTransmition(uint8 SlaveAddress , uint8 InternalLocation)
{
	 TWI_start();
	    if (TWI_getStatus() != TW_START)
	    {
	        return ERROR;
	    }
	 TWI_write(SlaveAddress);
	    if (TWI_getStatus() != TW_MT_DATA_ACK)
	    {
	        return ERROR;
	    }
	 TWI_write(InternalLocation);
	    if (TWI_getStatus() != TW_MT_DATA_ACK)
	    {
	        return ERROR;
	    }
     return SUCCESS;

}
