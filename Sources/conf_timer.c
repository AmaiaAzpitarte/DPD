
#include "Headers/conf_timer.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

#include "DPD_Config.h"


#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif


tBoolean g_timer_finished = false;


void TIMER_init_timer0(int factor){ //factor= multiplica 1 segundo para conseguir el tiempo que queremos

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //
	// Enable processor interrupts.
	//
    IntMasterEnable();

	//
    // Configure the two 32-bit periodic timers.
	//
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_ONE_SHOT);

	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * factor);

}

void TIMER_enable_timer0(void) {

	//
	// Setup the interrupts for the timer timeouts.
	//
	//TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * factor);

    IntEnable(INT_TIMER0A);

	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	//
	// Enable the timer.
	//
	TimerEnable(TIMER0_BASE, TIMER_A);

}

void TIMER_disable_timer0(void) {

	IntDisable(INT_TIMER0A);

}

//*****************************************************************************
//
// The interrupt handler for the first timer interrupt.
//
//*****************************************************************************
void TIMER_timer0_int_handler(void)
{
	//char str[1];
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Update the interrupt status on the display.
    //
    IntDisable(INT_TIMER0A);

    g_timer_finished = true;

    IntEnable(INT_TIMER0A);
}
