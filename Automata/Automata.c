/**
 * @file    Automata.c
 * @brief   Fichero donde se define la m&aacute;quina de estados o el aut&oacute;mata
 * @par		L&oacute;gica
 *			- Se ejecuta el aut&oacute;mata
 *			- Se ejecutan los estados, transiciones y acciones del aut&oacute;mata
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#define _AUTOMATA_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "Automata/Automata.h"

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

// Estructura donde se guardan los parámetros de la máquina de estados
extern TS_AUTOMATA dpd;

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
 * @brief  	Ejecuta el aut&oacute;mata
 * @par		L&oacute;gica:
 * 			- Se ejecuta el aut&oacute;mata, con sus estados, transiciones y acciones:
 * 				- Se consulta el estado del aut&oacute;mata
 * 				- Se ejecuta el estado que corresponda
 * @param	elAutomata	Puntero al aut&oacute;mata
 * @return void
 */
void AUTOMATA_ejecuta_automata(TS_AUTOMATA *elAutomata){

	// Valor índice rastreador
	TS_ESTADO **Indx;

	for (Indx = elAutomata->estado; *Indx != NULL; ++Indx){

	    if (elAutomata->estadoActual == (*Indx)->id){

	    	AUTOMATA_ejecuta_estado(*Indx, elAutomata);

			return;

	    }

	}

}

/**
 * @brief  	Ejecuta el estado
 * @par		L&oacute;gica:
 * 			- Mira en el estado si hay alg&uacute;n evento
 * 			- Si hay alg&uacute;n evento, se ejecuta la transici&oacute;n a otro estado
 * @param	elEstado	Puntero al estado
 * @param	elAutomata	Puntero al autómata
 * @return void
 */
void AUTOMATA_ejecuta_estado (TS_ESTADO *elEstado, TS_AUTOMATA *elAutomata){

	// Índice de rastreo
	TS_EVEACC *Indx;

		for (Indx = elEstado->funcion; Indx->evento != NULL; ++Indx){

			if (Indx->evento() == true){

				if (Indx->accion != NULL){

					Indx->accion();
				}

				if (Indx->id != elAutomata->estadoActual){

					elAutomata->estadoActual = Indx->id;

					return;

				}

			}

		}

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
