/**
 * @file    simulacion_linea.c
 * @brief   Fichero donde se simula la cantidad de l&iacute;neas que hay en el DPD
 * @par		L&oacute;gica
 *			- Dado que todav&iacute;a no se dispone de la comunicaci&oacute;n, se ha realizado este fichero para poder simular la cantidad de l&iacute;neas que hay en el DPD
 * @author  Amaia Azpitarte
 * @date    2013-06-06
 */

#define SIMULACION_LINEA_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "Simulacion_linea/simulacion_linea.h"
#include "Headers/keypad.h"

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

extern char g_pulsada;

extern int g_linea;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

void SIMULACION_cantidad_linea(){

	switch(g_pulsada){
	case RIGHT: g_linea=1;
				break;
	case LEFT: 	g_linea=2;
				break;
	case DOWN:	g_linea=3;
				break;
	}

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

