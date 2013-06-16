/**
 * @file    sensor.h
 * @brief   Cabecera del fichero sensor.c
 * @author  Amaia Azpitarte
 * @date    2013-06-10
 */

#ifndef _SENSOR_H
#define _SENSOR_H

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

void SENSOR_init();

void SENSOR_detectar_movimiento();

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

#ifndef _SENSOR_C
#define _PUB_SENSOR extern
#else
#define _PUB_SENSOR
#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/

#endif
