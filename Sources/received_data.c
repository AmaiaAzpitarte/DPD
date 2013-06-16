/**
 * @file    received_data.c
 * @brief   Fichero donde se guardan valores en las tres l&iacute;neas de pedido del DPD
 * @par		L&oacute;gica:
 *			- Se guardan los valores de las tres l&iacute;neas de pedido del DPD
 *			- Se reordenan las l&iacute;neas una vez se han confirmado
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 * @todo 	A las estructuras de t_lineapedido correspondientes a las tres l&iacute;neas de pedido que puede haber en el DPD no se les debe dar valores de esa manera. Se les da valores cuando el DPD recibe una l&iacute;nea de pedido desde CAN.
 * @todo	Falta por implementar la recepci&oacute;n de datos mediante CAN
 */

#define _RECEIVED_DATA_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "Headers/data_structs.h"
#include "Headers/received_data.h"

#include "Automata/Automata.h"

#include "DPD_Config.h"
#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif

/*********************************************************************
**																	**
** DEFINITIONS AND MACROS											**
** 																	**
*********************************************************************/
/*********************************************************************
**																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

// Estructura donde se guardan los parámetros de la máquina de estados
extern TS_AUTOMATA dpd;

#ifdef DPD_SENSOR
	extern int g_estado_confirmado;
#endif

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

// Estructura de la línea de pedido 1
t_lineapedido lineapedido_1={1,1,"4",0,0};

// Estructura de la línea de pedido 2
t_lineapedido lineapedido_2={2,2,"5",0,0};

// Estructura de la línea de pedido 3
t_lineapedido lineapedido_3={3,3,"6",1,1};

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief 	Se modifica el orden de las l&iacute;neas de pedido cuando se confirma alguna de ellas
 * @par		L&oacute;gica:
 * 			- Si se confirma la \e lineapedido_1, el 2 pasa a ser el 1, el 3 el 2 y el 1 el 3. (En realidad, el 1 deber&iacute;a eliminarse)
 * 			- Si se confirma la \e lineapedido_2, el 3 pasa a ser el 2 y el 2 el 3. (En realidad, el 2 deber&iacute;a eliminarse)
 * 			- Si se confirma la \e lineapedido_3, no se modifica el orden de las l&iacute;neas de pedido. (En realidad, el 3 deber&iacute;a eliminarse)
 * @return 	void
 * @todo	La l&iacute;nea de pedido que se ha confirmado se debe eliminar del DPD
 */
void RECEIVED_DATA_modificar_posiciones(){

	t_lineapedido lineapedido_changed;

	#ifdef DPD_SENSOR

		if(g_estado_confirmado == 1){

			lineapedido_changed = lineapedido_1;

			lineapedido_1 = lineapedido_2;

			lineapedido_2 = lineapedido_3;

			lineapedido_3 = lineapedido_changed;

		}
		else if(g_estado_confirmado == 2){

			lineapedido_changed = lineapedido_2;

			lineapedido_2 = lineapedido_3;

			lineapedido_3 = lineapedido_changed;

		}

	#else
		if((dpd.estadoActual == UNA_LINEA)||(dpd.estadoActual == MENU_PRIMERO)){

			lineapedido_changed = lineapedido_1;

			lineapedido_1 = lineapedido_2;

			lineapedido_2 = lineapedido_3;

			lineapedido_3 = lineapedido_changed;

		}
		else if(dpd.estadoActual == MENU_SEGUNDO){

			lineapedido_changed = lineapedido_2;

			lineapedido_2 = lineapedido_3;

			lineapedido_3 = lineapedido_changed;

		}
	#endif

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/

