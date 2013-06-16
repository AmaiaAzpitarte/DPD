/**
 * @file    simulacion_linea.c
 * @brief   Fichero donde se simula la cantidad de l&iacute;neas que hay en el DPD
 * @par		L&oacute;gica
 *			- Dado que todav&iacute;a no se dispone de la comunicaci&oacute;n, se ha realizado este fichero para poder simular la cantidad de l&iacute;neas que hay en el DPD
 * @author  Amaia Azpitarte
 * @date    2013-06-06
 * @todo	Una vez se implemente la comunicaci&oacute;n con CAN, se debe eliminar la funci&oacute;n \b SIMULACION_cantidad_linea(), que solo sirve para la simulaci&oacute;n de la cantidad de l&iacute;neas que hay en el DPD
 */

#define SIMULACION_LINEA_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "Simulacion_linea/simulacion_linea.h"
#include "Headers/keypad.h"

/*********************************************************************
**																	**
** DEFINITIONS AND MACROS											**
** 																	**
*********************************************************************/
/*********************************************************************
**																	**
** TYPEDEFS AND STRUCTURES											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

// Variable global que indica el botón que se ha pulsado
extern char g_pulsada;

// Variable global que indica la cantidad de líneas de pedido por realizar que hay en el DPD
extern int g_linea;

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief  	Se simula la cantidad de l&iacute;neas por realizar que hay en el DPD
 * @par		L&oacute;gica:
 * 			- Dependiendo de la tecla pulsada, se simula que hay una cantidad distinta en el DPD
 * @return 	void
 * @todo	Esta funci&oacute;n debe eliminarse, ya que solo sirve para simulaci&oacute;n
 */
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
*********************************************************************/

