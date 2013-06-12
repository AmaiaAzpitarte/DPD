/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : sonido.h  					  					    		**
** version : 1 									  							**
** date :  	2013-06-05		 		 									    **
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
**Date : 2012-06-05									 					    **
**Revised by : Amaia Azpitarte					  							**
**Description : Original version.							  				**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

#ifndef SONIDO_H
#define SONIDO_H

#define FRECUENCIA_SILENCIO 40000
#define FRECUENCIA_DO 262
#define FRECUENCIA_RE 294
#define FRECUENCIA_MI 330
#define FRECUENCIA_FA 349
#define FRECUENCIA_SOL 392

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void SONIDO_init();

void SONIDO_reproducir_nota();

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/
#ifndef SONIDO_C
#define PUB_SONIDO extern
#else
#define PUB_SONIDO
#endif
/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/
#endif
