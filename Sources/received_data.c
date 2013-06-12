/*********************************************************************
** 																	**
** project : DPD				 									**
** filename : received_data.c 										**
** version : 1 														**
** date : June 3, 2013		 										**
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
**Date : June 3, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/

#define RECEIVED_DATA_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "Headers/data_structs.h"
#include "Headers/received_data.h"

#include "Automata/Automata.h"

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

t_lineapedido lineapedido_changed;


void DPD_modificar_posiciones(){

	if((dpd.estadoActual == UNA_LINEA)||(dpd.estadoActual == MENU_PRIMERO)){

		lineapedido_changed = lineapedido_1;

		lineapedido_1 = lineapedido_2;

		lineapedido_2 = lineapedido_3;

		lineapedido_3 = lineapedido_changed;

	}
	else if(dpd.estadoActual == DOS_LINEAS){

		lineapedido_changed = lineapedido_2;

		lineapedido_2 = lineapedido_3;

		lineapedido_3 = lineapedido_changed;

	}

}

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

