/*********************************************************************
** 																	**
** project : DPD				 									**
** filename : main.c		 										**
** version : 1 														**
** date : May 28, 2013 												**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2013, 					 							**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : May 28, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/
#include "Automata/Automata.h"
#include "DPD/DPD.h"
#include "driverlib/systick.h"

//#include "Headers/clock.h"

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
**********************************************************************/
/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
**********************************************************************/
/*********************************************************************
** 																	**
** PROTOTYPES OF LOCAL FUNCTIONS 									**
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
**********************************************************************/

extern TS_AUTOMATA dpd;

int linea=0; //variable global que indica la cantidad de líneas a realizar en el DPD

/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

/**
* @brief  Punto de entrada y SuperLoop de la aplicación
*
* @return La función nunca finaliza su ejecución
*
* Inicializa todos los elementos del sistema y ejecuta las tareas de
* la máquina de estado constantemente en un bucle infinito
*
*/

int main(void){

	RIT128x96x4Init(1000000);
	RIT128x96x4Enable(1000000);
	RIT128x96x4StringDraw("ESTADO - dpd espera",5,80,15);

	initSysTick();

	DPD_inicializacion_pwm();

	DPD_inicializacion_keypad();

	DPD_inicializacion_clock();

	DPD_inicializacion_leds(); //como el puerto utilizado es el de SSI, no funciona correctamente con el display

	dpd.estadoActual = DPD_ESPERA; /* El primer estado es DPD_ESPERA */

	/* Se ejecutará la máquina de estado de forma continua */
	while(1){

		DPD_leer_keypad();

		DPD_elegir_tecla();

		EjecutaAutomata( (TS_AUTOMATA *) &dpd);

		cantidad_linea();

	}
}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
