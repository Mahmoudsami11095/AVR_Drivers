/*
 * UART.h
 *
 *  Created on: ١٨‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#ifndef UART_H_
#define UART_H_


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

extern volatile uint16 g_uartValue;

typedef enum {
	ASYNC,
	SYNC
}Uart_Mode;

typedef enum {
	RISING_EDGE,
	FALLING_EDGE
}ClockPolarity_Type;

typedef enum {
	DISABLE_PARITY,
	RESERVED,
	EVEN_PARITY,
	ODD_PARITY
}ParityMode_type;

typedef enum {
	INT_OFF=0,
	INT_TX_ON,
	INT_RX_ON,
	INT_TX_RX_ON
}Interrupt_Mode;

typedef enum {
	STOP_BIT_1,
	STOP_BIT_2
}StopBit_Type;

typedef enum {
	UART_OFF=0,
	UART_TX_ON,
	UART_RX_ON,
	UART_TX_RX_ON
}UartEnable_Mode;

typedef enum {
	SYNC_SPEED=2,
	ASYNC_DOUBLE_SPEED=8,
	ASYNC_NORMAL_SPEED=16
}Speed_Mode;

typedef enum {
	BIT_5,
	BIT_6,
	BIT_7,
	BIT_8
}DataBit_Type;

typedef uint32 Baudrate_Type;

typedef struct
{
	DataBit_Type DataBit_Num;
	ParityMode_type Parity_Mode;
	StopBit_Type Stopbit_Num;
	Uart_Mode Uartmode;
	ClockPolarity_Type ClkPol;
	Speed_Mode SpeedMode;
	Baudrate_Type Baudrate;
	Interrupt_Mode IntMode;
	UartEnable_Mode uartEnable;

}UART_Config;

void UART_init(const UART_Config *UART_Configuration);

void UART_send(uint8 data);

void UART_recieve(uint8 *PTR_data);

extern UART_Config uartConfig;

#endif /* UART_H_ */
