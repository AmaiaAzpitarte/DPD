/**
 * @file    sonido.c
 * @brief   Fichero donde se controla el altavoz
 * @par		L&oacute;gica
 *			- Se inicializa el PWM
 *			- Se reproduce el sonido
 * @author  Amaia Azpitarte
 * @date    2013-06-05
 */

#define _SONIDO_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "hw_types.h"
#include "hw_pwm.h"
#include "hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "Headers/sonido.h"

/*********************************************************************
**																	**
** DEFINITIONS AND MACROS											**
** 																	**
*********************************************************************/
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

// Frecuencia del clock
extern unsigned long g_system_clock;

/*********************************************************************
**																	**
** GLOBAL VARIABLES													**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief  	Inicializacai&oacute;n del PWM.
 * @par		L&oacute;gica:
 * 			- Se inicializa el clock del PWM, y luego los pines correspondientes
 * 			- Se apaga el generador para configurar su contador, y se vuelve a encender
 * 			- Se especifica el volumen y se activa la salida del PWM
 * @return  void
 */
void SONIDO_init(){

	//clock pwm
	SysCtlPWMClockSet(SYSCTL_PWMDIV_8);

	//Configuramos los pines 0 y 1 del puerto G como PWM
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
	GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_0);
	GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_1);

	// Apagamos el  PWM generator
	PWMOutputState(PWM_BASE,  PWM_OUT_1_BIT, false);
	PWMGenDisable(PWM_BASE, PWM_GEN_0);

	// Configuracion, contador up/down.
	PWMGenConfigure(PWM_BASE, PWM_GEN_0,
	PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_SYNC);

	// Activamos pwm
	PWMGenEnable(PWM_BASE, PWM_GEN_0);

	//Especificamos la ganancia.Volumen.
	HWREG(PWM_BASE + PWM_GEN_0_OFFSET + PWM_O_X_CMPB) = 50;
	PWMSyncUpdate(PWM_BASE, PWM_GEN_0_BIT);

	//Activamos la salida del pwm
	PWMOutputState(PWM_BASE, PWM_OUT_1_BIT, true);

}

/**
 * @brief  	Reproducir una nota con el PWM.
 * @par		L&oacute;gica:
 * 			- Se activa el PWM con la frecuencia seleccionada
 * @return  void
*/
void SONIDO_reproducir_nota(note_frecuency){

	PWMGenPeriodSet(PWM_BASE, PWM_GEN_0,(g_system_clock /(note_frecuency * 8)));
	PWMSyncUpdate(PWM_BASE, PWM_GEN_0_BIT);

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
