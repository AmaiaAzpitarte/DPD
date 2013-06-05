/*********************************************************************
** 																	**
** project : DPD				 									**
** filename : DPD.c													**
** version : 1 														**
** date : June 3, 2013		 										**
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
**Date : June 3, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/

#define _DPD_C

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
#include "DPD/DPD.h"
#include "Headers/keypad.h"

#include "Utiles/rit128x96x4.h"
#include "lm3slib/driverlib/gpio.h"

#include "Headers/received_data.h"
#include "Headers/data_structs.h"

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



/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

extern t_lineapedido lineapedido_1;

extern t_lineapedido lineapedido_2;

extern t_lineapedido lineapedido_3;

extern int linea;

/*
 * Definición de los estados de la máquina de estados con sus respectivos eventos
 * a otros estados y sus acciones
 */

ESTADO(dpd_espera)
	ITEM_EVAC(UNA_LINEA, SEM_EVENTO_finDPD_ESPERA, SEM_ACCION_una_linea)
FIN_ESTADO(dpd_espera, DPD_ESPERA, NULL)

ESTADO(una_linea)
	ITEM_EVAC(CONFIRMACION, SEM_EVENTO_finPULSADA, SEM_ACCION_confirmacion),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finUNA_LINEA, SEM_ACCION_dos_lineas)
FIN_ESTADO(una_linea, UNA_LINEA, NULL)

ESTADO(confirmacion)
	ITEM_EVAC(DPD_ESPERA, SEM_EVENTO_finCONFIRMACION, SEM_ACCION_dpd_espera),
	ITEM_EVAC(UNA_LINEA, SEM_EVENTO_finQUEDA_UNA, SEM_ACCION_una_linea),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finQUEDAN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finQUEDAN_TRES, SEM_ACCION_tres_lineas)
FIN_ESTADO(confirmacion, CONFIRMACION, NULL)

ESTADO(dos_lineas)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU, SEM_ACCION_menu_primero),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finTERCERA, SEM_ACCION_tres_lineas)
FIN_ESTADO(dos_lineas, DOS_LINEAS, NULL)

ESTADO(tres_lineas)
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finTRES_LINEAS, SEM_ACCION_menu_primero)
FIN_ESTADO(tres_lineas, TRES_LINEAS, NULL)

ESTADO(menu_primero)
	ITEM_EVAC(CONFIRMACION, SEM_EVENTO_finCONF_UNO, SEM_ACCION_confirmacion),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finDOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finTRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(MENU_SEGUNDO, SEM_EVENTO_finMENU_DOS, SEM_ACCION_menu_segundo)
FIN_ESTADO(menu_primero, MENU_PRIMERO, NULL)

ESTADO(menu_segundo)
	ITEM_EVAC(CONFIRMACION, SEM_EVENTO_finCONF_DOS, SEM_ACCION_confirmacion),
	ITEM_EVAC(DOS_LINEAS, SEM_EVENTO_finEXISTEN_DOS, SEM_ACCION_dos_lineas),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finEXISTEN_TRES, SEM_ACCION_tres_lineas),
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finHAY_DOS, SEM_ACCION_menu_primero),
	ITEM_EVAC(MENU_TERCERO, SEM_EVENTO_finHAY_TRES, SEM_ACCION_menu_tercero)
FIN_ESTADO(menu_segundo, MENU_SEGUNDO, NULL)

ESTADO(menu_tercero)
	ITEM_EVAC(CONFIRMACION, SEM_EVENTO_finCONF_TRES, SEM_ACCION_confirmacion),
	ITEM_EVAC(MENU_PRIMERO, SEM_EVENTO_finMENU_UNO, SEM_ACCION_menu_primero),
	ITEM_EVAC(TRES_LINEAS, SEM_EVENTO_finSIGUEN_TRES, SEM_ACCION_tres_lineas)
FIN_ESTADO(menu_tercero, MENU_TERCERO, NULL)


AUTOMATA(dpd)
	&dpd_espera,
	&una_linea,
	&confirmacion,
	&dos_lineas,
	&tres_lineas,
	&menu_primero,
	&menu_segundo,
	&menu_tercero
FIN_AUTOMATA(dpd,1,NULL)


/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/

