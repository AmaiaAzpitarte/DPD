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
**********************************************************************/

#include "Automata/Automata.h"

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

extern TS_AUTOMATA dpd;

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/

/**
 * @brief  Ejecuta el autómata
 *
 * @param elAutomata Puntero al autómata
 *
 * @return void
 *
 * Consulta el estado del autómata y ejecuta cada uno de los estados
 * que detecta
 */

void AUTOMATA_ejecuta_automata(TS_AUTOMATA *elAutomata){

	TS_ESTADO **Indx;    /* Valor índice rastreador */

	for (Indx = elAutomata->estado; *Indx != NULL; ++Indx){

	    if (elAutomata->estadoActual == (*Indx)->id){

			AUTOMATA_ejecuta_estado(*Indx, elAutomata);

			return;

	    }

	}

}

/**
 * @brief  Ejecuta el estado
 *
 * @param elEstado Puntero al estado
 * @param elAutomata Puntero al autómata
 *
 * @return void
 *
 * Mira en el estado si hay algun evento y si es así, ejecuta la acción
 * que corresponde a ese evento
 */

void AUTOMATA_ejecuta_estado (TS_ESTADO *elEstado, TS_AUTOMATA *elAutomata){

	TS_EVEACC *Indx;   /* Índice de rastreo */

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
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
