/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : data_structs.h  				  					    		**
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

#define _DATA_STRUCTS_H

/*****************************************************************************
**                                                                          **
** MODULES USED                                                             **
**                                                                          **
****************************************************************************/
/*****************************************************************************
**                                                                          **
** DEFINITIONS AND MACROS                                                   **
**                                                                          **
******************************************************************************/
/*****************************************************************************
**                                                                          **
** TYPEDEFS AND STRUCTURES                                                  **
**                                                                          **
*****************************************************************************/


//Estructura de una linea de pedido o una reposicion
typedef struct{
	int id_pedido;
	int operario;
	int cantidad;
	int confirmacion; //en realidad puede ser un booleano
	int final; // en realidad puede ser un booleano
}t_lineapedido;

/*****************************************************************************
**                                                                          **
** EXPORTED VARIABLES                                                       **
**                                                                          **
*****************************************************************************/
/*****************************************************************************
**                                                                          **
** EXPORTED FUNCTIONS                                                       **
**                                                                          **
******************************************************************************/
/*****************************************************************************
**                                                                          **
** EOF                                                                      **
**                                                                          **
******************************************************************************/