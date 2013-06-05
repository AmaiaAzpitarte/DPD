/*********************************************************************
** 																	**
** project : DPD			 										**
** filename : systick.c 											**
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
#define SYSTICK_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/


/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

unsigned char g_ucCounter;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

/**
 * @brief Cuenta cada vez que hay una interrupción del SysTick e
 * inicializa el contador al llegar a 10
 *
 * @return void
 */

void SysTick_Handler(void){

	g_ucCounter++;

	if (g_ucCounter == 6){

		g_ucCounter = 0;

	}

}

/**
 * @brief  Inicializa el SysTick
 *
 * @return void
 *
 */

void initSysTick(){

	SysTickPeriodSet(SysCtlClockGet());

	SysTickIntEnable();

	SysTickEnable();

}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

