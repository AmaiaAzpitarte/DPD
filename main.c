/*************************************************************************************************************************************
** @file    main.c																													**
** @brief   Fichero principal																										**
** @par		L&oacute;gica																											**
**			- Llama a la funci&oacute;n /a INICIALIZACION_init() para inicializar todas las funcionalidades que necesita el sistema	**
**			- En un bucle /a while, se realizan las siguientes funciones:															**
**				- Se detectan las teclas pulsadas																					**
**				- Se ejecuta la m&aacute;quina de estados																			**
**				- En el caso de que el DPD contenga sensor, se detecta si ha habido movimiento										**
** @author  Amaia Azpitarte																											**
** @date    2013-05-28																												**
** @todo	Falta por implementar la comunicaci&oacute;n con el Controlador															**
*************************************************************************************************************************************/

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/
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
extern TS_AUTOMATA dpd;
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/
int g_linea=0; //variable global que indica la cantidad de líneas a realizar en el DPD
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
* @brief  	Punto de entrada y SuperLoop de la aplicación
* @par		L&oacute;gica:
* 			- Llama a la funci&oacute;n /a INICIALIZACION_init() para inicializar todos los elementos del sistema
*			- En un bucle infinito, se realizan las siguientes funciones:
*				- Se ejecuta la m&aacute;quina de estados
*				- Se detectan las teclas pulsadas
*				- En el caso de que el DPD contenga sensor, se detecta si ha habido movimiento o no
* @return La función nunca finaliza su ejecución
*/
int main(void){

	INICIALIZACION_init();

	dpd.estadoActual = DPD_ESPERA; /* El primer estado es DPD_ESPERA */

	/* Se ejecutará la máquina de estados de forma continua */
	while(1){

		KEYPAD_leer_keypad();

		KEYPAD_elegir_tecla();

		#ifdef DPD_SENSOR
				SENSOR_detectar_movimiento();
		#endif

		AUTOMATA_ejecuta_automata( (TS_AUTOMATA *) &dpd);

		SIMULACION_cantidad_linea(); //solo para el testeo del DPD, para la simulación de la cantidad de líneas por realizar que hay en el DPD

	}
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
