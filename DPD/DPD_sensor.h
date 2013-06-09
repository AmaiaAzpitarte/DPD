/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : DPD_sensor.h  						  			    		**
** version : 1 									  							**
** date :  	2013-06-09		 		 									    **
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
**Date : 2013-06-09									 					    **
**Revised by : Amaia Azpitarte	          									**
**Description : Original version.							  				**
*****************************************************************************/

#define _DPD_SENSOR_H

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

typedef enum {DPD_ESPERA, UNA_LINEA, DOS_LINEAS, TRES_LINEAS, MENU_PRIMERO,
	MENU_SEGUNDO, MENU_TERCERO, SENSOR, INCORRECTO, CORRECTO} estados; /* Los estados del DPD */


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

//Transiciones desde el estado DPD_ESPERA
tBoolean SEM_EVENTO_finDPD_ESPERA();


//Transiciones desde el estado UNA_LINEA
tBoolean SEM_EVENTO_finSENSOR();

tBoolean SEM_EVENTO_finPULSADA_INC();

tBoolean SEM_EVENTO_finUNA_LINEA();


//Transiciones desde el estado DOS_LINEAS
tBoolean SEM_EVENTO_finMENU();

tBoolean SEM_EVENTO_finDOS_LINEAS();


//Transicion desde el estado TRES_LINEAS
tBoolean SEM_EVENTO_finMENU_DOS();


//Transiciones desde el estado MENU_PRIMERO
tBoolean SEM_EVENTO_finQUEDAN_DOS();

tBoolean SEM_EVENTO_finQUEDAN_TRES();

tBoolean SEM_EVENTO_finMENU_TRES();

tBoolean SEM_EVENTO_finSENSOR_PRIMERO();

tBoolean SEM_EVENTO_finPULSADA_PRIMERO();


//Transiciones desde el estado MENUN_SEGUNDO
tBoolean SEM_EVENTO_finMENU_CUATRO();

tBoolean SEM_EVENTO_finEXISTEN_DOS();

tBoolean SEM_EVENTO_finEXISTEN_TRES();

tBoolean SEM_EVENTO_finMENU_CINCO();

tBoolean SEM_EVENTO_finSENSOR_SEGUNDO();

tBoolean SEM_EVENTO_finPULSADA_SEGUNDO();


//Transiciones desde el estado MENU_TERCERO
tBoolean SEM_EVENTO_finMENU_SEIS();

tBoolean SEM_EVENTO_finHAY_TRES();

tBoolean SEM_EVENTO_finSENSOR_TERCERO();

tBoolean SEM_EVENTO_finPULSADA_TERCERO();


//Transiciones desde el estado SENSOR
tBoolean SEM_EVENTO_finPULSADA_COR();

tBoolean SEM_EVENTO_finINCORRECTO();


//Transiciones desde el estado INCORRECTA
tBoolean SEM_EVENTO_finSIGUE_UNO();

tBoolean SEM_EVENTO_finSIGUEN_DOS();

tBoolean SEM_EVENTO_finSIGUEN_TRES();


//Transiciones desde el estado CORRECTA
tBoolean SEM_EVENTO_finESTA_UNO();

tBoolean SEM_EVENTO_finESTAN_DOS();

tBoolean SEM_EVENTO_finESTAN_TRES();

tBoolean SEM_EVENTO_finREALIZADA();




//Acciones que realizar en los estados

void SEM_ACCION_dpd_espera();

void SEM_ACCION_una_linea();

void SEM_ACCION_dos_lineas();

void SEM_ACCION_tres_lineas();

void SEM_ACCION_menu_primero();

void SEM_ACCION_menu_segundo();

void SEM_ACCION_menu_tercero();

void SEM_ACCION_sensor();

void SEM_ACCION_incorrecto();

void SEM_ACCION_correcto();


/*//Funci�n que consulta si la operaci�n es la �ltima de un pedido

void pedido_finalizado(final);*/

/*****************************************************************************
**                                                                          **
** EOF                                                                      **
**                                                                          **
******************************************************************************/