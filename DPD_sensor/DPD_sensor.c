/**
 * @file    DPD.c
 * @brief   Fichero donde se definen los estados y las transiciones de la m&aacute;quina de estados con sensor
 * @par		L&oacute;gica
 *			- Se definen los estados de la m&aacute;quina de estados con sensor
 *			- Se definen las transiciones de la m&aacute;quina de estados con sensor
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#define _DPD_SENSOR_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include <string.h>

#include "Automata/Automata.h"
#include "DPD_sensor/DPD_sensor.h"
#include "Headers/keypad.h"

#include "Utiles/rit128x96x4.h"
#include "lm3slib/driverlib/gpio.h"

#include "Headers/received_data.h"
#include "Headers/data_structs.h"

#include "Headers/sonido.h"

#include "Headers/leds.h"

#include "Headers/conf_timer.h"

#include "DPD_Config.h"

#ifdef DPD_SENSOR

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** PROTOTYPES OF LOCAL FUNCTIONS 									**
** 																	**
*********************************************************************/

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

/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

// Variable en la que se guarda la tecla pulsada
extern char g_pulsada;

// Estructura donde se guardan los valores de la línea de pedido 1
extern t_lineapedido lineapedido_1;

// Estructura donde se guardan los valores de la línea de pedido 2
extern t_lineapedido lineapedido_2;

// Estructura donde se guardan los valores de la línea de pedido 3
extern t_lineapedido lineapedido_3;

// Variable que indica la cantidad de líneas de pedido que hay en el DPD
extern int g_linea;

// Varibale que indica cuándo finaliza de contar el timer 0
extern tBoolean g_timer_finished;

// Variable que indica el valor del sensor, si ha habido movimiento o no
extern int g_movimiento;

//Definición de los estados de la máquina de estados con sus respectivos eventos a otros estados y sus acciones

//Estado DPD_ESPERA y sus transiciones
ESTADO(dpd_espera)
	ITEM_EVAC(UNA_LINEA, SEM_EVENTO_finDPD_ESPERA, SEM_ACCION_una_linea)
FIN_ESTADO(dpd_espera, DPD_ESPERA, NULL)

//Estado UNA_LINEA y sus transiciones
ESTADO(una_linea)
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR, SEM_ACCION_sensor),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finPULSADA_INC, SEM_ACCION_incorrecto),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finUNA_LINEA, SEM_ACCION_dos_lineas)
FIN_ESTADO(una_linea, UNA_LINEA, NULL)

//Estado DOS_LINEAS y sus transiciones
ESTADO(dos_lineas)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU, SEM_ACCION_menu_primero),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finDOS_LINEAS, SEM_ACCION_tres_lineas)
FIN_ESTADO(dos_lineas, DOS_LINEAS, NULL)

//Estado TRES_LINEAS y sus transiciones
ESTADO(tres_lineas)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU_DOS, SEM_ACCION_menu_primero)
FIN_ESTADO(tres_lineas, TRES_LINEAS, NULL)

//Estado MENU_PRIMERO y sus transiciones
ESTADO(menu_primero)
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finQUEDAN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finQUEDAN_TRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(MENU_SEGUNDO, SEM_EVENTO_finMENU_TRES, SEM_ACCION_menu_segundo),
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR_PRIMERO, SEM_ACCION_sensor),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finPULSADA_PRIMERO, SEM_ACCION_incorrecto)
FIN_ESTADO(menu_primero, MENU_PRIMERO, NULL)

//Estado MENU_SEGUNDO y sus transiciones
ESTADO(menu_segundo)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU_CUATRO, SEM_ACCION_menu_primero),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finEXISTEN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finEXISTEN_TRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(MENU_TERCERO, SEM_EVENTO_finMENU_CINCO, SEM_ACCION_menu_tercero),
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR_SEGUNDO, SEM_ACCION_sensor),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finPULSADA_SEGUNDO, SEM_ACCION_incorrecto)
FIN_ESTADO(menu_segundo, MENU_SEGUNDO, NULL)

//Estado MENU_TERCERO y sus transiciones
ESTADO(menu_tercero)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU_SEIS, SEM_ACCION_menu_primero),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finHAY_TRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR_TERCERO, SEM_ACCION_sensor),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finPULSADA_TERCERO, SEM_ACCION_incorrecto)
FIN_ESTADO(menu_tercero, MENU_TERCERO, NULL)

