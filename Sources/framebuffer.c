/**
 * @file   	framebuffer.c
 * @brief   Fichero donde se define el framebuffer para dibujar o escribir en display
 * @par		L&oacute;gica
 *			- Se inicializa el framebuffer
 *			- Se definen distintos elementos para textos e im&aacute;genes
 *			- Se dibujan esos elementos en el display
 *			- Se eliminan esos elementos
 *			- Se borran l&iacute;neas del display
 * @author  Amaia Azpitarte
 * @date    2013-06-03
 */

#define _FRAMEBUFFER_C

/*********************************************************************
**																	**
** MODULES USED 													**
** 																	**
*********************************************************************/

#include <stdio.h>
#include <string.h>
#include "Utiles/rit128x96x4.h"

#include "Headers/displayGenerico.h"
#include "Headers/framebuffer.h"

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
** EXPORTED VARIABLES	 											**
** 																	**
*********************************************************************/
/*********************************************************************
** 																	**
** GLOBAL VARIABLES 												**
** 																	**
*********************************************************************/

// Indica la cantidad máxima de elementos que puede haber
DISPLAY_ELEMENT g_display_elements[MAX_ELEMS];

// Número de elementos que hay en el buffer
int g_display_element_kop = 0;

// Imagen para borrar un círculo
const unsigned char g_puc_nada[32]  =  {

		0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00

};

/*********************************************************************
** 																	**
** LOCAL FUNCTIONS 													**
** 																	**
*********************************************************************/

/**
 * @brief   Inicializaci&oacute;n de la pantalla y el buffer
 * @par		L&oacute;gica:
 * 			- Se inicializa la pantalla
 * 			- Se crea el buffer para un n&uacute;mero de elementos definido en MAX_ELEMS
 * @return    void
 */
void FRAME_BUFFER_init(){

	int i = 0;

	// Inicializa la pantalla
	DISPLAY_GENERICO_init();

	// Crea el buffer
	for (i=0; i<MAX_ELEMS; i++){

		g_display_elements[i].id = i;
		g_display_elements[i].x = i;
		g_display_elements[i].y = i;
		g_display_elements[i].width = i;
		g_display_elements[i].height = i;
		g_display_elements[i].picture_or_text = i;
		g_display_elements[i].what = i;

	}

}

/**
 * @brief   Inserta una imagen en el buffer
 * @par		L&oacute;gica:
 * 			- Se crea un elemento del tipo \e what=0 (imagen)
 * 			- Se especifica la imagen que debe tomar, la posici&oacute;n y dimensiones
 * 			- Se devuelve el n&uacute;mero de elementos que hay en el buffer una vez a&ntilde;adido &eacute;ste
 * @param	puc	Imagen del elemento a crear
 * @param	x	Coordenada \e x del elemento a crear
 * @param	y	Coordenada \e y del elemento a crear
 * @param	w	Anchura del elemento a crear
 * @param	h	Altura del elemento a crear
 * @return  \b display_element_kop	N&uacute;mero de elementos que hay en el buffer
 */
int FRAME_BUFFER_insert_image(unsigned char *puc, int x, int y, int w, int h){

	if(g_display_element_kop < MAX_ELEMS){

		g_display_elements[g_display_element_kop].id = g_display_element_kop;
		g_display_elements[g_display_element_kop].picture_or_text = puc;
		g_display_elements[g_display_element_kop].what = 0; // 0 para imagen
		g_display_elements[g_display_element_kop].x = x;
		g_display_elements[g_display_element_kop].y = y;
		g_display_elements[g_display_element_kop].width = w;
		g_display_elements[g_display_element_kop].height = h;
		g_display_element_kop ++; // Aumentamos el número de elementos que hay en el buffer

	}

	return g_display_element_kop;

}

/**
 * @brief   Inserta un texto en el buffer
 * @par		L&oacute;gica:
 * 			- Se crea un elemento del tipo \e what=1 (texto)
 * 			- Se especifica el texto que debe tomar y la posici&oacute;n
 * 			- Se devuelve el n&uacute;mero de elementos que hay en el buffer una vez a&ntilde;adido &eacute;ste
 * @param	texto	Texto del elemento a crear
 * @param	x	Coordenada \e x del elemento a crear
 * @param	y	Coordenada \e y del elemento a crear
 * @return  \b display_element_kop	N&uacute;mero de elementos que hay en el buffer
 */
int FRAME_BUFFER_insert_text(char *texto, int x, int y){

	if(g_display_element_kop < MAX_ELEMS){

		g_display_elements[g_display_element_kop].id = g_display_element_kop;
		g_display_elements[g_display_element_kop].picture_or_text = texto;
		g_display_elements[g_display_element_kop].what = 1; // 1 para texto
		g_display_elements[g_display_element_kop].x = x;
		g_display_elements[g_display_element_kop].y = y;
		g_display_elements[g_display_element_kop].width = 0;
		g_display_elements[g_display_element_kop].height = 0;
		g_display_element_kop ++; // Aumenta número de elementos que hay en el buffer

	}

	return g_display_element_kop;

}

