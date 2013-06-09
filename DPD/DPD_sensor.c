/*********************************************************************
** 																	**
** project : DPD				 									**
** filename : DPD_sensor.c											**
** version : 1 														**
** date : June 9, 2013		 										**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2013, 					 							**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : June 9, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/

#define _DPD_SENSOR_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include <string.h>

#include "Automata/Automata.h"
#include "DPD/DPD_sensor.h"
#include "Headers/keypad.h"

#include "Utiles/rit128x96x4.h"

#include "lm3slib/driverlib/gpio.h"

#include "Headers/received_data.h"
#include "Headers/data_structs.h"

#include "Headers/conf_systick.h"

#include "Headers/sonido.h"

#include "Headers/leds.h"

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
**********************************************************************/
/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
**********************************************************************/
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

extern char pulsada; /* Variable en la que se guarda la tecla pulsada */

extern t_lineapedido lineapedido_1;

extern t_lineapedido lineapedido_2;

extern t_lineapedido lineapedido_3;

extern int linea;

extern int valor_leds;

extern unsigned char g_ucCounter;



/*
 * Definición de los estados de la máquina de estados con sus respectivos eventos
 * a otros estados y sus acciones
 */

ESTADO(dpd_espera)
	ITEM_EVAC(UNA_LINEA, SEM_EVENTO_finDPD_ESPERA, SEM_ACCION_una_linea)
FIN_ESTADO(dpd_espera, DPD_ESPERA, NULL)

ESTADO(una_linea)
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR, SEM_ACCION_dos_lineas),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finPULSADA_INC, SEM_ACCION_incorrecto),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finUNA_LINEA, SEM_ACCION_dos_lineas)
FIN_ESTADO(una_linea, UNA_LINEA, NULL)

ESTADO(dos_lineas)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU, SEM_ACCION_menu_primero),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finDOS_LINEAS, SEM_ACCION_tres_lineas)
FIN_ESTADO(dos_lineas, DOS_LINEAS, NULL)

ESTADO(tres_lineas)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU_DOS, SEM_ACCION_menu_primero)
FIN_ESTADO(tres_lineas, TRES_LINEAS, NULL)

ESTADO(menu_primero)
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finQUEDAN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finQUEDAN_TRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(MENU_SEGUNDO, SEM_EVENTO_finMENU_TRES, SEM_ACCION_menu_segundo),
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR_PRIMERO, SEM_ACCION_sensor),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finPULSADA_PRIMERO, SEM_ACCION_incorrecto)
FIN_ESTADO(menu_primero, MENU_PRIMERO, NULL)

ESTADO(menu_segundo)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU_CUATRO, SEM_ACCION_menu_primero),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finEXISTEN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finEXISTEN_TRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(MENU_TERCERO, SEM_EVENTO_finMENU_CINCO, SEM_ACCION_menu_tercero),
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR_SEGUNDO, SEM_ACCION_sensor),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finPULSADA_SEGUNDO, SEM_ACCION_incorrecto)
FIN_ESTADO(menu_segundo, MENU_SEGUNDO, NULL)

ESTADO(menu_tercero)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU_SEIS, SEM_ACCION_menu_primero),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finHAY_TRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR_TERCERO, SEM_ACCION_sensor),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finPULSADA_TERCERO, SEM_ACCION_incorrecto)
FIN_ESTADO(menu_tercero, MENU_TERCERO, NULL)

ESTADO(sensor)
	ITEM_EVAC(CORRECTO, SEM_EVENTO_finPULSADA_COR, SEM_ACCION_correcto),
	ITEM_EVAC(INCORRECTO, SEM_EVENTO_finINCORRECTO, SEM_ACCION_incorrecto)
FIN_ESTADO(sensor, SENSOR, NULL)

ESTADO(incorrecto)
	ITEM_EVAC(UNA_LINEA, SEM_EVENTO_finSIGUE_UNO, SEM_ACCION_una_linea),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finSIGUEN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finSIGUEN_TRES, SEM_ACCION_tres_lineas)
FIN_ESTADO(incorrecto, INCORRECTO, NULL)

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
**********************************************************************/

//int estado=0;

unsigned long g_ul_system_clock;

/*********************************************************************
** 																	**
** EXPORTED FUNCTIONS 												**
** 																	**
**********************************************************************/
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/


//TRANSICIONES DESDE LOS ESTADOS

