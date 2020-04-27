/*
 * PWM.h
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#ifndef PWM_H_
#define PWM_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*
 * Waveform Generation Mode
 * Timer/Counter Mode of Operation TOP
 *
 * Mode   WGM01    WGM00
 * 1	    0		 1        PWM, Phase Correct
 * 3 		1		 1        Fast PWM
*/
typedef enum {
	PWM_WGMODE_PHASE_CORRECT=1,
	PWM_WGMODE_FAST=3
}PWM_WGModeType;

/*
 * Compare Output Mode , Fast PWM Mode
 * 	COM01    COM00	 Description
 * 	  0 	   0 	 Normal port operation, OC0 disconnected.
 * 	  0 	   1	 Reserved
 * 	  1 	   0	 Clear OC0 on compare match, set OC0 at BOTTOM,(non-inverting mode)
 * 	  1 	   1 	 Set OC0 on compare match, clear OC0 at BOTTOM,(inverting mode)
*/
/*
 * /*
 * Compare Output Mode , Fast PWM Mode
 * 	COM01    COM00	 Description
 * 	  0 	   0 	 Normal port operation, OC0 disconnected.
 * 	  0 	   1	 Reserved
 * 	  1 	   0	 Clear OC0 on compare match when up-counting. Set OC0 on compare match when downcounting.
 * 	  1 	   1 	 Set OC0 on compare match when up-counting. Clear OC0 on compare match when downcounting.
*/

typedef enum {
	PWM_FAST_OC0_DISCONNECTED,
	PWM_FAST_COMODE_NON_INVERTING=2,
	PWM_FAST_COMODE_INVERTING,
	PWM_PHASE_CORRECT_OC0_DISCONNECTED=0,
	PWM_PHASE_CORRECT_COMODE_OC0_CLEAR_UP_SET_DOWN=2,
	PWM_PHASE_CORRECT_COMODE_OC0_SET_UP_CLEAR_DOWN
}PWM_COModeType;

/*
 * Clock Select Bit Description
 * CS02   CS01   CS00   Description
 *   0      0      0    No clock source (Timer/Counter stopped).
 *   0      0      1    clkI/O/(No prescaling)
 *   0      1      0    clkI/O/8 (From prescaler)
 *   0      1      1    clkI/O/64 (From prescaler)
 *   1      0      0    clkI/O/256 (From prescaler)
 *   1      0      1    clkI/O/1024 (From prescaler)
 *   1      1      0    External clock source on T0 pin. Clock on falling edge.
 *   1      1      1    External clock source on T0 pin. Clock on rising edge.
 */
typedef enum
{
	PWM_FAST_F_CPU_256=1,
	PWM_FAST_F_CPU_8_256,
	PWM_FAST_F_CPU_64_256,
	PWM_FAST_F_CPU_256_256,
	PWM_FAST_F_CPU_1024_256,
	EX_CLOCK_FALLING,
	EX_CLOCK_RISING,
	PWM_PHASE_F_CPU_510=1,
	PWM_PHASE_F_CPU_8_510,
	PWM_PHASE_F_CPU_64_510,
	PWM_PHASE_F_CPU_256_510,
	PWM_PHASE_F_CPU_1024_510,
}PWM_Clock;

typedef enum {
	PWM_NO_INTERRUPT,
	PWM_OVER_FLOW_INTERRUPT,
	PWM_COMPARE_INTERRUPT,
	PWM_OVER_FLOW_AND_COMPARE_INTERRUPT
}PWM_Interrupt_ModeType;

typedef struct
{
	PWM_WGModeType PWMMode;
	PWM_COModeType COMode;
	PWM_Clock PWMClock;
	PWM_Interrupt_ModeType Int_Mode;
}PWM_ConfigChannel;

void PWM_init (void);

void PWM_start (const uint8 PWM_Value);

void PWM_stop (void);

extern PWM_ConfigChannel *g_PWM_Configuration;

#endif /* PWM_H_ */
