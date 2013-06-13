/**
 * @file    leds.h
 * @brief   Cabecera del fichero leds.c
 * @author  Amaia Azpitarte
 * @date    2013-06-06
 */

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

#ifndef LEDS_H
#define LEDS_H

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void LEDS_init();

void LEDS_controlar_leds(int leds);

void LEDS_escoger_leds(int operario);

void LEDS_escoger_leds_dos_lineas();

void LEDS_escoger_leds_tres_lineas();

//int LEDS_consultar_operarios(int operario);

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

#ifndef LEDS_C
#define PUB_LEDS extern
#else
#define PUB_LEDS
#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
