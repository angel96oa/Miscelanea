/******************************************************************

Ejercicio 2 - Practica 5  				Fecha: 16/04/2018


*******************************************************************/

#include <16f877a.h>

#USE DELAY (CLOCK=8M)
#FUSES NOWDT, HS, NOLVP
#USE FAST_IO(B)						//Para configurar manualmente los TRIS de los puertos correspondientes

#BYTE PORTB=0x6
main(){
	set_tris_b(0);					//Pone puerto B como salida
	output_b(1);					//Se pone a 1 el bit 0 de puerto B
	while(1){						//Bucle infinito
		 rotate_left(&PORTB,1);		//Rota a la izquierda el bit del puerto B
		 delay_ms(500);				//Retardo para visualizar el comportamiento
	}
}