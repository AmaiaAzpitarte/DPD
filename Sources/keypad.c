/**
 * @file    keypad.c
 * @brief   Fichero donde se controla el keypad, detectando las teclas pulsadas
 * @par		L&oacute;gica
 *			- Se inicializa el keypad
 *			- Se lee el valor del keypad
 *			- Se detecta qu&eacute; tecla se ha pulsado
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#define _KEYPAD_C

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
#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif

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
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

// Valor leído en los botones
unsigned long g_keypad = 0x1f;

// Variable donde se guarda la tecla pulsada
char g_pulsada;

// Variable donde se guarda el valor del keypad para detectar cuándo se vuelve a pulsar una tecla
unsigned long g_dato_cambiado;

// Variable donde se guarda el valor anterior del keypad
unsigned long g_dato_anterior;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief  	Inicializa el teclado (los botones)
 * @par		L&oacute;gica:
 * 			- Inicializa los puertos \e F y \e E
 * 			- Inicializa los pines correspondientes a los botones
 * 			- Habilita los pines de los botones como input
 * @return	void
 *
 */
void KEYPAD_init(){

	// Activa los pines del puerto F (botón select)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIOPinTypeGPIOInput( GPIO_PORTF_BASE, GPIO_PIN_1); // Pin 1

	GPIOPadConfigSet( GPIO_PORTF_BASE, GPIO_PIN_1 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

	// Activa los pines del puerto E (botones up, down, right, left)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_0); // Pin 0

	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_0 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_1); // Pin 1

	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_1 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_2); // Pin 2

	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_2 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

	GPIOPinTypeGPIOInput( GPIO_PORTE_BASE, GPIO_PIN_3); // Pin 3

	GPIOPadConfigSet( GPIO_PORTE_BASE, GPIO_PIN_3 , GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

}

/**
 * @brief  	Lee el bot&oacute;n pulsado en el teclado
 * @par		L&oacute;gica:
 * 			- Se lee el valor del keypad
 * 			- Se guarda en \e g_dato_cambiado el valor de \e dato_pulsado XOR el dato anterior (para evitar los rebotes causados por el keypad)
 * 			- Se guarda en \e g_keypad el dato pulsado
 * @return     void
 */
void KEYPAD_leer_keypad(){

	// Guarda el valor de la tecla pulsada
	unsigned long dato_pulsado;

	dato_pulsado = (GPIOPinRead( GPIO_PORTE_BASE , (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3) )|
					    	(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1) << 3));
	// Para evitar los rebotes
	g_dato_cambiado = g_keypad ^ dato_pulsado;

	g_keypad = dato_pulsado;

}

/**
 * @brief  	Le da valor a la tecla
 * @par		L&oacute;gica:
 * 			- Se mira si el dato ha cambiado desde la pulsaci&oacute;n anterior (para evitar rebotes)
 * 			- Dependiendo de la tecla pulsada, se le da un valor a la variable \e g_pulsada
 * @return	void
 */
void KEYPAD_elegir_tecla(){

	// Para evitar rebotes
	if(g_dato_cambiado != g_dato_anterior){

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

