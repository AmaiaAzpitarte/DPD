/*****************************************************************************
**											  								**
** project :  DPD.h							 							  	**
** filename : clock.h  						  					    		**
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
**Revised by : Amaia Azpitarte	               	  							**
**Description : Original version.							  				**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/
#ifndef CLOCK_H
#define CLOCK_H
/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void DPD_inicializacion_clock();

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef CLOCK_C
#define PUB_CLOCK extern
#else
#define PUB_CLOCK
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
