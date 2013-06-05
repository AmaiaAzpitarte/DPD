/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : keypad.h  					  					    		**
** version : 1 									  							**
** date :  	2013-06-05		 		 									    **
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
**Date : 2013-06-05									 					    **
**Revised by : Amaia Azpitarte	          									**
**Description : Original version.							  				**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

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
#define KEY_SELECT 15 //01111

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void DPD_inicializacion_keypad();

void DPD_leer_keypad();

void DPD_elegir_tecla();

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
******************************************************************************/
#endif
