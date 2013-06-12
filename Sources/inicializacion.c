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

void INICIALIZACION_init(){

	DISPLAY_inicializacion_display();

	//Las siguientes dos lineas tengo que quitarlas
	char* str = "Estado - dpd espera";
	DISPLAY_escribir_en_pantalla(str,5,87);

	SONIDO_init();

	KEYPAD_init();

	CLOCK_inicializacion_clock();

	LEDS_init();

	#ifdef DPD_SENSOR
		SENSOR_init();
	#endif

	TIMER_init_timer0(5);

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