tBoolean SEM_EVENTO_finDPD_ESPERA(){

	tBoolean ret;

	if(linea>=1) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finSENSOR(){ //Este evento debe ser la detección del sensor

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_INC(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finUNA_LINEA(){

	tBoolean ret;

	if (linea>=2) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU(){

	tBoolean ret;

	if (pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finDOS_LINEAS(){

	tBoolean ret;

	if (linea==3) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_DOS(){

	tBoolean ret;

	if (pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finQUEDAN_DOS(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==2)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finQUEDAN_TRES(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==3)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_TRES(){

	tBoolean ret;

	if (pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finSENSOR_PRIMERO(){ //Este evento debe ser la detección del sensor

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_PRIMERO(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_CUATRO(){

	tBoolean ret;

	if ((pulsada==UP)&(linea==2)) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finEXISTEN_DOS(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==2)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finEXISTEN_TRES(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==3)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_CINCO(){

	tBoolean ret;

	if ((pulsada==UP)&(linea==3)) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finSENSOR_SEGUNDO(){ //Este evento debe ser la detección del sensor

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_SEGUNDO(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_SEIS(){

	tBoolean ret;

	if (pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finHAY_TRES(){

	tBoolean ret;

	if (g_ucCounter == 5) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finSENSOR_TERCERO(){ //Este evento debe ser la detección del sensor

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_TERCERO(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_COR(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finINCORRECTO(){

	tBoolean ret;

	if (g_ucCounter == 5) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finSIGUE_UNO(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==1)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finSIGUEN_DOS(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==2)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finSIGUEN_TRES(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==3)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finESTA_UNO(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==1)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finESTAN_DOS(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==2)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finESTAN_TRES(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==3)) ret = true;
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finREALIZADA(){

	tBoolean ret;

	if ((g_ucCounter == 5)&(linea==0)) ret = true;
	else ret = false;

	return ret;

}





//ACCIONES DE LOS ESTADOS


void SEM_ACCION_dpd_espera(){

	RIT128x96x4Clear();

	DPD_escoger_leds(0);

	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - dpd espera",5,80,15);

}


void SEM_ACCION_una_linea(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string(lineapedido_1.cantidad,50,20,15);

	if(lineapedido_1.final==1){
		DISPLAY_GENERICO_dibuja_string("Ultima Operacion",15,40,15);
	}

	DPD_escoger_leds(lineapedido_1.operario);


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - una linea",5,80,15);

}


void SEM_ACCION_dos_lineas(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string("Varias Operaciones",10,30,15);
	DISPLAY_GENERICO_dibuja_string("Dos Operarios",25,45,15);

	DPD_escoger_leds_dos_lineas();


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - dos lineas",5,80,15);

}

void SEM_ACCION_tres_lineas(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string("Varias Operaciones",10,30,15);
	DISPLAY_GENERICO_dibuja_string("Tres Operarios",25,45,15);

	DPD_escoger_leds_tres_lineas();


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - tres lineas",5,80,15);

}

void SEM_ACCION_menu_primero(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string(lineapedido_1.cantidad,50,20,15);

	if(lineapedido_1.final==1){
		DISPLAY_GENERICO_dibuja_string("Ultima Operacion",15,40,15);
	}

	DPD_escoger_leds(lineapedido_1.operario);


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - menu primero",5,80,15);

}

void SEM_ACCION_menu_segundo(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string(lineapedido_2.cantidad,50,20,15);

	if(lineapedido_2.final==1){
		DISPLAY_GENERICO_dibuja_string("Ultima Operacion",15,40,15);
	}

	DPD_escoger_leds(lineapedido_2.operario);


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - menu segundo",5,80,15);

}

void SEM_ACCION_menu_tercero(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string(lineapedido_3.cantidad,50,20,15);

	if(lineapedido_3.final==1){
		DISPLAY_GENERICO_dibuja_string("Ultima Operacion",15,40,15);
	}

	DPD_escoger_leds(lineapedido_3.operario);


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - menu tercero",5,80,15);

}


void SEM_ACCION_sensor(){

	RIT128x96x4Clear();

	switch(dpd.estadoActual){
		case UNA_LINEA: 	DISPLAY_GENERICO_dibuja_string(lineapedido_1.cantidad,50,20,15);
							break;
		case MENU_PRIMERO:	DISPLAY_GENERICO_dibuja_string(lineapedido_1.cantidad,50,20,15);
							break;
		case MENU_SEGUNDO: 	DISPLAY_GENERICO_dibuja_string(lineapedido_2.cantidad,50,20,15);
							break;
		case MENU_TERCERO: 	DISPLAY_GENERICO_dibuja_string(lineapedido_3.cantidad,50,20,15);
							break;
		default:			break;
		}

	DISPLAY_GENERICO_dibuja_string("Detectado",20,30,15);


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - sensor",5,80,15);

}

void SEM_ACCION_incorrecto(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string("Operacion Incorrecta",20,30,15);
	DISPLAY_GENERICO_dibuja_string("Productos cogidos de otra ubicacion",20,40,15);

	while(1){
		DPD_reproducir_nota(FRECUENCIA_DO);
		if(g_ucCounter==4){
			DPD_reproducir_nota(40000);
			break;
		}
	}


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - incorrecto",5,80,15);

}

void SEM_ACCION_correcto(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string("Operacion Realizada",5,30,15);

	switch(valor_leds){
	case 0x01: 	pedido_finalizado(lineapedido_1.final);
						lineapedido_1.confirmacion=1;
						break;
	case 0x01:	pedido_finalizado(lineapedido_1.final);
						lineapedido_1.confirmacion=1;
						break;
	case 0x02: 	pedido_finalizado(lineapedido_2.final);
						lineapedido_2.confirmacion=1;
						break;
	case 0x03: 	pedido_finalizado(lineapedido_3.final);
						lineapedido_3.confirmacion=1;
						break;
	default:			break;
	}

	linea--;


	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - correcto",5,80,15);

}


void pedido_finalizado(final){

	if(final==1){

		DISPLAY_GENERICO_dibuja_string("Pedido Finalizado",10,60,15);

		while(1){
			DPD_reproducir_nota(FRECUENCIA_DO);
			if(g_ucCounter==4){
				DPD_reproducir_nota(40000);
				break;
			}
		}
	}

}
