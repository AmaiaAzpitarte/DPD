/*****************************************************************************
**											  								**
** project :  DPD							 							  	**
** filename : framebuffer.h  				  					    		**
** version : 1 									  							**
** date :  	2013-06-03		 		 									    **
** 											  								**
******************************************************************************
** 											  								**
**                      											  		**
**  								  					                    **
** 											  								**
******************************************************************************
**										        							**
**VERSION HISTORY:									  						**
**----------------									  						**
**Version : 1										  						**
**Date : 2013-06-03									 					    **
**Revised by : Amaia Azpitarte	          									**
**Description : Original version.							  				**
*****************************************************************************/
/*****************************************************************************
** 																			**
** DEFINITIONS AND MACROS 													**
** 																			**
******************************************************************************/

#ifndef _CONSOLE_H

#define _CONSOLE_H

#define MAX_ELEMS 10

/*****************************************************************************
** 																			**
** PROTOTYPES OF GLOBAL FUNCTIONS											**
** 																			**
******************************************************************************/

void FRAME_BUFFER_init();

int FRAME_BUFFER_insert_image(unsigned char *puc, int x, int y, int w, int h);

int FRAME_BUFFER_insert_text(char *texto, int x, int y);

void FRAME_BUFFER_actualiza_posicion_elemento(int id, int x, int y);

int FRAME_BUFFER_delete_element(int id);

void FRAME_BUFFER_write_to_display(void);

void FRAME_BUFFER_delete_row(int y);

/*****************************************************************************
**	 																		**
** TYPEDEFS AND STRUCTURES 													**
** 																			**
*****************************************************************************/

#ifndef CONSOLE_C

#define PUB_CONSOLE extern

#else

#define PUB_CONSOLE

#endif

/*Creamos la estructura del buffer*/
struct Tipo_DISPLAY_ELEMENT{

	int id;
	int x;
	int y;
	int xOld;
	int yOld;
	int width;
	int height;
	char* picture_or_text;
	int what; /*0=IMAGE, 1=TEXT*/

};

/*Creamos un buffer: DISPLAY_ELEMENT*/
typedef struct Tipo_DISPLAY_ELEMENT DISPLAY_ELEMENT;

/*****************************************************************************
** 																			**
** EOF 																		**
** 																			**
******************************************************************************/

#endif
