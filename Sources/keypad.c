/*********************************************************************************
** @file    keypad.c															**
** @brief   Fichero donde se controla el keypad, detectando las teclas pulsadas	**
** @par		L&oacute;gica														**
**			- Se inicializa el keypad											**
**			- Se lee el valor del keypad										**
**			- Se detecta qu&eacute; tecla se ha pulsado							**
** @author  Amaia Azpitarte														**
** @date    2013-06-03															**
*********************************************************************************/

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "hw_types.h"
#include "hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "Headers/keypad.h"

#include "DPD_Config.h"

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
*********************************************************************/
#define KEYPAD_C

#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif

/*********************************************************************
** 																	**
** TYPEDEFS AND STRUCTURES 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

unsigned long g_keypad = 0x1f; /*Valor leído en los botones*/

char g_pulsada; /* Variable donde se guarda la tecla pulsada */

unsigned long g_dato_cambiado;

unsigned long g_dato_anterior; //solo para este fichero

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief  Inicializamos el teclado (los botones).
 *
 * @return      -
 *
*/
void KEYPAD_init(){

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
void KEYPAD_leer_keypad(){

		unsigned long dato_pulsado; //Guarda el valor de la tecla pulsada

		dato_pulsado = (GPIOPinRead( GPIO_PORTE_BASE , (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3) )|
					    	(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1) << 3));

		g_dato_cambiado = g_keypad ^ dato_pulsado; //para evitar los rebotes

		g_keypad = dato_pulsado;

		g_keypad = g_keypad & 0x1f;

}

/**
 * @brief  Le damos valor a la tecla.
 *
 * @return      -
 *
 * Se le asigna un valor a la variable pulsada según el botón que
 * se haya seleccionado.
*/
void KEYPAD_elegir_tecla(){

	if(g_dato_cambiado != g_dato_anterior){ //se evitan rebotes

		switch(g_keypad){

			case KEY_UP:	g_pulsada = UP;
							break;

			case KEY_DOWN: 	g_pulsada = DOWN;
							break;

			case KEY_LEFT: 	g_pulsada = LEFT;
							break;

			case KEY_RIGHT: g_pulsada = RIGHT;
							break;

			case KEY_SELECT: 	g_pulsada = SELECT;
								break;

			default: 	g_pulsada = NADA;
						break;

		}

	}
	else g_pulsada = NADA;

	g_dato_anterior = g_dato_cambiado;
}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/

