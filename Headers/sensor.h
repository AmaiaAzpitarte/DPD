/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : sensor.h  					  					    		**
** version : 1 									  							**
** date :  	2013-06-10		 		 									    **
** 											  								**
******************************************************************************
** 											  								**
** 							                            			  		**
**  								  					                    **
** 											  								**
******************************************************************************
**										        							**
**VERSION HISTORY:									  						**
**----------------									  						**
**Version : 1										  						**
**Date : 2012-06-10									 					    **
**Revised by : Amaia Azpitarte					  							**
**Description : Original version.							  				**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

#ifndef SENSOR_H
#define SENSOR_H

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void DPD_inicializacion_sensor();

void DPD_detectar_movimiento();

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef SENSOR_C
#define PUB_SENSOR extern
#else
#define PUB_SENSOR
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
