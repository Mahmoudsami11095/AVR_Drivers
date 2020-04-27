/*
 * WATCH_DOG.c
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#include "WATCH_DOG.h"

void WATCHDOG_start (const WatchDogConfigure * WDConfiguration)
{
	WDTCR = (WD_ENABLE <<WDE)|(WDConfiguration->WDTime << WDP0);

}
void WATCHDOG_stop ()
{
	WDTCR = (WD_ENABLE << WDTOE)| (WD_ENABLE << WDE);
	WDTCR = (WD_DISABLE << WDE);
}