//Estado SENSOR y sus transiciones
ESTADO(sensor)
	ITEM_EVAC(CORRECTO, SEM_EVENTO_finPULSADA_COR, SEM_ACCION_correcto),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finINCORRECTO, SEM_ACCION_incorrecto)
FIN_ESTADO(sensor, SENSOR, NULL)

//Estado INCORRECTO y sus transiciones
ESTADO(incorrecto)
	ITEM_EVAC(UNA_LINEA, SEM_EVENTO_finSIGUE_UNO, SEM_ACCION_una_linea),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finSIGUEN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finSIGUEN_TRES, SEM_ACCION_tres_lineas)
FIN_ESTADO(incorrecto, INCORRECTO, NULL)

//Estado CORRECTO y sus transiciones
ESTADO(correcto)
	ITEM_EVAC(UNA_LINEA, SEM_EVENTO_finESTA_UNO, SEM_ACCION_una_linea),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finESTAN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finESTAN_TRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(DPD_ESPERA, SEM_EVENTO_finREALIZADA, SEM_ACCION_dpd_espera)
FIN_ESTADO(correcto, CORRECTO, NULL)


AUTOMATA(dpd)
	&dpd_espera,
	&una_linea,
	&dos_lineas,
	&tres_lineas,
	&menu_primero,
	&menu_segundo,
	&menu_tercero,
	&sensor,
	&incorrecto,
	&correcto
FIN_AUTOMATA(dpd,1,NULL)

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

// Variable que indica el clock del sistema
unsigned long g_system_clock;

//Variable que se utiliza para escribir textos en el display
char *str;

// Variable que indica el estado que se ha confirmado
int g_estado_confirmado;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

//TRANSICIONES DESDE LOS ESTADOS

/**
 * @brief  	Transici&oacute;n del estado DPD_ESPERA a UNA_LINEA
 * @par		L&oacute;gica:
 * 			- Si se recibe alguna l&iacute;nea de pedido en el DPD (\e g_linea>=1), se realiza la transici&oacute;n al estado UNA_LINEA
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado UNA_LINEA
 */
