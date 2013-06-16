/**
 * @file   	clock.c
 * @brief   Se define el clock al que funcionar&aacute; el sistema
 * @par		L&oacute;gica
 *			- Se define el clock del sistema: 8MHz
 * @author  Amaia Azpitarte
 * @date    2013-06-05
 */

#define _CLOCK_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "hw_types.h"
#include "Headers/clock.h"
#include "driverlib/sysctl.h"

/*********************************************************************
** 																	**
** DEFINITION AND MACROS 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

// Frecuencia del clock
extern unsigned long g_system_clock;

/*********************************************************************
** 																	**
** GLOBAL VARIABLES					 								**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief  	Funci&oaaaaaacute;n para inicializar el clock.
 * @par		L&oacute;gica:
 * 			- Se inicializa el clock del sistema
 * @return	void
 */
void CLOCK_inicializacion_clock(){

	//125ns
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_8MHZ);
	g_system_clock = SysCtlClockGet();

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/

