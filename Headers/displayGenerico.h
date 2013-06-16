/**
 * @file    displayGenerico.h
 * @brief   Cabecera del fichero displayRIT.c
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#ifndef _DISPLAY_GENERICO_H
#define _DISPLAY_GENERICO_H

/*****************************************************************************
** 																			**
** MODULES USED			 													**
** 																			**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
*****************************************************************************/
/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
*****************************************************************************/

void DISPLAY_GENERICO_dibuja_string(const char *pcStr, unsigned long ulX,
        unsigned long ulY, unsigned char ucLevel);

void DISPLAY_GENERICO_dibuja_imagen(unsigned char *pucImage, int ulX,
        int ulY, int ulWidth, int ulHeight);

void DISPLAY_GENERICO_init();

/*****************************************************************************
** 																			**
** EXPORTED VARIABLES	 													**
** 																			**
*****************************************************************************/
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

#ifndef _DISPLAY_RIT_C
#define _PUB_DISPLAY_RIT extern
#else
#define _PUB_DISPLAY_RIT
#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/

#endif
