/****************************************************************************************/
*																						 *
/										README											 /
*																						 *
/****************************************************************************************/

	EL PROGRAMA:
	
	Este programa implementa la l�gica de un DPD (Digital Picking Device). Hay dos 
	funcionalidades distintas:
		- DPD sin sensor
		- DPD con sensor
		
	La implementaci�n se ha realizado mediante dos m�quinas de estados que ejecutan las 
	acciones necesarias en cada momento.
	
	Cuando llega una l�nea al DPD, se muestra la cantidad en el display y se enciende el 
	led correspondiente al operario que debe realizar esa l�nea de pedido.
	
	Si hay m�s de una l�nea de pedido en el DPD, se muestra en el display que hay m�s de 
	una operaci�n por realizar y se encienden los leds correspondientes a los operarios 
	que deben realizar esas l�neas de pedido.
	
	En el caso de que haya m�s de una l�nea en el DPD, el operario debe pulsar el bot�n 
	de men� (bot�n UP) para poder visualizar la l�nea de pedido que le corresponde.
	
	Cuando el operario realiza la operaci�n, en el caso de que el DPD no disponga de sensor,
	lo �nico que debe hacer es pulsar la tecla de confirmaci�n (bot�n SELECT). Si el DPD
	dispone de sensor, primero debe coger los productos de la ubicaci�n correcta, es decir, 
	se debe detectar movimiento en la ubicaci�n, y despu�s debe pulsar la tecla de 
	confirmaci�n (bot�n SELECT).
	
/****************************************************************************************/

	FICHEROS DEL PROGRAMA:

	El proyecto consta de un fichero "main.c" en el que se encuentra el programa principal
	y se ejecuta la m�quina de estados mediante el superloop. 
	
	Los ficheros "Automata.c" y "Automata.h" recogen la l�gica de una m�quina de estados 
	gen�rica, de manera que se puede ejecutar cualquier m�quina de estados mediante estos 
	ficheros.
	
	Para escoger una de las funcionalidades del DPD, con sensor o sin sensor, se debe 
	definir DPD_SENSOR en el fichero "DPD_Config.h" cuando se quiere el DPD con sensor, y si 
	se quiere la funcionalidad del DPD sin sensor, se debe comentar el define de DPD_SENSOR.
	
	Los ficheros "DPD.c" y "DPD.h", o "DPD_sensor.c" y "DPD_sensor.h", recogen la definici�n 
	de las estructuras necesarias para que se implemente el DPD siguiendo la l�gica de 
	"Automata.c". 
	
	Las funciones correspondientes al DPD han sido definidas en distintos ficheros. Cada uno
	se ha definido con sus respectivos nombres y ficheros cabecera, de modo que pueden ser
	reemplazados f�cilmente en el caso de que el HW utilizado se modifique.
	
	Por otra parte, el fichero "display.c" hace uso del Frame Buffer definido en 
	"framebuffer.c" para hacer mejor uso de la pantalla. Este Frame Buffer es gen�rico, es
	decir, no est� especificado para ning�n display en concreto. Por lo tanto, hace uso del 
	fichero "displayRIT.c" para utilizar las funciones espec�ficas del display RIT128x96x4.
	
/****************************************************************************************/

	ESTRUCTURA Y ORGANIZACI�N DEL PROGRAMA
	
	Al mismo nivel que el fichero "main.c" hay varias carpetas, que contienen los siguientes 
	ficheros del proyecto "Automata":
	
		- DPD_Config.h
	
		- Automata		=>	Automata.c
							Automata.h
					
		- DPD			=>	DPD.c
							DPD.h
					
		- DPD_SENSOR	=>	DPD_sensor.c
							DPD_sensor.h
										
		- Headers		=>	clock.h
							conf_timer.h
							data_structs.h
							display.h
							displayGenerico.h
							framebuffer.h
							inicializacion.h
							keypad.h
							leds.h
							received_data.h
							sensor.h
							sonido.h	
						
		- Sources		=>	clock.c
							conf_timer.c
							display.c
							displayRIT.c
							framebuffer.c
							inicializacion.c
							keypad.c
							leds.c
							received_data.c
							sensor.c
							sonido.c
							
		- Simulacion_linea	=>	simulacion_linea.c
								simulacion_linea.h							
					
/****************************************************************************************/	
	
	PUESTA EN MARCHA DEL PROGRAMA
	
	Para poder poner en marcha el programa y que la aplicaci�n funcione sobre la placa 
	Stellaris EKS-LM3S8962, hace falta la siguiente carpeta con los siguientes ficheros o 
	drivers:
	
		-Utiles		=>	rit128x96x4.c
						rit128x96x4.h										 
	
	Por otro lado, en el fichero "cmsisboot\startup\startup_lm3s.c" hay que a�adir las 
	siguientes l�neas para que funcione el timer 0:
	
		- En "Function prototypes"	=>	extern void TIMER_timer0_int_handler(void);
	
		- En "External Exceptions"	=>	TIMER_timer0_int_handler,
	 