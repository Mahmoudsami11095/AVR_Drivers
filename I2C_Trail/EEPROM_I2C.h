/*
 * EEPROM_I2C.h
 *
 *  Created on: ٢٣‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#ifndef EEPROM_I2C_H_
#define EEPROM_I2C_H_


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

uint8 EEPROM_Write(uint16 MemoryAddress , uint8 InternalLocation , uint8 ArrOfBytes[] ,uint8 SizeOfBytes);

uint8 EEPROM_Read(uint16 MemoryAddress , uint8 InternalLocation , uint8 ArrOfBytes[] ,uint8 SizeOfBytes);

#endif /* EEPROM_I2C_H_ */
