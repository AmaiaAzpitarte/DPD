/**
 * @file    conf_timer.h
 * @brief   Cabecera del fichero conf_timer.c
 * @author  Amaia Azpitarte
 * @date    2013-06-11
 */

/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
#ifndef CONFIG_TIMER_H_
#define CONFIG_TIMER_H_


#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void TIMER_init_timer0(int);
void TIMER_enable_timer0(void);

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef CONF_TIMER_C
#define PUB_CONF_TIMER extern
#else
#define PUB_CONF_TIMER
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
