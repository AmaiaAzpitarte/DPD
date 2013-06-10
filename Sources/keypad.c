/*********************************************************************
** 																	**
** project : DPD				 									**
** filename : keypad.c		 										**
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

#define KEYPAD_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "hw_types.h"
#include "hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "Headers/keypad.h"

#include "DPD_Config.h"

#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif

/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
**********************************************************************/

unsigned long g_ul_keypad_switches = 0x1f; /*Valor leído en los botones*/

char pulsada; /* Variable donde se guarda la tecla pulsada */

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

/**
 * @brief  Inicializamos el teclado (los botones).
 *
 * @return      -
 *
*/

void DPD_inicializacion_keypad(){

	//Activamos pines del puerto F (botón select)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIOPinTypeGPIOInput( GPIO_PORTF_BASE, GPIO_PIN_1); /*pin 1*/

	GPIOPadConfigSet( GPIO_PORTF_BASE, GPIO_PIN_1 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

	//Activamos pines del puerto E (botones up, down, right, left)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_0); /*pin 0*/

	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_0 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_1); /*pin 1*/

	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_1 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_2); /*pin 2*/

	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_2 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_3); /*pin 3*/

	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_3 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

}

/**
 * @brief  Leemos el botón pulsado en el teclado.
 *
 * @return     void
 *
*/

void DPD_leer_keypad(){

	//esta función hay que modificarla para poner algo más elegante
	int i=0;
	for(i=0;i<500;i++){
		i++;
		i--;
	}

		unsigned long ul_pressed_data;

		ul_pressed_data = (GPIOPinRead( GPIO_PORTE_BASE , (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3) )|
					    	(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1) << 3));

		g_ul_keypad_switches = ul_pressed_data;

		g_ul_keypad_switches = g_ul_keypad_switches & 0x1f;

}

/**
 * @brief  Le damos valor a la tecla.
 *
 * @return      -
 *
 * Se le asigna un valor a la variable pulsada según el botón que
 * se haya seleccionado.
*/

void DPD_elegir_tecla(){

	switch(g_ul_keypad_switches){

		case KEY_UP:	pulsada = UP;
						break;

		case KEY_DOWN: 	pulsada = DOWN;
						break;

		case KEY_LEFT: 	pulsada = LEFT;
						break;

		case KEY_RIGHT: pulsada = RIGHT;
						break;

		case KEY_SELECT: 	pulsada = SELECT;
							break;

		default: 	pulsada = NADA;
					break;

	}

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/

