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
//#include "DPD/DPD.h"
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

	DPD_inicializacion();

	dpd.estadoActual = DPD_ESPERA; /* El primer estado es DPD_ESPERA */

	/* Se ejecutará la máquina de estado de forma continua */
	while(1){

		DPD_leer_keypad();

		DPD_elegir_tecla();

		#ifdef DPD_SENSOR
			//if((dpd.estadoActual=UNA_LINEA)||(dpd.estadoActual=MENU_PRIMERO)||(dpd.estadoActual=MENU_SEGUNDO)||(dpd.estadoActual=MENU_TERCERO)){
				DPD_detectar_movimiento();
			//}
		#endif

		EjecutaAutomata( (TS_AUTOMATA *) &dpd);

		cantidad_linea(); //solo para el testeo del DPD

	}
}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
