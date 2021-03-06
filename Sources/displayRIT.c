/**
 * @file   	displayRIT.c
 * @brief   Fichero donde se recogen las funciones b&aacute;sicas del display de la Stellaris LM3S8962
 * @par		L&oacute;gica
 *			- Se inicializa el display
 *			- Se escribe un texto en el display
 *			- Se dibuja una imagen en el display
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#define _DISPLAY_RIT_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "Headers/displayGenerico.h"
#include "Utiles/rit128x96x4.h"
#include "string.h"

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
** TYPERDEFS AND STRUCTURES											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** EXPORTED VARIABLES												**
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
*********************************************************************/

/**
 * @brief  	Funci&oacute;n para escribir un texto en pantalla
 * @par		L&ogica:
 * 			- Escribe un texto en la pantalla
 * @param	*pcStr	Guarda el texto que debe escribirse en pantalla
 * @param	ulX		Coordenada \e x donde debe escribirse el texto
 * @param	ulY		Coordenada \e y donde debe escribirse el texto
 * @param	ucLevel	Nivel del texto que debe escribirse en pantalla
 * @return  void
 *
 */
void DISPLAY_GENERICO_dibuja_string(const char *pcStr, unsigned long ulX,
		unsigned long ulY, unsigned char ucLevel){

	RIT128x96x4StringDraw(pcStr,ulX,ulY,ucLevel);

}

/**
 * @brief  	Funci&oacute;n para dibujar una imagen en pantalla
 * @par		L&ogica:
 * 			- Dibuja una imagen en la pantalla
 * @param	*pucImage	Guarda la imagen que debe dibujarse en pantalla
 * @param	ulX			Coordenada \e x donde debe dibujarse la imagen
 * @param	ulY			Coordenada \e y donde debe dibujarse la imagen
 * @param	ulWidth		Anchura de la imagen
 * @param	ulHeight		Altura de la imagen
 * @return  void
 */
void DISPLAY_GENERICO_dibuja_imagen(unsigned char *pucImage, int ulX,
		int ulY, int ulWidth,int ulHeight){

	RIT128x96x4ImageDraw(pucImage,ulX,ulY,ulWidth,ulHeight);

}

/**
 * @brief  Funci&oacute;n para inicializar pantalla
 * @par		L&oacute;gica:
 * 			- Inicializa la pantalla
 * @return   void
 */
void DISPLAY_GENERICO_init(){

	RIT128x96x4Init(1000000);

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
