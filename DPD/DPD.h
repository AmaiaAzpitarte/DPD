/**
 * @file    DPD.h
 * @brief   Cabecera del fichero DPD.c
 * @enum	Declaraciones
 *			- \b DPD_ESPERA	Estado DPD_ESPERA de la m&aacute;quina de estados
 *			- \b UNA_LINEA		Estado UNA_LINEA de la m&aacute;quina de estados
 *			- \b CONFIRMACION	Estado CONFIRMACION de la m&aacute;quina de estados
 *			- \b DOS_LINEAS	Estado DOS_LINEAS de la m&aacute;quina de estados
 *			- \b TRES_LINEAS	Estado TRES_LINEAS de la m&aacute;quina de estados
 *			- \b MENU_PRIMERO	Estado MENU_PRIMERO de la m&aacute;quina de estados
 *			- \b MENU_SEGUNDO	Estado MENU_SEGUNDO de la m&aacute;quina de estados
 *			- \b MENU_TERCERO	Estado MENU_TERCERO de la m&aacute;quina de estados
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

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
** PROTOTYPES OF GLOBAL FUNCTIONS                                           **
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

//ESTADOS DE LA MÁQUINA DE ESTADOS SIN SENSOR
typedef enum {DPD_ESPERA, UNA_LINEA, CONFIRMACION, DOS_LINEAS, TRES_LINEAS, MENU_PRIMERO,
				MENU_SEGUNDO, MENU_TERCERO} estados; // Los estados del DPD sin sensor


#ifndef _DPD_H
#define _PUB_DPD extern
#else
#define _PUB_DPD
#endif

/*****************************************************************************
**                                                                          **
** EOF                                                                      **
**                                                                          **
*****************************************************************************/

#endif
