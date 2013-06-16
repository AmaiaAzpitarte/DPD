/**
 * @file   	inicializacion.c
 * @brief   Fichero donde se inicializan las funcionalidades que el sistema necesita
 * @par		L&oacute;gica
 *			- Se inicializa el display
 *			- Se inicializa el altavoz
 *			- Se inicializa el keypad
 *			- Se inicializa el clock
 *			- Se inicializan los leds
 *			- Se inicializa el timer_0
 *			- En caso de que el DPD contenga sensor, se inicializa el sensor
 * @author  Amaia Azpitarte
 * @date    2013-06-07
 */

#define _INICIALIZACION_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "Headers/inicializacion.h"

#include "DPD_Config.h"

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** GLOBAL VARIABLES		 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief  	Inicializa todas las funcionalidades o elementos que el sistema necesita
 * @par		L&oacute;gica
 *			- Se inicializa el display
 *			- Se inicializa el altavoz
 *			- Se inicializa el keypad
 *			- Se inicializa el clock
 *			- Se inicializan los leds
 *			- Se inicializa el timer_0
 *			- En caso de que el DPD contenga sensor, se inicializa el sensor
 * @return 	void
 */
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

	TIMER_init_timer0(TIMER_ESPERA);

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/

