/*********************************************************************
** 																	**
** project : DPD				 									**
** filename :testeo_datos_linea.c 									**
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

#define TESTEO_DATOS_LINEA_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "Headers/data_structs.h"
#include "Headers/received_data.h"

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

LINEAPEDIDO linea_pedido_1(){
	LINEAPEDIDO pedido_1;
	pedido_1.id_pedido=1;
	pedido_1.operario=1;
	pedido_1.cantidad=4;
	pedido_1.confirmacion=0;
	pedido_1.final=0;
}

LINEAPEDIDO linea_pedido_2(){
	LINEAPEDIDO pedido_2;
	pedido_2.id_pedido=2;
	pedido_2.operario=2;
	pedido_2.cantidad=5;
	pedido_2.confirmacion=0;
	pedido_2.final=0;
}

LINEAPEDIDO linea_pedido_3(){
	LINEAPEDIDO pedido_3;
	pedido_3.id_pedido=3;
	pedido_3.operario=3;
	pedido_3.cantidad=6;
	pedido_3.confirmacion=0;
	pedido_3.final=1;
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

