/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : displayGenerico.h  			 					    		**
** version : 1 									  							**
** date :  	2013-06-03		 		 									    **
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
**Date : 2013-06-03									 					    **
**Revised by : Amaia Azpitarte	          									**
**Description : Original version.							  				**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

#ifndef _DISPLAY_GENERICO_H

#define _DISPLAY_GENERICO_H

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void DISPLAY_GENERICO_dibuja_string(const char *pcStr, unsigned long ulX,
        unsigned long ulY, unsigned char ucLevel);

void DISPLAY_GENERICO_dibuja_imagen(unsigned char *pucImage, int ulX,
        int ulY, int ulWidth, int ulHeight);

void DISPLAY_GENERICO_init();

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

#ifndef DISPLAY_RIT_C

#define PUB_DISPLAY_RIT extern

#else

#define PUB_DISPLAY_RIT

#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/

#endif
