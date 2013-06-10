/*********************************************************************
** 																	**
** project : DPD				 									**
** filename : displayRIT.c		 									**
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

#define DISPLAY_RIT_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
**********************************************************************/

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
** LOCAL FUNCTIONS 													**
** 																	**
**********************************************************************/

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
**********************************************************************/
