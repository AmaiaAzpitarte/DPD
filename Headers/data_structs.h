/*********************************************************************************************************************************************************************
** @file    data_structs.h																																			**
** @brief   Se define la estructura de una linea de pedido																											**
** @par		Declaraciones:																																			**
**			- t_lineapedido Define la estructura de una linea de pedido, con los siguientes elementos:																**
**				- id_pedido		Identificador del pedido al que pertenece la l&iacute;nea de pedido																	**
**				- operario		Operario que debe realizar la l&iacute;nea																							**
**				- cantidad 		Cantidad que se debe coger de la ubicaci&oacute;n del DPD																			**
**				- confirmacion	Indica el estado de la l&iacute;nea de pedido (sin realizar, confirmado, error de confirmaci&oacute;n, error de ubicaci&oacute;n)	**
**				- final			Indica si la l&iacute;nea de pedido a realizar es la &uacute;ltima de un pedido														**
** @author  Amaia Azpitarte																																			**
** @date    2013-06-03																																				**
*********************************************************************************************************************************************************************/
#ifndef _DATA_STRUCTS_H
#define _DATA_STRUCTS_H
/*****************************************************************************
**                                                                          **
** MODULES USED                                                             **
**                                                                          **
*****************************************************************************/
/*****************************************************************************
**                                                                          **
** DEFINITIONS AND MACROS                                                   **
**                                                                          **
*****************************************************************************/
/*****************************************************************************
**                                                                          **
** EXPORTED VARIABLES                                                       **
**                                                                          **
*****************************************************************************/
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
	int confirmacion;
	int final; // puede ser un booleano
}t_lineapedido;

/*****************************************************************************
**                                                                          **
** EOF                                                                      **
**                                                                          **
*****************************************************************************/
#endif
