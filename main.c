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

int g_linea=0; //variable global que indica la cantidad de líneas a realizar en el DPD

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

	INICIALIZACION_init();

	dpd.estadoActual = DPD_ESPERA; /* El primer estado es DPD_ESPERA */

	/* Se ejecutará la máquina de estado de forma continua */
	while(1){

		KEYPAD_leer_keypad();

		KEYPAD_elegir_tecla();

		#ifdef DPD_SENSOR
				SENSOR_detectar_movimiento();
		#endif

		AUTOMATA_ejecuta_automata( (TS_AUTOMATA *) &dpd);

		SIMULACION_cantidad_linea(); //solo para el testeo del DPD

	}
}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
