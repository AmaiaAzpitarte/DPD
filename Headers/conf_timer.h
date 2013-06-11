

#ifndef __CONFIG_TIMER_H__
#define __CONFIG_TIMER_H__

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

void init_Timer0(int);
void enable_Timer_0(void);
void disable_Timer0(void);

//void init_Timer3(int);
//void enable_Timer_3(void);
//void disable_Timer3(void);

//void init_Timer2(int);
//void enable_Timer_2(void);

#endif
