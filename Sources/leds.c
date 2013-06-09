/*********************************************************************
** 																	**
** project : DPD			 										**
** filename : leds.c 												**
** version : 1 														**
** date : June 06, 2013 											**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2013,		 										**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : June 06, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/
#define LEDS_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "Headers/leds.h"

#include "DPD/DPD.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "Headers/received_data.h"
#include "Headers/data_structs.h"

/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

extern int linea;

extern t_lineapedido lineapedido_1;

extern t_lineapedido lineapedido_2;

extern t_lineapedido lineapedido_3;

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

int valor_leds;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

void DPD_inicializacion_leds(){

	//
	// Enable the GPIO port B that is used for the LEDS.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	//
	// Enable the GPIO pins 0, 1 and 2 for the LEDS.  Set the direction as output, and
	// enable the GPIO pins for digital function.
	//
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);

	// Apagar los leds desde el principio
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, 0x00000000);
}

void DPD_controlar_leds(leds){

	//
	// Output leds' values
	//
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, leds);

}


void DPD_escoger_leds(operario){

	valor_leds = 0x00;

	int led1;
	int led2;

	if(linea==0) valor_leds = 0x00; // DPD_ESPERA
	else valor_leds = DPD_consultar_operarios(operario); // UNA_LINEA | MENU_PRIMERO | MENU_SEGUNDO | MENU_TERCERO

	DPD_controlar_leds(valor_leds);

}

void DPD_escoger_leds_dos_lineas(){ // DOS_LINEAS

	valor_leds = 0x00;
	int led1=0x00;
	int led2=0x00;

	led1= DPD_consultar_operarios(lineapedido_1.operario);
	led2= DPD_consultar_operarios(lineapedido_2.operario);
	valor_leds = led1 | led2;

	DPD_controlar_leds(valor_leds);

}

void DPD_escoger_leds_tres_lineas(){ // TRES_LINEAS

	DPD_controlar_leds(0x07);

}

int DPD_consultar_operarios(operario){

	int ret = 0x00;

	switch(operario){
	case 1: ret = 0x01;
			break;
	case 2: ret = 0x02;
			break;
	case 3: ret = 0x04;
			break;
	default: break;
	}

	return ret;

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

