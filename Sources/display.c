/*********************************************************************************
** @file   	display.c															**
** @brief   Fichero donde se inicializa el display y se escribe en &eacute;l	**
** @par		L&oacute;gica														**
**			- Se inicializa el display											**
**			- Se escribe un texto en el display									**
** @author  Amaia Azpitarte														**
** @date    2013-06-03															**
*********************************************************************************/
#define _DISPLAY_C
/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/
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
void DISPLAY_inicializacion_display(){

	FRAME_BUFFER_init();

}

/**
 * @brief  Función para escribir en la pantalla.
 *
 * @return   void
 *
 * Se inserta un texto en el buffer y se vuelca el buffer en el display
 *
*/
void DISPLAY_escribir_en_pantalla(unsigned char *puc, int x, int y){

	int identificador; /*Variable donde se guardará el id de los elementos creados*/

	identificador = FRAME_BUFFER_insert_text(puc, x, y);

	FRAME_BUFFER_write_to_display(); /*Volcamos el buffer en la pantalla*/

	FRAME_BUFFER_delete_element(identificador);

}
/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
