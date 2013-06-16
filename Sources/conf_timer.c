/**
 * @file   	conf_timer.c
 * @brief   Se configura el timer del sistema
 * @par		L&oacute;gica
 *			- Se inicializa el timer_0
 *			- Se habilita el timer_0
 *			- Se define una funci&oacute;n para poder deshabilitar el timer_0 cuando se quiera
 *			- Se controla el timer_0
 * @author  Amaia Azpitarte
 * @date    2013-06-11
 */

#define _CONF_TIMER_C

/*********************************************************************
** 																	**
** MODULES USED		 												**
** 																	**
*********************************************************************/

#include "Headers/conf_timer.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

#include "DPD_Config.h"
#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

// Variable global que indica que el timer ha finalizado de esperar el tiempo que le hemos asignado
tBoolean g_timer_finished = false;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief  	Inicializaci&oacute;n del timer 0
 * @par		L&oacute;gica:
 * 			- Habilita el timer 0
 *			- Configura el timer 0, multiplicando el tiempo que debe esperar por el par&aacute;metro \e factor
 * @param 	factor	par&aacute;metro que multiplica el tiempo de espera del timer
 * @return 	void
 */
void TIMER_init_timer0(int factor){

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    IntMasterEnable();

    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_ONE_SHOT);

	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() * factor);

}

/**
 * @brief  	Habilita el timer 0
 * @par		L&oacute;gica:
 * 			- Habilita el timer
 * @return 	void
 */
void TIMER_enable_timer0(void) {

    IntEnable(INT_TIMER0A);

	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	//
	// Enable the timer.
	//
	TimerEnable(TIMER0_BASE, TIMER_A);

}

/**
 * @brief  	Deshabilita el timer 0
 * @par		L&oacute;gica:
 * 			- Deshabilita el timer 0
 * @return 	void
 */
void TIMER_disable_timer0(void) {

	IntDisable(INT_TIMER0A);

}

/**
 * @brief  	Controla las interrupciones del timer 0
 * @par		L&oacute;gica:
 * 			- Limpia la interrupci&oacute;n del timer 0
 * 			- Deshabilita el timer 0
 * 			- Cambia el valor de la variable global \b g_timer_finished, para indicar que ha pasado el tiempo definido
 * 			- Vuelve a habilitar el timer
 * @return 	void
 */
void TIMER_timer0_int_handler(void)
{

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TIMER_disable_timer0();

    g_timer_finished = true;

    IntEnable(INT_TIMER0A);

}

/*********************************************************************
** 																	**
** EOF				 												**
** 																	**
*********************************************************************/
