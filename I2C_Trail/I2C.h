/*
 * I2C.h
 *
 *  Created on: ٢٢‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#ifndef I2C_H_
#define I2C_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave
#define ERROR 0
#define SUCCESS 1
/*******************************************************************************/

/* F_TWI = ( (F_CPU) / ( 16 + (2 * TWI_Bit_Rate * prescaler) ) */

typedef enum{
	PRESCALER_1,
	PRESCALER_4,
	PRESCALER_16,
	PRESCALER_64,
}TWI_Prescler;

typedef uint8 TWI_Bit_Rate;

typedef uint8 TWI_Address;

typedef enum {
	GENERAL_CALL_OFF,
	GENERAL_CALL_ON
}General_Call_Mode;

typedef enum {
	INT_OFF,
	INT_ON
}Interrupt_Mode;

typedef struct
{
	TWI_Prescler Prescaler;
	TWI_Bit_Rate BitRate;
	TWI_Address Address;
	General_Call_Mode GeneralCall;
	Interrupt_Mode IntMode;
}TWI_Config;

void I2C_init(const TWI_Config *TWI_Configuration);
void I2C_send(uint8 address,uint8 data);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void); //read with send Ack
uint8 TWI_readWithNACK(void); //read without send Ack
uint8 TWI_getStatus(void);

extern TWI_Config twiConfig;

#endif /* I2C_H_ */
