/*************************************************************************************
** @file    sonido.h																**
** @brief   Cabecera del fichero sonido.c											**
** @par		Declaraciones															**
**			- FRECUENCIA_SILENCIO	Indica la frecuencia de silencio del sonido		**
**			- FRECUENCIA_DO			Indica la frecuencia de sonido de la nota do	**
** @author  Amaia Azpitarte															**
** @date    2013-06-05																**
*************************************************************************************/

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
*****************************************************************************/
#ifndef SONIDO_H
#define SONIDO_H

#define FRECUENCIA_SILENCIO 40000 // frecuencia de silencio
#define FRECUENCIA_DO 262 // frecuencia de la nota do
/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
*****************************************************************************/

void SONIDO_init();

void SONIDO_reproducir_nota();

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef SONIDO_C
#define PUB_SONIDO extern
#else
#define PUB_SONIDO
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/
#endif
