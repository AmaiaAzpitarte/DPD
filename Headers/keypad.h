/*****************************************************************************
** @file    keypad.h														**
** @brief   Cabecera del fichero keypad.c									**
** @par		Declaraciones													**
**			- UP			Indica la tecla UP								**
**			- DOWN			Indica la tecla DOWN							**
**			- LEFT			Indica la tecla LEFT							**
**			- RIGHT			Indica la tecla RIGHT							**
**			- SELECT		Indica la tecla SELECT							**
**			- NADA			Indica que no se ha pulsado ninguna tecla		**
**			- KEY_UP		Indica que la tecla pulsada es UP				**
**			- KEY_DOWN		Indica que la tecla pulsada es DOWN				**
**			- KEY_LEFT		Indica que la tecla pulsada es LEFT				**
**			- KEY_RIGHT		Indica que la tecla pulsada es RIGHT			**
**			- KEY_SELECT	Indica que la tecla pulsada es SELECT			**
** @author  Amaia Azpitarte													**
** @date    2013-06-05														**
*****************************************************************************/

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
*****************************************************************************/

#ifndef KEYPAD_H
#define KEYPAD_H

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
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

#ifndef KEYPAD_C
#define PUB_KEYPAD extern
#else
#define PUB_KEYPAD
#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/
#endif
