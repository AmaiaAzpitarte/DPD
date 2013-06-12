/*********************************************************************
** 																	**
** project : DPD			 										**
** filename : inicializacion.c 										**
** version : 1 														**
** date : June 07, 2013 											**
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
**Date : June 07, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/
#define INICIALIZACION_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "Headers/inicializacion.h"

#include "DPD_Config.h"

/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

void DPD_inicializacion(){

	RIT128x96x4Init(1000000);
	RIT128x96x4StringDraw("ESTADO - dpd espera",5,87,15);

	//initSysTick();

	DPD_inicializacion_pwm();

	DPD_inicializacion_keypad();

	DPD_inicializacion_clock();

	DPD_inicializacion_leds();

	#ifdef DPD_SENSOR
		DPD_inicializacion_sensor();
	#endif

	init_Timer0(5);

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

