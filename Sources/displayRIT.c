/*************************************************************************************************
** @file   	displayRIT.c																		**
** @brief   Fichero donde se recogen las funciones básicas del display de la Stellaris LM3S8962	**
** @par		L&oacute;gica																		**
**			- Se inicializa el display															**
**			- Se escribe un texto en el display													**
**			- Se dibuja una imagen en el display												**
** @author  Amaia Azpitarte																		**
** @date    2013-06-03																			**
*************************************************************************************************/

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include "Headers/displayGenerico.h"
#include "Utiles/rit128x96x4.h"
#include "string.h"

#include "DPD_Config.h"

/*********************************************************************
** 																	**
** DEFINITIONS AND MACROS 											**
** 																	**
*********************************************************************/
#ifdef DPD_SENSOR
	#include "DPD_sensor/DPD_sensor.h"
#else
	#include "DPD/DPD.h"
#endif

#define DISPLAY_RIT_C

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
 * @brief  Función para escribir en pantalla.
 *
 * @return  void
 *
*/
void DISPLAY_GENERICO_dibuja_string(const char *pcStr, unsigned long ulX,
		unsigned long ulY, unsigned char ucLevel){

	RIT128x96x4StringDraw(pcStr,ulX,ulY,ucLevel);

}

/**
 * @brief  Función para dibujar en pantalla.
 *
 * @return   void
 *
*/
void DISPLAY_GENERICO_dibuja_imagen(unsigned char *pucImage, int ulX,
		int ulY, int ulWidth,int ulHeight){

	RIT128x96x4ImageDraw(pucImage,ulX,ulY,ulWidth,ulHeight);

}

/**
 * @brief  Función para inicializar pantalla.
 *
 * @return   void
 *
*/
void DISPLAY_GENERICO_init(){

	RIT128x96x4Init(1000000);

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
