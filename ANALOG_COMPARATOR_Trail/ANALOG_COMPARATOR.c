/*
 * ANALOG_COMPARATOR.c
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "ANALOG_COMPARATOR.H"

void ANALOG_COMARTOR_init (const AnalogCompartorConfiguration * ACConfiguration)
{
	SFIOR |= (ACConfiguration->ACMultiplexerMode <<ACME);

	ACSR |=   (ACConfiguration->ACBandgapMode <<ACBG)
		    | (ACConfiguration->ACInterruptMode <<ACIE)
			| (ACConfiguration->ACInterruptType <<ACIS0)
			| (ACConfiguration->ACInputCaptureMode <<ACIC);

	ADMUX &= 0xF8;
	ADMUX |= (ACConfiguration->ACNegativeInputMode <<MUX0);
}

void ANALOG_COMARTOR_Start ()
{
	CLEAR_BIT(ACSR,ACD);
	ACSR |= (AC_ENABLE<<ACD);
}

uint8 ANALOG_COMARTOR_Output ()
{
	return ((ACSR >> ACO) & (0x01));
}

void ANALOG_COMARTOR_Stop ()
{
	ACSR |= (AC_DISABLE<<ACD);

}
