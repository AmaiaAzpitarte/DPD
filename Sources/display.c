/*********************************************************************
** 																	**
** project : DPD				 									**
** filename : display.c		 										**
** version : 1 														**
** date : June 03, 2013		 										**
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
**Date : June 03, 2013												**
**Revised by : Amaia Azpitarte										**
**Description : Original version. 									**
*********************************************************************/
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

#include "Utiles/rit128x96x4.h"

#include "Headers/display.h"
#include "Headers/displayGenerico.h"
#include "Headers/framebuffer.h"

#include "DPD_Config.h"

#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif

#include "Headers/inicializacion.h"

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
**********************************************************************/

#define DISPLAY_C

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
/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

/**
 * @brief  Inicializamos y escribimos los tres estados del sem�foro
 * y el c�rculo en la pantalla.
 *
 * @return    -
 *
 * Primero se inicializa el buffer, y luego se escribeen el display.
 *
*/

void DISPLAY_inicializacion_display(){

	FRAME_BUFFER_init();

}

/**
 * @brief  Funci�n para escribir en la pantalla.
 *
 * @return   void
 *
 * Se inserta un texto en el buffer y se vuelca el buffer en el display
 *
*/

void DISPLAY_escribir_en_pantalla(unsigned char *puc, int x, int y){

	int identificador; /*Variable donde se guardar� el id de los elementos creados*/

	identificador = FRAME_BUFFER_insert_text(puc, x, y);

	FRAME_BUFFER_write_to_display(); /*Volcamos el buffer en la pantalla*/

	FRAME_BUFFER_delete_element(identificador);

}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
