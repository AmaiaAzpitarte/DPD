/**
 * @file    display.h
 * @brief   Cabecera del fichero display.c
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

#ifndef _DISPLAY_H

#define _DISPLAY_H

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void DISPLAY_inicializacion_display();

void DISPLAY_escribir_en_pantalla(unsigned char *puc, int x, int y);

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

#ifndef DISPLAY_C

#define PUB_DISPLAY extern

#else

#define PUB_DISPLAY

#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/

#endif
