/**
 * @file   	clock.c
 * @brief   Se define el clock al que funcionará el sistema
 * @par		L&oacute;gica
 *			- Se define el clock del sistema: 8MHz
 * @author  Amaia Azpitarte
 * @date    2013-06-05
 */

#define CLOCK_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "hw_types.h"
#include "Headers/clock.h"
#include "driverlib/sysctl.h"
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

extern unsigned long g_system_clock; /*Frecuencia del clock*/

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/**
 * @brief  Función para inicializar el clock.
 *
 * @return    -
 *
 *
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
**********************************************************************/

