/**
 * @file    leds.c
 * @brief   Fichero donde se controlan los leds
 * @par		L&oacute;gica
 *			- Se inicializan y se habilitan el puerto y los pines donde se conectan los leds
 *			- Se encienden y se apagan los leds
 * @author  Amaia Azpitarte
 * @date    2013-06-06
 */

#define _LEDS_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "Headers/leds.h"

#include "DPD_Config.h"

#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "Headers/received_data.h"
#include "Headers/data_structs.h"

#include "Headers/inicializacion.h"

/*********************************************************************
**																	**
** DEFINITIONS AND MACROS											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

// Variable que indica la cantidad de líneas por realizar que hay en el DPD
extern int g_linea;

// Estructura donde se guardan los parámetros de la línea de pedido 1
extern t_lineapedido lineapedido_1;

// Estructura donde se guardan los parámetros de la línea de pedido 2
extern t_lineapedido lineapedido_2;

// Estructura donde se guardan los parámetros de la línea de pedido 3
extern t_lineapedido lineapedido_3;

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

// Variable donde se guarda el valor de los leds
int g_valor_leds;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief  	Inicializaci&oacute;n de los leds
 * @par		L&oacute;gica:
 * 			- Inicializa el puerto B
 *			- Inicializa los pines donde se conectan los leds, configur&aacute;ndolos como output
 *			- Apaga los leds
 * @return 	void
 */
void LEDS_init(){

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);

	// Apagar los leds desde el principio
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, 0x00000000);

}

/**
 * @brief  	Escribe el valor de los leds, encendiendo o apagando estos
 * @par		L&oacute;gica:
 * 			- Escribe el valor de los leds en los pines correspondientes, para encender o apagar los leds
 * @param	leds	valor que define qu&eacute; leds se deben apagar y cu&aacute;les se deben encender
 * @return 	void
 */
void LEDS_controlar_leds(int leds){

	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, leds);

}

/**
 * @brief  	Define el valor que deben tener los leds para el caso en el que solo se deba encender uno de los leds (estados: UNA_LINEA, MENU_PRIMERO, MENU_SEGUNDO_ MENNU_TERCERO)
 * @par		L&oacute;gica:
 * 			- Si no hay ninguna l&iacute;nea por realizar en el DPD, apaga todos los leds (\b g_valor_leds=0x00)
 * 			- Si hay una l&iacute;nea por realizar, consulta el operario de esa l&iacute;nea y cambia el valor de la variable \b g_valor_leds al correspondiente a ese operario
 * 			- Escribe el valor definido para g_valor_leds en los leds
 * @param	operario	Define el operario que debe realizar la l&iacute;nea de pedido
 * @return 	void
 */
void LEDS_escoger_leds(int operario){

	g_valor_leds = 0x00;

	if(g_linea == 0) g_valor_leds = 0x00; // DPD_ESPERA
	else g_valor_leds = LEDS_consultar_operarios(operario); // UNA_LINEA | MENU_PRIMERO | MENU_SEGUNDO | MENU_TERCERO

	LEDS_controlar_leds(g_valor_leds);

}

/**
 * @brief  	Define el valor que deben tener los leds para el caso en el que se deben encender dos leds (estado: DOS_LINEAS)
 * @par		L&oacute;gica:
 * 			- Consulta los operarios de las dos l&iacute;neas que hay en el DPD
 * 			- Cambia el valor de la variable \b g_valor_leds al correspondiente a esos operarios
 * 			- Escribe el valor definido para g_valor_leds en los leds
 * @return 	void
 */
void LEDS_escoger_leds_dos_lineas(){ // DOS_LINEAS

	g_valor_leds = 0x00;

	int led1=0x00;
	int led2=0x00;

	led1= LEDS_consultar_operarios(lineapedido_1.operario);
	led2= LEDS_consultar_operarios(lineapedido_2.operario);
	g_valor_leds = led1 | led2;

	LEDS_controlar_leds(g_valor_leds);

}

/**
 * @brief  	Define el valor que deben tener los leds para el caso en el que se deben encender tres leds (estado: TRES_LINEAS)
 * @par		L&oacute;gica:
 * 			- Cambia el valor de la variable \b g_valor_leds para encender los tres leds
 * 			- Escribe el valor definido para g_valor_leds en los leds
 * @return 	void
 */
void LEDS_escoger_leds_tres_lineas(){ // TRES_LINEAS

	LEDS_controlar_leds(0x07);

}

/**
 * @brief  	Dependiendo del valor de la variable \e operario, devuelve un valor distinto para los leds
 * @par		L&oacute;gica:
 * 			- Dependiendo del valor de la variable \e operario, devuelve un valor distinto para los leds:
 * 				- Si es el \e operario_1, devuelve \e 0x01
 * 				- Si es el \e operario_2, devuelve \e 0x02
 * 				- Si es el \e operario_3, devuelve \e 0x04
 * @param	operario	Define el operario que debe realizar la l&iacute;nea de pedido
 * @return 	void
 */
int LEDS_consultar_operarios(int operario){

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
*********************************************************************/

