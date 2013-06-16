/**
 * @file    framebuffer.h
 * @brief   Cabecera del fichero framebuffer.c
 * @par		Declaraciones:
 *			- \b MAX_ELEMS	Indica la cantidad m&aacute;xima de elementos que puede haber
 * 			- \b Tipo_DISPLAY_ELEMENT Se define la estructura de los elementos a dibujar en display, con los siguientes campos:
 * 				- \b id					Identificador del elemento
 * 				- \b x					Coordenada x nueva del display en el que debe dibujarse
 * 				- \b y 					Coordenada y nueva del display en el que debe dibujarse
 * 				- \b xOld				Coordenada x actual del display donde est&aacute; dibujado
 * 				- \b yOld				Coordenada y actual del display donde est&aacute; dibujado
 * 				- \b width				Anchura del tipo de letra
 * 				- \b height				Altura del tipo de letra
 * 				- \b picture_or_text	El texto o el dibujo a mostrar en display
 * 				- \b what				Indica si el elemento es un texto o un dibujo
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

/*****************************************************************************
** 																			**
** MODULES USED																**
** 																			**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
*****************************************************************************/

// Indica la cantidad máxima de elementos que puede haber en el buffer
#define MAX_ELEMS 10

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
*****************************************************************************/

void FRAME_BUFFER_init();

int FRAME_BUFFER_insert_image(unsigned char *puc, int x, int y, int w, int h);

int FRAME_BUFFER_insert_text(char *texto, int x, int y);

void FRAME_BUFFER_actualiza_posicion_elemento(int id, int x, int y);

int FRAME_BUFFER_delete_element(int id);

void FRAME_BUFFER_write_to_display(void);

void FRAME_BUFFER_delete_row(int y);

/*****************************************************************************
** 																			**
** EXPORTED VARIABLES	 													**
** 																			**
*****************************************************************************/
/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

// Estructura del buffer
struct Tipo_DISPLAY_ELEMENT{

	int id;
	int x;
	int y;
	int xOld;
	int yOld;
	int width;
	int height;
	char* picture_or_text;
	int what; // 0=IMAGE, 1=TEXT

};

// Se crea el buffer DISPLAY_ELEMENT, del tipo de estructura Tipo_DISPLAY_ELEMENT
typedef struct Tipo_DISPLAY_ELEMENT DISPLAY_ELEMENT;

#ifndef _FRAMEBUFFER_C
#define _PUB_FRAMEBUFFER extern
#else
#define _PUB_FRAMEBUFFER
#endif

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
*****************************************************************************/

#endif
