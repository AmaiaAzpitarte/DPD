/*********************************************************************
** 																	**
** project : DPD			 										**
** filename : clock.c 												**
** version : 1 														**
** date : June 05, 2013 											**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2013,		 										**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : June 05, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/
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

