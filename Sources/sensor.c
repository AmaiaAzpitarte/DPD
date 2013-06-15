/*************************************************************************************************
** @file    sensor.c																			**
** @brief   Fichero donde se lee el sensor														**
** @par		L&oacute;gica																		**
**			- Se inicializan y se habilitan el puerto y los pines donde se conecta el sensor	**
**			- Se lee el valor del sensor, para ver si ha habido movimiento						**
** @author  Amaia Azpitarte																		**
** @date    2013-06-10																			**
*************************************************************************************************/


/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"

/*********************************************************************
**																	**
** DEFINITIONS AND MACROS											**
** 																	**
*********************************************************************/
#define SENSOR_C
/*********************************************************************
**																	**
** TYPEDEFS AND STRUCTURES											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/
/*********************************************************************
**																	**
** GLOBAL VARIABLES													**
** 																	**
*********************************************************************/
int g_movimiento;
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

void SENSOR_init(){

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

}

void SENSOR_detectar_movimiento(){
	g_movimiento = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
