/*********************************************************************************
** @file    DPD.h																**
** @brief   Cabecera del fichero DPD.c											**
** @enum	Declaraciones														**
**			- DPD_ESPERA	Estado DPD_ESPERA de la m&aacute;quina de estados	**
**			- UNA_LINEA		Estado UNA_LINEA de la m&aacute;quina de estados	**
**			- CONFIRMACION	Estado CONFIRMACION de la m&aacute;quina de estados	**
**			- DOS_LINEAS	Estado DOS_LINEAS de la m&aacute;quina de estados	**
**			- TRES_LINEAS	Estado TRES_LINEAS de la m&aacute;quina de estados	**
**			- MENU_PRIMERO	Estado MENU_PRIMERO de la m&aacute;quina de estados	**
**			- MENU_SEGUNDO	Estado MENU_SEGUNDO de la m&aacute;quina de estados	**
**			- MENU_TERCERO	Estado MENU_TERCERO de la m&aacute;quina de estados	**
** @author  Amaia Azpitarte														**
** @date    2013-06-03															**
*********************************************************************************/

#include "DPD_Config.h"

#ifndef DPD_SENSOR

#define _DPD_H

/*****************************************************************************
**                                                                          **
** MODULES USED                                                             **
**                                                                          **
*****************************************************************************/

#include "inc/hw_types.h"

/*****************************************************************************
**                                                                          **
** DEFINITIONS AND MACROS                                                   **
**                                                                          **
*****************************************************************************/
/*****************************************************************************
**                                                                          **
** TYPEDEFS AND STRUCTURES                                                  **
**                                                                          **
*****************************************************************************/

//ESTADOS DE LA MAQUINA DE ESTADOS
typedef enum {DPD_ESPERA, UNA_LINEA, CONFIRMACION, DOS_LINEAS, TRES_LINEAS, MENU_PRIMERO,
				MENU_SEGUNDO, MENU_TERCERO} estados; /* Los estados del DPD */

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
#endif
