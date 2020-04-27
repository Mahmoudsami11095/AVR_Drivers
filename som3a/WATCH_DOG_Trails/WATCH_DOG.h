/*
 * WATCH_DOG.h
 *
 *  Created on: ٢٩‏/٠٢‏/٢٠٢٠
 *      Author: som3a
 */

#ifndef WATCH_DOG_H_
#define WATCH_DOG_H_


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
/*
0 0 0 16K (16,384) 17.1 ms 16.3 ms
0 0 1 32K (32,768) 34.3 ms 32.5 ms
0 1 0 64K (65,536) 68.5 ms 65 ms
0 1 1 128K (131,072) 0.14 s 0.13 s
1 0 0 256K (262,144) 0.27 s 0.26 s
1 0 1 512K (524,288) 0.55 s 0.52 s
1 1 0 1,024K (1,048,576) 1.1 s 1.0 s
1 1 1 2,048K (2,097,152) 2.2 s 2.1*/
typedef enum{
	WD_TIMEOUT_16_3_MS,
	WD_TIMEOUT_32_5_MS,
	WD_TIMEOUT_65_0_MS,
	WD_TIMEOUT_0_13_S,
	WD_TIMEOUT_0_26_S,
	WD_TIMEOUT_0_52_S,
	WD_TIMEOUT_1_0_S,
	WD_TIMEOUT_2_1_S
}WatchDogPrescale;

typedef enum{
	WD_DISABLE,
	WD_ENABLE
}WatchDogMode;

typedef struct{
	WatchDogPrescale WDTime;
}WatchDogConfigure;

void WATCHDOG_start (const WatchDogConfigure * WDConfiguration);
void WATCHDOG_stop ();

extern WatchDogConfigure WDConfig;
#endif /* WATCH_DOG_H_ */
