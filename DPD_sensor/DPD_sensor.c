/*****************************************************************************************************************
** @file    DPD.c																								**
** @brief   Fichero donde se definen los estados y las transiciones de la m&aacute;quina de estados con sensor	**
** @par		L&oacute;gica																						**
**			- Se definen los estados de la m&aacute;quina de estados con sensor									**
**			- Se definen las transiciones de la m&aacute;quina de estados con sensor							**
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

#define _DPD_SENSOR_C
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

extern char g_pulsada; /* Variable en la que se guarda la tecla pulsada */

extern t_lineapedido lineapedido_1;

extern t_lineapedido lineapedido_2;

extern t_lineapedido lineapedido_3;

extern int g_linea;

extern tBoolean g_timer_finished;

extern int g_movimiento;

/*
 * Definici�n de los estados de la m�quina de estados con sus respectivos eventos
 * a otros estados y sus acciones
 */

ESTADO(dpd_espera)
	ITEM_EVAC(UNA_LINEA, SEM_EVENTO_finDPD_ESPERA, SEM_ACCION_una_linea)
FIN_ESTADO(dpd_espera, DPD_ESPERA, NULL)

ESTADO(una_linea)
	ITEM_EVAC(SENSOR, SEM_EVENTO_finSENSOR, SEM_ACCION_sensor),
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
*********************************************************************/

unsigned long g_system_clock;

char *str;

int g_estado_confirmado;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

//TRANSICIONES DESDE LOS ESTADOS

tBoolean SEM_EVENTO_finDPD_ESPERA(){

	tBoolean ret;

	if(g_linea>=1) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finSENSOR(){ //Este evento debe ser la detecci�n del sensor

	tBoolean ret;

	if (g_movimiento==1) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_INC(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finUNA_LINEA(){

	tBoolean ret;

	if (g_linea>=2) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU(){

	tBoolean ret;

	if (g_pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finDOS_LINEAS(){

	tBoolean ret;

	if (g_linea==3) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_DOS(){

	tBoolean ret;

	if (g_pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

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

tBoolean SEM_EVENTO_finMENU_TRES(){

	tBoolean ret;

	if (g_pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finSENSOR_PRIMERO(){ //Este evento debe ser la detecci�n del sensor

	tBoolean ret;

	if (g_movimiento==1) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_PRIMERO(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_CUATRO(){

	tBoolean ret;

	if ((g_pulsada==UP)&&(g_linea==2)) ret=true;
	else ret=false;

	return ret;

}

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

tBoolean SEM_EVENTO_finMENU_CINCO(){

	tBoolean ret;

	if ((g_pulsada==UP)&&(g_linea==3)) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finSENSOR_SEGUNDO(){ //Este evento debe ser la detecci�n del sensor

	tBoolean ret;

	if (g_movimiento==1) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_SEGUNDO(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finMENU_SEIS(){

	tBoolean ret;

	if (g_pulsada==UP) ret=true;
	else ret=false;

	return ret;

}

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

tBoolean SEM_EVENTO_finSENSOR_TERCERO(){ //Este evento debe ser la detecci�n del sensor

	tBoolean ret;

	if (g_movimiento==1) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_TERCERO(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

tBoolean SEM_EVENTO_finPULSADA_COR(){

	tBoolean ret;

	if (g_pulsada==SELECT) ret=true;
	else ret=false;

	return ret;

}

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


void SEM_ACCION_dpd_espera(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	LEDS_escoger_leds(0);


	//Para saber en qu� estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - dpd espera",5,87,15);

}


void SEM_ACCION_una_linea(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	DISPLAY_escribir_en_pantalla(lineapedido_1.cantidad,50,30);

	if(lineapedido_1.final==1){

		str = "Ultima Operacion";

		DISPLAY_escribir_en_pantalla(str,15,50);

	}

	LEDS_escoger_leds(lineapedido_1.operario);


	//Para saber en qu� estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - una linea",5,87,15);

}


void SEM_ACCION_dos_lineas(){

	FRAME_BUFFER_delete_row(30);

	FRAME_BUFFER_delete_row(50);

	str = "Varias Operaciones";

	DISPLAY_escribir_en_pantalla(str,10,30);

	str = "Dos Operarios";

	DISPLAY_escribir_en_pantalla(str,25,50);

	LEDS_escoger_leds_dos_lineas();


	//Para saber en qu� estado estamos en cada momento
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


	//Para saber en qu� estado estamos en cada momento
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


	//Para saber en qu� estado estamos en cada momento
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


	//Para saber en qu� estado estamos en cada momento
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


	//Para saber en qu� estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - menu tercero",5,87,15);

}


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

	//Para saber en qu� estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - sensor",5,87,15);
}

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


	//Para saber en qu� estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - incorrecto",5,87,15);

}

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


	//Para saber en qu� estado estamos en cada momento
	FRAME_BUFFER_delete_row(87);
	RIT128x96x4StringDraw("ESTADO - correcto",5,87,15);

}


void DPD_SENSOR_pedido_finalizado(int final){

	if(final==1){

		str = "Pedido Finalizado";

		DISPLAY_escribir_en_pantalla(str,10,50);

		DPD_SENSOR_emitir_sonido();

	}

}

void DPD_SENSOR_emitir_sonido(){

	SONIDO_reproducir_nota(FRECUENCIA_DO);

}

/*********************************************************************
** 																	**
** EOF																**
** 																	**
*********************************************************************/
#endif
