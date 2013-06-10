/*********************************************************************
** 																	**
** project : DPD			 										**
** filename : sensor.c 												**
** version : 1 														**
** date : June 10, 2013 											**
** 																	**
**********************************************************************
** 																	**
** Copyright (c) 2013,					 							**
** All rights reserved. 											**
** 																	**
**********************************************************************
**																	**
**VERSION HISTORY:													**
**----------------													**
**Version : 1														**
**Date : June 10, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/
#define SENSOR_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"

/*********************************************************************
** 																	**
** EXPORTED VARIABLES 												**
** 																	**
*********************************************************************/

int movimiento;

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

void DPD_inicializacion_sensor(){

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

}

void DPD_detectar_movimiento(){
	movimiento = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
