/**
 * @file    Automata.h
 * @brief   Cabecera del fichero Automata.c
 * @par		Declaraciones
 *			- \b BYTE
 *			- \b NULL
 *			- \b PRIVATE
 *			- \b ITEM_EVAC
 *			- \b ESTADO		Macro del estado del aut&oacute;mata
 *			- \b FIN_ESTADO	Macro de fin de estado del aut&oacute;mata
 *			- \b AUTOMATA		Macro del aut&oacute;mata
 *			- \b FIN_AUTOMATA	Macro del fin del aut&oacute;mata
 *			- \b TS_EVEACC		Estructura de las transiciones del aut&oacute;mata
 *			- \b TS_ESTADO		Estructura de los estados del aut&oacute;mata
 *			- \b TS_AUTOMATA	Estructura del aut&oacute;mata
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#ifndef _AUTOMATA_H
#define _AUTOMATA_H

/*****************************************************************************
**                                                                          **
** MODULES USED                                                             **
**                                                                          **
*****************************************************************************/

#include "inc/hw_types.h"

/*****************************************************************************
**                                                                          **
** DEFINITIONS AND MACROS                                                   **
**                                                                          **
*****************************************************************************/

#define BYTE unsigned char
#define NULL 0
#define PRIVATE static

/**
 * @brief Macros para la definici&oacute;n del aut&oacute;mata y sus elementos
 */
#define ITEM_EVAC(nombre, evento, accion) {nombre, #nombre, evento, accion}

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
** EXPORTED VARIABLES                                                       **
**                                                                          **
*****************************************************************************/
/*****************************************************************************
**                                                                          **
** TYPEDEFS AND STRUCTURES                                                  **
**                                                                          **
*****************************************************************************/

typedef void (*TPFN_ACC)(void); 	/* Puntero a una función acción */
typedef tBoolean (*TPFN_EVE)(void); /* Puntero a una función evento */

// TRANSICIÓN

typedef struct {
	  BYTE          id;             /* Identificador del estado destino */
	  char        * nombre;         /* Nombre identificativo de depuración */
	  TPFN_EVE      evento;         /* Puntero a la función evento */
	  TPFN_ACC      accion;         /* Puntero a la función acción */
} TS_EVEACC;

// ESTADO

typedef struct {
	  BYTE          id;             /* Identificador del estado */
	  char        * nombre;         /* Nombre identificativo de depuración */
	  TPFN_ACC      controles;      /* Función de control del estado */
	  TS_EVEACC   * funcion;        /* Punteros a las funciones del estado */
} TS_ESTADO;

// AUTÓMATA

typedef struct {
	  BYTE          id;             /* Identificador del autómata */
	  char        * nombre;         /* Nombre identificativo de depuración */
	  TPFN_EVE      StopCond;       /* Condición necesaria para la ejecución */
	  TS_ESTADO   **estado;         /* Matriz de punteros a los estados */
	  BYTE			estadoActual;	/* Indica el estado actual del autómata */
} TS_AUTOMATA;

/*****************************************************************************
**                                                                          **
** PROTOTYPES OF GLOBAL FUNCTIONS                                           **
**                                                                          **
*****************************************************************************/

void AUTOMATA_ejecuta_automata(TS_AUTOMATA *elAutomata);


#ifndef _AUTOMATA_C
#define _PUB_AUTOMATA extern
#else
#define _PUB_AUTOMATA
#endif

/*****************************************************************************
**                                                                          **
** EOF                                                                      **
**                                                                          **
*****************************************************************************/

#endif
