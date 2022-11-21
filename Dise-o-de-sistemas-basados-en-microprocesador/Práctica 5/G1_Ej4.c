/******************************************************************

Ejercicio 4 - Practica 5  				Fecha: 16/04/2018


*******************************************************************/

#include <16f877a.h>

#USE DELAY (CLOCK=8M)
#FUSES NOWDT, HS, NOLVP
#USE FAST_IO(B)						//Para configurar manualmente los TRIS de los puertos correspondientes

#BIT PORTB0=0x6.0
#BYTE PORTD=0x8
main(){
	set_tris_b(1);					//Se inicializa el bit 0 del puerto B como entrada y el puerto D como salida
	set_tris_d(0);
	output_b(0);					//Se ponen a 0 los puertos B y D
	output_d(0);
	
	while(1){						//Bucle infinito
		if(PORTB0==1){				//Si el boton esta pulsado
			PORTD++;				//Se incremente el valor del puerto D
			while(PORTB0==1);		//PAra evitar que se mantenga pulsado e incremente de mas
		}
	}
}