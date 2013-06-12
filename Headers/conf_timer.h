

#ifndef __CONFIG_TIMER_H__
#define __CONFIG_TIMER_H__

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

void TIMER_init_timer0(int);
void TIMER_enable_timer0(void);
//void TIMER_disable_timer0(void);
//void TIMER_timer0_int_handler(void);

#endif