tBoolean SEM_EVENTO_finDPD_ESPERA(){

	tBoolean ret;

	if(g_linea>=1) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado UNA_LINEA a SENSOR
 * @par		L&oacute;gica:
 * 			- Si se detecta movimiento (\e g_movimiento==1), se realiza la transici&oacute;n al estado SENSOR
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado SENSOR
 */
tBoolean SEM_EVENTO_finSENSOR(){

	tBoolean ret;

	if (g_movimiento==1) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado UNA_LINEA a INCORRECTO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla SELECT (se confirma la operaci&oacute;n), se realiza la transici&oacute;n al estado INCORRECTO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado INCORRECTO
 */
tBoolean SEM_EVENTO_finPULSADA_INC(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado UNA_LINEA a DOS_LINEAS
 * @par		L&oacute;gica:
 * 			- Si se recibe otra l&iacute;nea de pedido en el DPD (\e g_linea>=2), se realiza la transici&oacute;n al estado DOS_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado DOS_LINEAS
 */
tBoolean SEM_EVENTO_finUNA_LINEA(){

	tBoolean ret;

	if (g_linea>=2) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado DOS_LINEAS a MENU_PRIMERO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla UP (opci&oacute;n men&uacute;), se realiza la transici&oacute;n al estado MENU_PRIMERO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado MENU_PRIMERO
 */
tBoolean SEM_EVENTO_finMENU(){

	tBoolean ret;

	if (g_pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado DOS_LINEAS a TRES_LINEAS
 * @par		L&oacute;gica:
 * 			- Si se recibe otra l&iacute;nea de pedido en el DPD (\e g_linea==3), se realiza la transici&oacute;n al estado TRES_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado TRES_LINEAS
 */
tBoolean SEM_EVENTO_finDOS_LINEAS(){

	tBoolean ret;

	if (g_linea==3) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado TRES_LINEAS a MENU_PRIMERO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla UP (opci&oacute;n men&uacute;), se realiza la transici&oacute;n al estado MENU_PRIMERO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado MENU_PRIMERO
 */
tBoolean SEM_EVENTO_finMENU_DOS(){

	tBoolean ret;

	if (g_pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_PRIMERO a DOS_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y quedan dos l&iacute;neas de pedido en el DPD (\e g_linea==2), se realiza la transici&oacute;n al estado DOS_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado DOS_LINEAS
 */
tBoolean SEM_EVENTO_finQUEDAN_DOS(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==2)){
		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_PRIMERO a TRES_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y quedan tres l&iacute;neas de pedido en el DPD (\e g_linea==3), se realiza la transici&oacute;n al estado TRES_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado TRES_LINEAS
 */
tBoolean SEM_EVENTO_finQUEDAN_TRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==3)){
		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_PRIMERO a MENU_SEGUNDO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla UP (opci&oacute;n men&uacute;), se realiza la transici&oacute;n al estado MENU_SEGUNDO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado MENU_SEGUNDO
 */
tBoolean SEM_EVENTO_finMENU_TRES(){

	tBoolean ret;

	if (g_pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_PRIMERO a SENSOR
 * @par		L&oacute;gica:
 * 			- Si se detecta movimiento (\e g_movimiento==1), se realiza la transici&oacute;n al estado SENSOR
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado SENSOR
 */
tBoolean SEM_EVENTO_finSENSOR_PRIMERO(){

	tBoolean ret;

	if (g_movimiento==1) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_PRIMERO a INCORRECTO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla SELECT (se confirma la operaci&oacute;n), se realiza la transici&oacute;n al estado INCORRECTO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado INCORRECTO
 */
tBoolean SEM_EVENTO_finPULSADA_PRIMERO(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_SEGUNDO a MENU_PRIMERO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla UP (opci&oacute;n men&uacute;) y quedan dos l&iacute;neas de pedido en el DPD (e g_linea==2), se realiza la transici&oacute;n al estado MENU_PRIMERO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado MENU_PRIMERO
 */
tBoolean SEM_EVENTO_finMENU_CUATRO(){

	tBoolean ret;

	if ((g_pulsada==UP)&&(g_linea==2)) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_SEGUNDO a DOS_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y quedan dos l&iacute;neas de pedido en el DPD (\e g_linea==2), se realiza la transici&oacute;n al estado DOS_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado DOS_LINEAS
 */
tBoolean SEM_EVENTO_finEXISTEN_DOS(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==2)) {
		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_SEGUNDO a TRES_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y quedan tres l&iacute;neas de pedido en el DPD (\e g_linea==3), se realiza la transici&oacute;n al estado TRES_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado TRES_LINEAS
 */
tBoolean SEM_EVENTO_finEXISTEN_TRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==3)){
		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_SEGUNDO a MENU_TERCERO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla UP (opci&oacute;n men&uacute;) y quedan tres l&iacute;neas de pedido en el DPD (e g_linea==3), se realiza la transici&oacute;n al estado MENU_TERCERO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado MENU_TERCERO
 */
tBoolean SEM_EVENTO_finMENU_CINCO(){

	tBoolean ret;

	if ((g_pulsada==UP)&&(g_linea==3)) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_SEGUNDO a SENSOR
 * @par		L&oacute;gica:
 * 			- Si se detecta movimiento (\e g_movimiento==1), se realiza la transici&oacute;n al estado SENSOR
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado SENSOR
 */
tBoolean SEM_EVENTO_finSENSOR_SEGUNDO(){

	tBoolean ret;

	if (g_movimiento==1) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_SEGUNDO a INCORRECTO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla SELECT (se confirma la operaci&oacute;n), se realiza la transici&oacute;n al estado INCORRECTO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado INCORRECTO
 */
tBoolean SEM_EVENTO_finPULSADA_SEGUNDO(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_TERCERO a MENU_PRIMERO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla UP (opci&oacute;n men&uacute;), se realiza la transici&oacute;n al estado MENU_PRIMERO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado MENU_PRIMERO
 */
tBoolean SEM_EVENTO_finMENU_SEIS(){

	tBoolean ret;

	if (g_pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_TERCERO a TRES_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true), se realiza la transici&oacute;n al estado TRES_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado TRES_LINEAS
 */
tBoolean SEM_EVENTO_finHAY_TRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if (g_timer_finished){
		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_TERCERO a SENSOR
 * @par		L&oacute;gica:
 * 			- Si se detecta movimiento (\e g_movimiento==1), se realiza la transici&oacute;n al estado SENSOR
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado SENSOR
 */
tBoolean SEM_EVENTO_finSENSOR_TERCERO(){

	tBoolean ret;

	if (g_movimiento==1) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado MENU_TERCERO a INCORRECTO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla SELECT (se confirma la operaci&oacute;n), se realiza la transici&oacute;n al estado INCORRECTO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado INCORRECTO
 */
tBoolean SEM_EVENTO_finPULSADA_TERCERO(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado SENSOR a CORRECTO
 * @par		L&oacute;gica:
 * 			- Si se pulsa la tecla SELECT (se confirma la operaci&oacute;n), se realiza la transici&oacute;n al estado CORRECTO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado CORRECTO
 */
tBoolean SEM_EVENTO_finPULSADA_COR(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado SENSOR a INCORRECTO
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true), se realiza la transici&oacute;n al estado INCORRECTO
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado INCORRECTO
 */
tBoolean SEM_EVENTO_finINCORRECTO(){

	TIMER_enable_timer0();

	tBoolean ret;

	if (g_timer_finished){
		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado INCORRECTO a UNA_LINEA
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y queda una l&iacute;nea de pedido en el DPD (\e g_linea==1), se realiza la transici&oacute;n al estado UNA_LINEA
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado UNA_LINEA
 */
tBoolean SEM_EVENTO_finSIGUE_UNO(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==1)){
		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado INCORRECTO a DOS_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y quedan dos l&iacute;neas de pedido en el DPD (\e g_linea==2), se realiza la transici&oacute;n al estado DOS_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado DOS_LINEAS
 */
tBoolean SEM_EVENTO_finSIGUEN_DOS(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==2)){
		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado INCORRECTO a TRES_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y quedan tres l&iacute;neas de pedido en el DPD (\e g_linea==3), se realiza la transici&oacute;n al estado TRES_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado TRES_LINEAS
 */
tBoolean SEM_EVENTO_finSIGUEN_TRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==3)){
		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado CORRECTO a UNA_LINEA
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y queda una l&iacute;nea de pedido en el DPD (\e g_linea==1), se realiza la transici&oacute;n al estado UNA_LINEA
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado UNA_LINEA
 */
tBoolean SEM_EVENTO_finESTA_UNO(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==1)){
		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado CORRECTO a DOS_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y quedan dos l&iacute;neas de pedido en el DPD (\e g_linea==2), se realiza la transici&oacute;n al estado DOS_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado DOS_LINEAS
 */
tBoolean SEM_EVENTO_finESTAN_DOS(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==2)){
		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado CORRECTO a TRES_LINEAS
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y quedan tres l&iacute;neas de pedido en el DPD (\e g_linea==3), se realiza la transici&oacute;n al estado TRES_LINEAS
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado TRES_LINEAS
 */
tBoolean SEM_EVENTO_finESTAN_TRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==3)){
		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}

/**
 * @brief  	Transici&oacute;n del estado CORRECTO a DPD_ESPERA
 * @par		L&oacute;gica:
 * 			- Si pasan 5 segundos (\e g_timer_finished=true) y no queda ninguna l&iacute;nea de pedido en el DPD (\e g_linea==0), se realiza la transici&oacute;n al estado DPD_ESPERA
 * @return 	\b ret	Indica que debe realizarse la transici&oacute;n al estado DPD_ESPERA
 */
tBoolean SEM_EVENTO_finREALIZADA(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea==0)){
		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}


//ACCIONES DE LOS ESTADOS

/**
 * @brief  	Acciones que realizar en el estado DPD_ESPERA
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se apagan los tres leds
 * @return 	void
 */
void SEM_ACCION_dpd_espera(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	LEDS_escoger_leds(0);


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - dpd espera",5,87,15);

}

/**
 * @brief  	Acciones que realizar en el estado UNA_LINEA
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display la \b cantidad de la linea de pedido 1
 * 			- Si esta l&iacute;nea de pedido es la &uacute;ltima del pedido, se indica en el display
 * 			- Se enciende el led correspondiente al \b operario de la l&iacute;nea de pedido 1
 * @return 	void
 */
void SEM_ACCION_una_linea(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	DISPLAY_escribir_en_pantalla(lineapedido_1.cantidad,50,30);

	if(lineapedido_1.final==1){

		str = "Ultima Operacion";

		DISPLAY_escribir_en_pantalla(str,15,50);

	}

	LEDS_escoger_leds(lineapedido_1.operario);


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - una linea",5,87,15);

}

/**
 * @brief  	Acciones que realizar en el estado DOS_LINEAS
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display que hay dos operaciones que realizar
 * 			- Se encienden los leds correspondientes a los \b operarios de las dos l&iacute;neas de pedido
 * @return 	void
 */
void SEM_ACCION_dos_lineas(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	str = "Varias Operaciones";

	DISPLAY_escribir_en_pantalla(str,10,30);

	str = "Dos Operarios";

	DISPLAY_escribir_en_pantalla(str,25,50);

	LEDS_escoger_leds_dos_lineas();


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - dos lineas",5,87,15);

}

/**
 * @brief  	Acciones que realizar en el estado TRES_LINEAS
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display que hay tres operaciones que realizar
 * 			- Se encienden los tres leds
 * @return 	void
 */
void SEM_ACCION_tres_lineas(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	str = "Varias Operaciones";

	DISPLAY_escribir_en_pantalla(str,10,30);

	str = "Tres Operarios";

	DISPLAY_escribir_en_pantalla(str,25,50);

	LEDS_escoger_leds_tres_lineas();


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - tres lineas",5,87,15);

}

/**
 * @brief  	Acciones que realizar en el estado MENU_PRIMERO
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display la \b cantidad de la linea de pedido 1
 * 			- Si esta l&iacute;nea de pedido es la &uacute;ltima del pedido, se indica en el display
 * 			- Se enciende el led correspondiente al \b operario de la l&iacute;nea de pedido 1
 * @return 	void
 */
void SEM_ACCION_menu_primero(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	DISPLAY_escribir_en_pantalla(lineapedido_1.cantidad,50,30);

	if(lineapedido_1.final==1){

		str = "Ultima Operacion";

		DISPLAY_escribir_en_pantalla(str,15,50);

	}

	LEDS_escoger_leds(lineapedido_1.operario);


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - menu primero",5,87,15);

}

/**
 * @brief  	Acciones que realizar en el estado MENU_SEGUNDO
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display la \b cantidad de la linea de pedido 2
 * 			- Si esta l&iacute;nea de pedido es la &uacute;ltima del pedido, se indica en el display
 * 			- Se enciende el led correspondiente al \b operario de la l&iacute;nea de pedido 2
 * @return 	void
 */
void SEM_ACCION_menu_segundo(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	DISPLAY_escribir_en_pantalla(lineapedido_2.cantidad,50,30);

	if(lineapedido_2.final==1){

		str = "Ultima Operacion";

		DISPLAY_escribir_en_pantalla(str,15,50);

	}

	LEDS_escoger_leds(lineapedido_2.operario);


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - menu segundo",5,87,15);

}

/**
 * @brief  	Acciones que realizar en el estado MENU_TERCERO
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display la \b cantidad de la linea de pedido 3
 * 			- Si esta l&iacute;nea de pedido es la &uacute;ltima del pedido, se indica en el display
 * 			- Se enciende el led correspondiente al \b operario de la l&iacute;nea de pedido 3
 * @return 	void
 */
void SEM_ACCION_menu_tercero(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	DISPLAY_escribir_en_pantalla(lineapedido_3.cantidad,50,30);

	if(lineapedido_3.final==1){

		str = "Ultima Operacion";

		DISPLAY_escribir_en_pantalla(str,15,50);

	}

	LEDS_escoger_leds(lineapedido_3.operario);


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - menu tercero",5,87,15);

}

/**
 * @brief  	Acciones que realizar en el estado SENSOR
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display que se ha detectado movimiento
 * 			- Se guarda en la variable \e g_estado_confirmado la \e lineapedido_x que se ha detectado
 * @return 	void
 */
void SEM_ACCION_sensor(){

	FRAME_BUFFER_delete_row(50);

	str = "Detectado";

	DISPLAY_escribir_en_pantalla(str,35,50);

	if((dpd.estadoActual == UNA_LINEA)|| (dpd.estadoActual == MENU_PRIMERO)){
		g_estado_confirmado = 1;
	}
	else if(dpd.estadoActual == MENU_SEGUNDO){
		g_estado_confirmado = 2;
	}
	else
		g_estado_confirmado = 3;

	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - sensor",5,87,15);
}

/**
 * @brief  	Acciones que realizar en el estado INCORRECTO
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display que la operaci&oacute;n ha sido incorrecta
 * 			- Se indica en display el tipo de fallo cometido
 * 			- Se emite un pitido de aviso
 * @return 	void
 */
void SEM_ACCION_incorrecto(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	str = "Operacion Incorrecta";

	DISPLAY_escribir_en_pantalla(str,5,30);

	if(dpd.estadoActual == SENSOR){

		str = "Falta Confirmacion";

		DISPLAY_escribir_en_pantalla(str,10,50);

		lineapedido_1.confirmacion=2;
	}
	else{

		str = "Ubicacion Incorrecta";

		DISPLAY_escribir_en_pantalla(str,5,50);

		lineapedido_1.confirmacion=3;
	}

	DPD_SENSOR_emitir_sonido();


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - incorrecto",5,87,15);

}

/**
 * @brief  	Acciones que realizar en el estado CORRECTO
 * @par		L&oacute;gica:
 * 			- Se eliminan del display las l&iacute;neas que no interesan
 * 			- Se muestra en display que la operaci&oacute;n se ha realizado
 * 			- Si esta l&iacute;nea de pedido ha sido la &uacute;ltima del pedido, se indica en el display y se emite un pitido de aviso
 * 			- Se disminuye en 1 el valor de la variable \e g_linea.
 * 			- Se modifica el orden de las l&iacute;neas de pedido del DPD
 * @return 	void
 * @todo	Una vez se implementa la comunicaci&oacute;n v&iacute;a CAN, se debe enviar la informaci&oacute;n de la &iacute;nea confirmada y eliminarla del DPD
 */
void SEM_ACCION_correcto(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	str = "Operacion Realizada";

	DISPLAY_escribir_en_pantalla(str,5,30);

	switch(g_estado_confirmado){
	case 1: 	DPD_SENSOR_pedido_finalizado(lineapedido_1.final);
				lineapedido_1.confirmacion=1;
				break;
	case 2: 	DPD_SENSOR_pedido_finalizado(lineapedido_2.final);
				lineapedido_2.confirmacion=1;
				break;
	case 3: 	DPD_SENSOR_pedido_finalizado(lineapedido_3.final);
				lineapedido_3.confirmacion=1;
				break;
	default:	break;
	}

	g_linea--;

	RECEIVED_DATA_modificar_posiciones();


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - correcto",5,87,15);

}



//FUNCIONES DEL DPD CON SENSOR

/**
 * @brief  	Muestra en pantalla que el pedido se ha realizado y emite un pitido de aviso
 * @par		L&oacute;gica:
 * 			- Se muestra en display que el pedido se ha realizado, es decir, que ha sido la &uacute;ltima l&iacute;nea de un pedido
 * 			- Se emite un pitido de aviso
 * @return 	void
 */
void DPD_SENSOR_pedido_finalizado(int final){

	if(final==1){

		str = "Pedido Finalizado";

		DISPLAY_escribir_en_pantalla(str,10,50);

		DPD_SENSOR_emitir_sonido();

	}

}

/**
 * @brief  	Emite un pitido
 * @par		L&oacute;gica:
 * 			- Se emite un pitido por el altavoz
 * @return 	void
 */
void DPD_SENSOR_emitir_sonido(){

	SONIDO_reproducir_nota(FRECUENCIA_DO);

}

/*********************************************************************
** 																	**
** EOF																**
** 																	**
*********************************************************************/
#endif
