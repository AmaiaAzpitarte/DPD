/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : DPD.h  						  					    		**
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

#include "DPD_Config.h"

#ifndef DPD_SENSOR

#define _DPD_H

/*****************************************************************************
**                                                                          **
** MODULES USED                                                             **
**                                                                          **
****************************************************************************/

#include "inc/hw_types.h"

/*****************************************************************************
**                                                                          **
** DEFINITIONS AND MACROS                                                   **
**                                                                          **
******************************************************************************/

//ESTADOS DE LA MAQUINA DE ESTADOS

typedef enum {DPD_ESPERA, UNA_LINEA, CONFIRMACION, DOS_LINEAS, TRES_LINEAS, MENU_PRIMERO,
				MENU_SEGUNDO, MENU_TERCERO} estados; /* Los estados del DPD */


/*****************************************************************************
**                                                                          **
** TYPEDEFS AND STRUCTURES                                                  **
**                                                                          **
*****************************************************************************/
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

/*//Transiciones desde el estado DPD_ESPERA
tBoolean SEM_EVENTO_finDPD_ESPERA();

//Transiciones desde el estado UNA_LINEA
tBoolean SEM_EVENTO_finPULSADA();

tBoolean SEM_EVENTO_finUNA_LINEA();

//Transiciones desde el estado CONFIRMACION
tBoolean SEM_EVENTO_finCONFIRMACION();

tBoolean SEM_EVENTO_finQUEDA_UNA();

tBoolean SEM_EVENTO_finQUEDAN_DOS();

tBoolean SEM_EVENTO_finQUEDAN_TRES();

//Transiciones desde el estado DOS_LINEAS
tBoolean SEM_EVENTO_finMENU();

tBoolean SEM_EVENTO_finTERCERA();

//Transicion desde el estado TRES_LINEAS
tBoolean SEM_EVENTO_finTRES_LINEAS();

//Transiciones desde el estado MENU_PRIMERO
tBoolean SEM_EVENTO_finCONF_UNO();

tBoolean SEM_EVENTO_finDOS();

tBoolean SEM_EVENTO_finTRES();

tBoolean SEM_EVENTO_finMENU_DOS();

//Transiciones desde el estado MENUN_SEGUNDO
tBoolean SEM_EVENTO_finCONF_DOS();

tBoolean SEM_EVENTO_finEXISTEN_DOS();

tBoolean SEM_EVENTO_finEXISTEN_TRES();

tBoolean SEM_EVENTO_finHAY_DOS();

tBoolean SEM_EVENTO_finHAY_TRES();

//Transiciones desde el estado MENU_TERCERO
tBoolean SEM_EVENTO_finCONF_TRES();

tBoolean SEM_EVENTO_finMENU_UNO();

tBoolean SEM_EVENTO_finSIGUEN_TRES();




//Acciones que realizar en los estados

void SEM_ACCION_dpd_espera();

void SEM_ACCION_una_linea();

void SEM_ACCION_confirmacion();

void SEM_ACCION_dos_lineas();

void SEM_ACCION_tres_lineas();

void SEM_ACCION_menu_primero();

void SEM_ACCION_menu_segundo();

void SEM_ACCION_menu_tercero();


//Funci�n que consulta si la operaci�n es la �ltima de un pedido

void DPD_pedido_finalizado(int final);


void DPD_emitir_sonido();*/

/*****************************************************************************
**                                                                          **
** EOF                                                                      **
**                                                                          **
******************************************************************************/
#endif
