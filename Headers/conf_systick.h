/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : systick.h  					  					    		**
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
**Revised by : Amaia Azpitarte	              	  							**
**Description : Original version.							  				**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
#ifndef SYSTICK_H
#define SYSTICK_H
/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void SysTick_Handler(void);

void initSysTick();

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef SYSTICK_C
#define PUB_SYSTICK extern
#else
#define PUB_SYSTICK
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif