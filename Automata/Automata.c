/*********************************************************************
** 																	**
** project : DPD				 									**
** filename : Automata.c		 									**
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
 * @brief  Ejecuta el aut�mata
 *
 * @param elAutomata Puntero al aut�mata
 *
 * @return void
 *
 * Consulta el estado del aut�mata y ejecuta cada uno de los estados
 * que detecta
 */

void AUTOMATA_ejecuta_automata(TS_AUTOMATA *elAutomata){

	TS_ESTADO **Indx;    /* Valor �ndice rastreador */

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
 * @param elAutomata Puntero al aut�mata
 *
 * @return void
 *
 * Mira en el estado si hay algun evento y si es as�, ejecuta la acci�n
 * que corresponde a ese evento
 */

void AUTOMATA_ejecuta_estado (TS_ESTADO *elEstado, TS_AUTOMATA *elAutomata){

	TS_EVEACC *Indx;   /* �ndice de rastreo */

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
