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
 * @brief Macros para la definici�n del aut�mata y sus elementos
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

typedef void (*TPFN_ACC)(void); 	/* Puntero a una funci�n acci�n */
typedef tBoolean (*TPFN_EVE)(void); /* Puntero a una funci�n evento */

// Transici�n

typedef struct {
	  BYTE          id;             /* Identificador del estado destino */
	  char        * nombre;         /* Nombre identificativo de depuraci�n */
	  TPFN_EVE      evento;         /* Puntero a la funci�n evento */
	  TPFN_ACC      accion;         /* Puntero a la funci�n acci�n */
} TS_EVEACC;

//Estado

typedef struct {
	  BYTE          id;             /* Identificador del estado */
	  char        * nombre;         /* Nombre identificativo de depuraci�n */
	  TPFN_ACC      controles;      /* Funci�n de control del estado */
	  TS_EVEACC   * funcion;        /* Punteros a las funciones del estado */
} TS_ESTADO;

// Automata

typedef struct {
	  BYTE          id;             /* Identificador del aut�mata */
	  char        * nombre;         /* Nombre identificativo de depuraci�n */
	  TPFN_EVE      StopCond;       /* Condici�n necesaria para la ejecuci�n */
	  TS_ESTADO   **estado;         /* Matriz de punteros a los estados */
	  BYTE			estadoActual;	/* Indica el estado actual del aut�mata */
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
 * @brief  Ejecuta el aut�mata
 *
 * @param elAutomata Puntero al aut�mata
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
