/*****************************************************************************************************************
** @file    DPD.c																								**
** @brief   Fichero donde se definen los estados y las transiciones de la m&aacute;quina de estados sin sensor	**
** @par		L&oacute;gica																						**
**			- Se definen los estados de la m&aacute;quina de estados sin sensor									**
**			- Se definen las transiciones de la m&aacute;quina de estados sin sensor							**
** @author  Amaia Azpitarte																						**
** @date    2013-06-03																							**
*****************************************************************************************************************/

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
#include "DPD/DPD.h"
#include "Headers/keypad.h"

#include "Utiles/rit128x96x4.h"
#include "lm3slib/driverlib/gpio.h"

#include "Headers/received_data.h"
#include "Headers/data_structs.h"

#include "Headers/sonido.h"

#include "Headers/leds.h"

#include "Headers/conf_timer.h"

#include "DPD_Config.h"
#ifndef DPD_SENSOR

#define _DPD_C

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

extern char g_pulsada; /* Variable en la que se guarda la tecla pulsada */

extern t_lineapedido lineapedido_1;

extern t_lineapedido lineapedido_2;

extern t_lineapedido lineapedido_3;

extern int g_linea;

extern tBoolean g_timer_finished;

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
*********************************************************************/

unsigned long g_system_clock;

char *str;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

//TRANSICIONES DESDE LOS ESTADOS

tBoolean SEM_EVENTO_finDPD_ESPERA(){

	tBoolean ret;

	if(g_linea >= 1) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA(){

	tBoolean ret;

	if (g_pulsada == SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finUNA_LINEA(){

	tBoolean ret;

	if (g_linea >= 2) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finCONFIRMACION(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea == 0)){

		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;

	}
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finQUEDA_UNA(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea == 1)) {
		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}

	return ret;

}

tBoolean SEM_EVENTO_finQUEDAN_DOS(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea == 2)) {

		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finQUEDAN_TRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea == 3)){

		g_timer_finished = false;
		SONIDO_reproducir_nota(FRECUENCIA_SILENCIO);
		ret = true;
	}
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU(){

	tBoolean ret;

	if (g_pulsada == UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finTERCERA(){

	tBoolean ret;

	if (g_linea == 3) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finTRES_LINEAS(){

	tBoolean ret;

	if (g_pulsada == UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finCONF_UNO(){

	tBoolean ret;

	if (g_pulsada == SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finDOS(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea == 2)){

		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finTRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea == 3)){

		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_DOS(){

	tBoolean ret;

	if (g_pulsada == UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finCONF_DOS(){

	tBoolean ret;

	if (g_pulsada == SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finEXISTEN_DOS(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea == 2)){

		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finEXISTEN_TRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if ((g_timer_finished)&&(g_linea == 3)){

		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}

tBoolean SEM_EVENTO_finHAY_DOS(){

	tBoolean ret;

	if ((g_pulsada == UP)&&(g_linea == 2)) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finHAY_TRES(){

	tBoolean ret;

	if ((g_pulsada == UP)&&(g_linea == 3)) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finCONF_TRES(){

	tBoolean ret;

	if (g_pulsada == SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_UNO(){

	tBoolean ret;

	if (g_pulsada == UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finSIGUEN_TRES(){

	TIMER_enable_timer0();

	tBoolean ret;

	if (g_timer_finished){

		g_timer_finished = false;
		ret = true;
	}
	else ret = false;

	return ret;

}




//ACCIONES DE LOS ESTADOS


void SEM_ACCION_dpd_espera(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	LEDS_escoger_leds(0);


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - dpd espera",5,87,15);

}


void SEM_ACCION_una_linea(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	DISPLAY_escribir_en_pantalla(lineapedido_1.cantidad,50,30);

	if(lineapedido_1.final == 1){

		str = "Ultima Operacion";

		DISPLAY_escribir_en_pantalla(str,15,50);
	}

	LEDS_escoger_leds(lineapedido_1.operario);


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - una linea",5,87,15);

}


// @todo	Cuando se integre con la comunicación CAN, se debería llamar a una función de envío que envíe la línea
//			de pedido realizado y que lo borre del DPD, shift-ando otras líneas que puedan quedar, de manera que
//			las líneas recibidas estén siempre en orden 1, 2, 3.
void SEM_ACCION_confirmacion(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	str = "Operacion Realizada";

	DISPLAY_escribir_en_pantalla(str,5,30);

	switch(dpd.estadoActual){
	case UNA_LINEA: 	DPD_pedido_finalizado(lineapedido_1.final);
						lineapedido_1.confirmacion=1;
						break;
	case MENU_PRIMERO:	DPD_pedido_finalizado(lineapedido_1.final);
						lineapedido_1.confirmacion=1;
						break;
	case MENU_SEGUNDO: 	DPD_pedido_finalizado(lineapedido_2.final);
						lineapedido_2.confirmacion=1;
						break;
	case MENU_TERCERO: 	DPD_pedido_finalizado(lineapedido_3.final);
						lineapedido_3.confirmacion=1;
						break;
	default:			break;
	}

	g_linea--;

	RECEIVED_DATA_modificar_posiciones();


	//Para saber en qué estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - confirmacion",5,87,15);

}

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

void DPD_pedido_finalizado(int final){

	if(final==1){

		str = "Pedido Finalizado";

		DISPLAY_escribir_en_pantalla(str,10,50);

		DPD_emitir_sonido();

	}

}

void DPD_emitir_sonido(){

	SONIDO_reproducir_nota(FRECUENCIA_DO);

}

/*********************************************************************
**																	**
** EOF			 													**
** 																	**
*********************************************************************/
#endif