extern char pulsada; /* Variable en la que se guarda la tecla pulsada */

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

	if (pulsada==SELECT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finPULSADA(){

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finUNA_LINEA(){

	tBoolean ret;

	if (pulsada==UP) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finCONFIRMACION(){

	tBoolean ret;

	if (pulsada==UP) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finQUEDA_UNA(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finQUEDAN_DOS(){

	tBoolean ret;

	if (pulsada==LEFT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finQUEDAN_TRES(){

	unsigned long ulValue;

	int i;

	for(i=0;i<2500;i++){
		i++;
		i--;
	}

	// Configure and enable the SysTick counter.
	SysTickPeriodSet(1000);
	SysTickEnable();

	// Delay for some time...

	// Read the current SysTick value.
	ulValue = SysTickValueGet();

	tBoolean ret;

	if(ulValue==1000) ret = true;

}

tBoolean SEM_EVENTO_finMENU(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finTERCERA(){

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finTRES_LINEAS(){

	tBoolean ret;

	if (pulsada==UP) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finCONF_UNO(){

	tBoolean ret;

	if (pulsada==RIGHT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finDOS(){

	unsigned long ulValue;

	int i;

	for(i=0;i<2500;i++){
		i++;
		i--;
	}

	// Configure and enable the SysTick counter.
	SysTickPeriodSet(1000);
	SysTickEnable();

	// Delay for some time...

	// Read the current SysTick value.
	ulValue = SysTickValueGet();

	tBoolean ret;

	if(ulValue==1000) ret = true;

}

tBoolean SEM_EVENTO_finTRES(){

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finMENU_DOS(){

	tBoolean ret;

	if (pulsada==LEFT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finCONF_DOS(){

	tBoolean ret;

	if (pulsada==RIGHT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finEXISTEN_DOS(){

	tBoolean ret;

	if (pulsada==UP) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finEXISTEN_TRES(){

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finHAY_DOS(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finHAY_TRES(){



	tBoolean ret;

		if (pulsada==LEFT) ret=true;
		else ret=false;

}

tBoolean SEM_EVENTO_finCONF_TRES(){

	tBoolean ret;

	if (pulsada==RIGHT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finMENU_UNO(){

	tBoolean ret;

	if (pulsada==SELECT) ret=true;
	else ret=false;

}

tBoolean SEM_EVENTO_finSIGUEN_TRES(){

	tBoolean ret;

	if (pulsada==DOWN) ret=true;
	else ret=false;

}





//ACCIONES DE LOS ESTADOS


void SEM_ACCION_dpd_espera(){

	RIT128x96x4Clear();

	//Para saber en qué estado estamos en cada momento
	RIT128x96x4StringDraw("ESTADO - dpd espera",5,80,15);

}


void SEM_ACCION_una_linea(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string(lineapedido_1.cantidad,50,20,15);

	if(lineapedido_1.final==1){
		DISPLAY_GENERICO_dibuja_string("Ultima operacion",15,40,15);
	}

	//Para saber en qué estado estamos en cada momento
	//FRAME_BUFFER_delete_row(80);

	RIT128x96x4StringDraw("ESTADO - una linea",5,80,15);

}

void SEM_ACCION_confirmacion(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string("Operacion realizada",5,30,15);

	//Para saber en qué estado estamos en cada momento
	//FRAME_BUFFER_delete_row(80);

	RIT128x96x4StringDraw("ESTADO - confirmacion",5,80,15);

}

void SEM_ACCION_dos_lineas(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string("Varias Operaciones",10,30,15);
	DISPLAY_GENERICO_dibuja_string("Dos Operarios",25,45,15);

	//Para saber en qué estado estamos en cada momento
	//FRAME_BUFFER_delete_row(80);

	RIT128x96x4StringDraw("ESTADO - dos lineas",5,80,15);

}

void SEM_ACCION_tres_lineas(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string("Varias Operaciones",10,30,15);
	DISPLAY_GENERICO_dibuja_string("Tres Operarios",25,45,15);

	//Para saber en qué estado estamos en cada momento
	//FRAME_BUFFER_delete_row(80);

	RIT128x96x4StringDraw("ESTADO - tres lineas",5,80,15);

}

void SEM_ACCION_menu_primero(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string(lineapedido_1.cantidad,50,20,15);

	if(lineapedido_1.final==1){
		DISPLAY_GENERICO_dibuja_string("Ultima operacion",15,40,15);
	}


	//Para saber en qué estado estamos en cada momento
	//FRAME_BUFFER_delete_row(80);

	RIT128x96x4StringDraw("ESTADO - menu primero",5,80,15);

}

void SEM_ACCION_menu_segundo(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string(lineapedido_2.cantidad,50,20,15);

	if(lineapedido_2.final==1){
		DISPLAY_GENERICO_dibuja_string("Ultima operacion",15,40,15);
	}


	//Para saber en qué estado estamos en cada momento
	//FRAME_BUFFER_delete_row(80);

	RIT128x96x4StringDraw("ESTADO - menu segundo",5,80,15);

}

void SEM_ACCION_menu_tercero(){

	RIT128x96x4Clear();

	DISPLAY_GENERICO_dibuja_string(lineapedido_3.cantidad,50,20,15);

	if(lineapedido_3.final==1){
		DISPLAY_GENERICO_dibuja_string("Ultima operacion",15,40,15);
	}

	//Para saber en qué estado estamos en cada momento
	//FRAME_BUFFER_delete_row(80);

	RIT128x96x4StringDraw("ESTADO - menu tercero",5,80,15);

}