/**
 * @brief 	Cambia la posici&oacute;n de un elemento existente
 * @par		L&oacute;gica:
 * 			- Se guardan las coordenadas anteriores en \e xOld e \e yOld
 * 			- Se guardan las nuevas coordenadas en \e x e \e y
 * @param	id	Identificador del elemento a mover
 * @param	x 	Coordenada \e x al que mover el elemento
 * @param	y	Coordenada \e y al que mover el elemento
 * @return  void
 */
void FRAME_BUFFER_actualiza_posicion_elemento(int id, int x, int y){

	// Posición actual en el eje x
	int x_actual;

	// Posición actual en el eje y
	int y_actual;

	// Obtener posición actual
	x_actual = g_display_elements[id].x;

	y_actual = g_display_elements[id].y;

	// Borrar del FrameBuffer
	g_display_elements[id].xOld = x_actual;

	g_display_elements[id].yOld = y_actual;

	// Actualizar valor
	g_display_elements[id].x = x;

	g_display_elements[id].y = y;

}

/**
 * @brief   Borra un elemento del buffer
 * @par		L&oacute;gica:
 * 			- Saca el elemento de la pantalla
 * 			- Desplaza los elementos con una id mayor a la posici&oacute;n anterior del buffer
 * 			- Reduce una vez el n&uacute;mero de elementos del buffer
 * @param	id	Identificador del elemento a borrar
 * @return  \b display_element_kop	N&uacute;mero de elementos que hay en el buffer
 */
int FRAME_BUFFER_delete_element(int id){

	// Posición del elemento en el eje x
	int x_actual;

	// Posición del elemento en el eje y
	int y_actual;

	int i;

	// Obtener posición actual
	x_actual = g_display_elements[id].x;

	y_actual = g_display_elements[id].y;

	// Borrar del FrameBuffer
	g_display_elements[id].xOld = x_actual;

	g_display_elements[id].yOld = y_actual;

	// Actualizar valor
	g_display_elements[id].x = -5;

	g_display_elements[id].y = -5;

	for(i=id;i<MAX_ELEMS;i++){

		g_display_elements[i].picture_or_text = g_display_elements[i + 1].picture_or_text;
		g_display_elements[i].what = g_display_elements[i + 1].what; // 1 para texto
		g_display_elements[i].x = g_display_elements[i + 1].x;
		g_display_elements[i].y = g_display_elements[i + 1].y;
		g_display_elements[i].width = g_display_elements[i + 1].width;
		g_display_elements[i].height = g_display_elements[i + 1].height;

	}

	// Reduce número de elementos que hay en el buffer
	g_display_element_kop =  g_display_element_kop - 1;

	return g_display_element_kop;

}

/**
 * @brief 	Volcar el buffer en la pantalla
 * @par		L&oacute;gica:
 * 			- Se vuelcan todos los elementos del buffer en la pantalla
 * 			- Se mira uno a uno si el elemento es un texto a una imagen
 * 			- Se borran los innecesarios y se muestran los elementos necesarios
 * @return  void
 */
void FRAME_BUFFER_write_to_display(void){

	int i=0;

	// Tamaño del string
	int size = 0;

	// Índice de posición en el array str
	int index =0;

	// Array donde se va a guardar el string
	char str[30];

	// Volcamos todos los elementos existentes en el buffer
	for(i=0;i< g_display_element_kop; i++){

		if(( g_display_elements[i].xOld != g_display_elements[i].x ) ||
				(g_display_elements[i].yOld != g_display_elements[i].y )){

			if(g_display_elements[i].what==1){ // Es un texto

				size = strlen(g_display_elements[i].picture_or_text);

				for(index = 0; index < size; index ++){

					str[index]= ' ';

				}

				str[index]='\0';

				DISPLAY_GENERICO_dibuja_string(str, g_display_elements[i].xOld,g_display_elements[i].yOld, 30);

				DISPLAY_GENERICO_dibuja_string(g_display_elements[i].picture_or_text, g_display_elements[i].x,
						g_display_elements[i].y, 30);

			}else { // Es una imagen

				DISPLAY_GENERICO_dibuja_imagen(g_puc_nada, g_display_elements[i].xOld, g_display_elements[i].yOld,
						g_display_elements[i].width, g_display_elements[i].height);

				DISPLAY_GENERICO_dibuja_imagen(g_display_elements[i].picture_or_text, g_display_elements[i].x,
						g_display_elements[i].y, g_display_elements[i].width, g_display_elements[i].height);

			}

		}

	}

}

/**
 * @brief  	Borra una l&iacute;nea de la pantalla
 * @par		L&oacute;gica:
 * 			- Borra la l&iacute;nea \e y del buffer
 * 			- Vuelca el buffer en la pantalla
 * @param	y	Coordenada \e y de la l&iacute;nea a borrar
 * @return  void
 */
void FRAME_BUFFER_delete_row(int y){

	// Índice de posición en el array str
	int index =0;

	// Array donde se va a guardar el string
	char str[150];

	for(index=0;index<80;index++){

		str[index]= ' ';

	}

	DISPLAY_escribir_en_pantalla(str, 0, y);

}

/*********************************************************************
** 																	**
** EOF 																**
** 																	**
*********************************************************************/
