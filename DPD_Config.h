/**
 * @file    DPD_Config.h
 * @brief  	En este fichero, se definen las configuraciones del DPD
 * @par		Declaraciones
 *			- \b DPD_SENSOR		Indica si el DPD dispone de sensor o no
 *			- \b TIMER_ESPERA	Indica el tiempo de espera del timer_0
 * @author  Amaia Azpitarte
 * @date    2013-06-10
 */

#ifndef _DPD_CONFIG_H
#define _DPD_CONFIG_H

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

// Para ejecutar DPD SIN SENSOR, comentar la siguiente linea
// Para ejecutar DPD CON SENSOR, utilizar la siguiente linea
//#define	DPD_SENSOR	1

// Indica que el timer esperará 5 segundos
#define TIMER_ESPERA  5

/*****************************************************************************
**	 																		**
** PROTOTYPES OF GLOBAL FUNCTIONS		 									**
** 																			**
*****************************************************************************/
/*****************************************************************************
**	 																		**
** EXPORTED VARIABLES														**
** 																			**
*****************************************************************************/
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/

#endif
