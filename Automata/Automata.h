/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : Automata.h  					  					    		**
** version : 1 									  							**
** date :  	2013-06-03		 		 									    **
** 											  								**
******************************************************************************
** 											  								**
**                      											  		**
**  								  					                    **
** 											  								**
******************************************************************************
**										        							**
**VERSION HISTORY:									  						**
**----------------									  						**
**Version : 1										  						**
**Date : 2013-06-03									 					    **
**Revised by : Amaia Azpitarte	          									**
**Description : Original version.							  				**
*****************************************************************************/

#define _AUTOMATA_H

/*****************************************************************************
**                                                                          **
** MODULES USED                                                             **
**                                                                          **
****************************************************************************/

#include "inc/hw_types.h"

/*****************************************************************************
**                                                                          **
** DEFINITIONS AND MACROS                                                   **
**                                                                          **
******************************************************************************/

#define BYTE unsigned char
#define NULL 0
#define PRIVATE static

/**
 * @brief Macros para la definición del autómata y sus elementos
 */

#define ITEM_EVAC( nombre , evento , accion ) { nombre , #nombre , evento, accion}

#define ESTADO(nombre)\
        PRIVATE const TS_EVEACC x##nombre[] = {

#define FIN_ESTADO(nombre, ident, control)\
		,{0,NULL,NULL,NULL} };\
		PRIVATE TS_ESTADO nombre =\
		{ident, #ident, control, (TS_EVEACC *) x##nombre};

#define AUTOMATA(nombre)\
		PRIVATE TS_ESTADO * (x##nombre[]) = {

#define FIN_AUTOMATA(nombre,ident, StopC)\
		,NULL };\
		TS_AUTOMATA nombre =\
		{ident, #nombre, StopC, (TS_ESTADO **) x##nombre};

/*****************************************************************************
**                                                                          **
** TYPEDEFS AND STRUCTURES                                                  **
**                                                                          **
*****************************************************************************/

typedef void (*TPFN_ACC)(void); 	/* Puntero a una función acción */
typedef tBoolean (*TPFN_EVE)(void); /* Puntero a una función evento */

// Transición

typedef struct {
	  BYTE          id;             /* Identificador del estado destino */
	  char        * nombre;         /* Nombre identificativo de depuración */
	  TPFN_EVE      evento;         /* Puntero a la función evento */
	  TPFN_ACC      accion;         /* Puntero a la función acción */
} TS_EVEACC;

//Estado

typedef struct {
	  BYTE          id;             /* Identificador del estado */
	  char        * nombre;         /* Nombre identificativo de depuración */
	  TPFN_ACC      controles;      /* Función de control del estado */
	  TS_EVEACC   * funcion;        /* Punteros a las funciones del estado */
} TS_ESTADO;

// Automata

typedef struct {
	  BYTE          id;             /* Identificador del autómata */
	  char        * nombre;         /* Nombre identificativo de depuración */
	  TPFN_EVE      StopCond;       /* Condición necesaria para la ejecución */
	  TS_ESTADO   **estado;         /* Matriz de punteros a los estados */
	  BYTE			estadoActual;	/* Indica el estado actual del autómata */
} TS_AUTOMATA;


/*****************************************************************************
**                                                                          **
** EXPORTED VARIABLES                                                       **
**                                                                          **
*****************************************************************************/
/*****************************************************************************
**                                                                          **
** EXPORTED FUNCTIONS                                                       **
**                                                                          **
******************************************************************************/

/**
 * @brief  Ejecuta el autómata
 *
 * @param elAutomata Puntero al autómata
 *
 * @return void
 */

void EjecutaAutomata( TS_AUTOMATA *elAutomata);

/**
 * @brief  Ejecuta el estado
 *
 * @param elEstado Puntero al estado
 * @param elAutomata Puntero al automata
 *
 * @return void
 */

void EjecutaEstado  ( TS_ESTADO *elEstado, TS_AUTOMATA *elAutomata);

/*****************************************************************************
**                                                                          **
** EOF                                                                      **
**                                                                          **
******************************************************************************/
