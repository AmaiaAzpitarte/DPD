/**
 * @file   	display.c
 * @brief   Fichero donde se inicializa el display y se escribe en &eacute;l
 * @par		L&oacute;gica
 *			- Se inicializa el display
 *			- Se escribe un texto en el display
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

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
 * @brief   Inicializa el display
 * @par		L&oacute;gica:
 * 			- Inicializa el display
 * @return  void
*/
void DISPLAY_inicializacion_display(){

	FRAME_BUFFER_init();

}

/**
 * @brief  	Funci&oacute;n para escribir en la pantalla
 * @par		L&oacute;gica:
 *			- Se inserta un texto en el buffer
 *			- Se vuelca el buffer en el display
 * @param	*puc Guarda el texto a escribir en pantalla
 * @param	x 	Coordenada \e x donde debe escribirse el texto
 * @param	y	Coordenada \e y donde debe escribirse el texto
 * @return   void
 *
 * Se inserta un texto en el buffer y se vuelca el buffer en el display
 *
*/
void DISPLAY_escribir_en_pantalla(unsigned char *puc, int x, int y){

	//Variable donde se guardará el id de los elementos creados
	int identificador;

	identificador = FRAME_BUFFER_insert_text(puc, x, y);

	//Volcamos el buffer en la pantalla
	FRAME_BUFFER_write_to_display();

	FRAME_BUFFER_delete_element(identificador);

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
