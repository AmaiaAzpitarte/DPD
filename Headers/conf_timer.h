/**
 * @file    conf_timer.h
 * @brief   Cabecera del fichero conf_timer.c
 * @author  Amaia Azpitarte
 * @date    2013-06-11
 */

#ifndef _CONF_TIMER_H
#define _CONF_TIMER_H

/*****************************************************************************
** 																			**
** MODULES USED			 													**
** 																			**
*****************************************************************************/

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

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

void TIMER_init_timer0(int);

void TIMER_enable_timer0(void);

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

#ifndef _CONF_TIMER_C
#define _PUB_CONF_TIMER extern
#else
#define _PUB_CONF_TIMER
#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/

#endif
