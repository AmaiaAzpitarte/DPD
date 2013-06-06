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
//#include "driverlib/debug.h"
#include "driverlib/sysctl.h"

#include "Headers/received_data.h"
#include "Headers/data_structs.h"

#include "Automata/Automata.h"

/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

extern int linea;

extern t_lineapedido lineapedido_1;

extern t_lineapedido lineapedido_2;

extern t_lineapedido lineapedido_3;

extern TS_AUTOMATA dpd;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

void DPD_inicializacion_leds(){

	//
	// Enable the GPIO port A that is used for the LEDS.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	//
	// Enable the GPIO pins 2, 3 and 3 for the LEDS.  Set the direction as output, and
	// enable the GPIO pins for digital function.
	//
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);

	//apagar los leds desde el principio
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, 0x00000000);
}

void DPD_controlar_leds(leds){

	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, 0x00000000);

	//
	// Output leds' values
	//
	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4, leds);

}

void DPD_escoger_leds(){

	int valor_leds = 0x00;

	int led1;
	int dos_leds;

	switch(linea){
	case 0: valor_leds = 0x00;
			break;
	case 1: valor_leds = DPD_consultar_operarios(lineapedido_1.operario);
			break;
	case 2: led1= DPD_consultar_operarios(lineapedido_1.operario);
			valor_leds= DPD_consultar_operarios(lineapedido_2.operario);
			dos_leds = led1 || valor_leds; //esto no funciona correctamente
			break;
	case 3: valor_leds = 0x1C;
			break;
	default: 	valor_leds = 0x00;
				break;
	}

	if((linea==2)&&(dpd.estadoActual==DOS_LINEAS)){
		DPD_controlar_leds(dos_leds);
	}
	else{
		DPD_controlar_leds(valor_leds);
	}


}

int DPD_consultar_operarios(operario){

	int ret = 0x00;

	switch(operario){
	case 1: ret = 0x04;
			break;
	case 2: ret = 0x08;
			break;
	case 3: ret = 0x10;
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

