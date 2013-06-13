/**
 * @file    received_data.c
 * @brief   Fichero donde se guardan valores en las tres lineas de pedido del DPD
 * @par		L&oacute;gica
 *			- Se guardan los valores de las tres l&iacute;neas de pedido del DPD
 *			- Se reordenan las l&iacute;neas una vez se han confirmado
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#define RECEIVED_DATA_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

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
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

extern TS_AUTOMATA dpd;

#ifdef DPD_SENSOR
	extern int g_estado_confirmado;
#endif

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/


//@todo 	Estos en realidad no deben estar creados así. Se les da
//			valores a los elementos cuando el DPD recibe una línea de
//			pedido mediante CAN.
t_lineapedido lineapedido_1={1,1,"4",0,0};

t_lineapedido lineapedido_2={2,2,"5",0,0};

t_lineapedido lineapedido_3={3,3,"6",1,1};

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

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
**********************************************************************/

