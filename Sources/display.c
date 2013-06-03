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

#include "DPD/DPD.h"

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

int identificador; /*Variable donde se guardará el id de los elementos creados*/

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

/**
 * @brief  Inicializamos y escribimos los tres estados del semáforo
 * y el círculo en la pantalla.
 *
 * @return    -
 *
 * Primero se inicializa el buffer, y luego se escribeen el display.
 *
*/

void DPD_inicializacion_display(){

	//FRAME_BUFFER_delete_row(10);

	FRAME_BUFFER_init();

	//str = "DPD_ESPERA";

	//FRAME_BUFFER_insert_text(str, 5, 10);

}

/**
 * @brief  Función para escribir en la pantalla.
 *
 * @return   void
 *
 * Se inserta un texto en el buffer y se vuelca el buffer en el display
 *
*/

void DPD_escribir_en_pantalla(unsigned char *puc, int x, int y){

	identificador = FRAME_BUFFER_insert_text(puc, x, y);

	FRAME_BUFFER_write_to_display(); /*Volcamos el buffer en la pantalla*/

	FRAME_BUFFER_delete_element (identificador);

}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
**********************************************************************/
