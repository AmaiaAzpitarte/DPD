/**
 * @file    keypad.h
 * @brief   Cabecera del fichero keypad.c
 * @par		Declaraciones
 *			- \b UP			Indica la tecla UP
 *			- \b DOWN			Indica la tecla DOWN
 *			- \b LEFT			Indica la tecla LEFT
 *			- \b RIGHT			Indica la tecla RIGHT
 *			- \b SELECT		Indica la tecla SELECT
 *			- \b NADA			Indica que no se ha pulsado ninguna tecla
 *			- \b KEY_UP		Indica que la tecla pulsada es UP
 *			- \b KEY_DOWN		Indica que la tecla pulsada es DOWN
 *			- \b KEY_LEFT		Indica que la tecla pulsada es LEFT
 *			- \b KEY_RIGHT		Indica que la tecla pulsada es RIGHT
 *			- \b KEY_SELECT	Indica que la tecla pulsada es SELECT
 * @author  Amaia Azpitarte
 * @date    2013-06-05
 */

#ifndef _KEYPAD_H
#define _KEYPAD_H

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

// Definición de las teclas para la varibale pulsada
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SELECT 5
#define NADA 6

// Definición de las teclas
#define KEY_UP 0x1e     //11110
#define KEY_DOWN 0x1d   //11101
#define KEY_LEFT 0x1b   //11011
#define KEY_RIGHT 0x17  //10111
#define KEY_SELECT 15 	//01111

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
*****************************************************************************/

void KEYPAD_init();

void KEYPAD_leer_keypad();

void KEYPAD_elegir_tecla();

/*****************************************************************************
** 																			**
** EXPORTED FUNCTIONS	 													**
** 																			**
*****************************************************************************/
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

#ifndef _KEYPAD_C
#define _PUB_KEYPAD extern
#else
#define _PUB_KEYPAD
#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/

#endif
