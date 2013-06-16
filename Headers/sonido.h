/**
 * @file    sonido.h
 * @brief   Cabecera del fichero sonido.c
 * @par		Declaraciones
 *			- \b FRECUENCIA_SILENCIO	Indica la frecuencia de silencio del sonido
 *			- \b FRECUENCIA_DO			Indica la frecuencia de sonido de la nota do
 * @author  Amaia Azpitarte
 * @date    2013-06-05
 */

#ifndef _SONIDO_H
#define _SONIDO_H

/*****************************************************************************
** 																			**
** MODULES USED																**
** 																			**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
*****************************************************************************/

// Frecuencia de silencio
#define FRECUENCIA_SILENCIO 40000

// Frecuencia de la nota do
#define FRECUENCIA_DO 262

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
*****************************************************************************/

void SONIDO_init();

void SONIDO_reproducir_nota();

/*****************************************************************************
** 																			**
** EXPORTED VARIABLES														**
** 																			**
*****************************************************************************/
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

#ifndef _SONIDO_C
#define _PUB_SONIDO extern
#else
#define _PUB_SONIDO
#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/

#endif
