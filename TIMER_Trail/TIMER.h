/*
 * TIMER.h
 *
 *  Created on: ٢٥‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

typedef enum
{
	TIMER0,
	TIMER1,
	TIMER2,
}Gpt_ChannelType;


/*Type for reading and setting the timer values (in number of ticks).*/
typedef uint8 Gpt_ValueType;
/*
 * Waveform Generation Mode
 * Timer/Counter Mode of Operation TOP
 *
 * Mode   WGM01    WGM00
 * 0	    0		 0        Normal
 * 2 		1		 0        CTC
*/
typedef enum {
	GPT_WGMODE_NORMAL,
	GPT_WGMODE_CTC=2
}Gpt_WGModeType;

/*
 * Compare Output Mode , Non PWM Mode
 * 	COM01    COM00	 Description
 * 	0 		0 		 Normal port operation, OC0 disconnected.
 * 	0 		1		 Toggle OC0 on compare match
 * 	1 		0		 Clear OC0 on compare match
 * 	1 		1 		 Set OC0 on compare match
*/
typedef enum {
	GPT_COMODE_NORMAL,
	GPT_COMODE_TOGGLE_OC0,
	GPT_COMODE_CLEAR_OC0,
	GPT_COMODE_SET_OC0
}Gpt_COModeType;

/*
 * Clock Select Bit Description
 * CS02 CS01 CS00 Description
 * 0 0 0 No clock source (Timer/Counter stopped).
 * 0 0 1 clkI/O/(No prescaling)
 * 0 1 0 clkI/O/8 (From prescaler)
 * 0 1 1 clkI/O/64 (From prescaler)
 * 1 0 0 clkI/O/256 (From prescaler)
 * 1 0 1 clkI/O/1024 (From prescaler)
 * 1 1 0 External clock source on T0 pin. Clock on falling edge.
 * 1 1 1 External clock source on T0 pin. Clock on rising edge.
 */
typedef enum
{
	T0_F_CPU_CLOCK=1,
	T2_F_CPU_CLOCK=1,
	T0_F_CPU_8,
	T2_F_CPU_8=2,
	T0_F_CPU_64,
	T2_F_CPU_32=3,
	T0_F_CPU_256,
	T2_F_CPU_64=4,
	T0_F_CPU_1024,
	T2_F_CPU_128=5,
	T0_EX_CLOCK_FALLING,
	T2_F_CPU_256=6,
	T0_EX_CLOCK_RISING,
	T2_F_CPU_1024=7
}Gpt_Clock;


/*
 * Waveform Generation Mode
 * Mode WGM01(CTC0) WGM00(PWM0)
 * Timer/Counter Mode of Operation TOP

 * 0	    0		 0 Normal
 * 2 		1		 0 CTC
*/
typedef enum {
	GPT_NO_INTERRUPT,
	GPT_NORMAL_INTERRUPT,
	GPT_CTC_INTERRUPT
}Gpt_Interrupt_ModeType;



typedef struct
{
	Gpt_WGModeType WGMode;
	Gpt_COModeType COMode;
	Gpt_Clock Clock;
	Gpt_Interrupt_ModeType Int_Mode;
}Gpt_ConfigChannel;


void TIMER0_init (void);

void TIMER0_start (const uint8 Gpt_Value);

void TIMER0_stop (void);

void TIMER2_init (void);

void TIMER2_start (const uint8 Gpt_Value);

void TIMER2_stop (void);

extern Gpt_ConfigChannel *g_Gpt_Configuration;


#endif /* TIMER_H_ */
