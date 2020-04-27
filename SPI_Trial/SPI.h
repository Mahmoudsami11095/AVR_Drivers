/*
 * SPI.h
 *
 *  Created on: Ù¢Ù â€�/Ù Ù¢â€�/Ù¢Ù Ù¢Ù 
 *      Author: som3a
 */

#ifndef SPI_H_
#define SPI_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

typedef enum {
	INT_OFF,
	INT_ON
}Interrupt_Mode;


typedef enum {
	MSB,
	LSB
}DataOrder_Mode;


typedef enum {
	LEVEL_LOW,
	LEVEL_HIGH
}ClockPolarity_Mode;

typedef enum {
	LEADING_EDGE,
	TRAILING_EDGE
}ClockPhase_Mode;

typedef enum {
	F_CPU_4_NS,
	F_CPU_16_NS,
	F_CPU_64_NS,
	F_CPU_128_NS,
	F_CPU_2_DS,
	F_CPU_8_DS,
	F_CPU_32_DS,
	F_CPU_64_DS
}ClockRate_Mode;

typedef struct
{
	DataOrder_Mode DataOrder;
	ClockPolarity_Mode ClkPolarity;
	ClockPhase_Mode ClkPhase;
	ClockRate_Mode ClkRate;
	Interrupt_Mode IntMode;
}SPI_Config;

void SPI_Masterinit(const SPI_Config *SPI_Configuration);

void SPI_Slaveinit(const SPI_Config *SPI_Configuration);

void SPI_send(uint8 data);

void SPI_recieve(uint8 *PTR_data);

extern SPI_Config spiConfig;


#endif /* SPI_H_ */
