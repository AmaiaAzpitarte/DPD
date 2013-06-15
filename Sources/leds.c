/*************************************************************************************************
** @file    leds.c																				**
** @brief   Fichero donde se controlan los leds													**
** @par		L&oacute;gica																		**
**			- Se inicializan y se habilitan el puerto y los pines donde se conectan los leds	**
**			- Se encienden y se apagan los leds													**
** @author  Amaia Azpitarte																		**
** @date    2013-06-06																			**
*************************************************************************************************/

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
#define LEDS_C
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

extern int g_linea;

extern t_lineapedido lineapedido_1;

extern t_lineapedido lineapedido_2;

extern t_lineapedido lineapedido_3;

/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

int g_valor_leds;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

void LEDS_init(){

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

void LEDS_controlar_leds(int leds){

	//
	// Output leds' values
	//
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, leds);

}


void LEDS_escoger_leds(int operario){

	g_valor_leds = 0x00;

	if(g_linea == 0) g_valor_leds = 0x00; // DPD_ESPERA
	else g_valor_leds = LEDS_consultar_operarios(operario); // UNA_LINEA | MENU_PRIMERO | MENU_SEGUNDO | MENU_TERCERO

	LEDS_controlar_leds(g_valor_leds);

}

void LEDS_escoger_leds_dos_lineas(){ // DOS_LINEAS

	g_valor_leds = 0x00;

	int led1=0x00;
	int led2=0x00;

	led1= LEDS_consultar_operarios(lineapedido_1.operario);
	led2= LEDS_consultar_operarios(lineapedido_2.operario);
	g_valor_leds = led1 | led2;

	LEDS_controlar_leds(g_valor_leds);

}

void LEDS_escoger_leds_tres_lineas(){ // TRES_LINEAS

	LEDS_controlar_leds(0x07);

}

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

