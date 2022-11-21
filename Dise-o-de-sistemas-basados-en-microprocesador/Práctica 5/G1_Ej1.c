/******************************************************************

Ejercicio 1 - Practica 5  				Fecha: 16/04/2018


*******************************************************************/		

#include <16f877a.h>

#USE DELAY (CLOCK=8M)
#FUSES NOWDT, HS, NOLVP

#BYTE porta=0x5
#BYTE portb=0x6
#BYTE trisa=0x85
#BYTE trisb=0x86

main(){ 				
	trisa=63;			//Puerto A como entrada
	trisb=0;			//Puerto B como salida
	porta=0;			//Se inicializa Puerto A, todos los bits a 0
	portb=0;			//Se inicializa Puerto A, todos los bits a 0
	while(1){			//Bucle infinito
		portb=porta;	//Pasamos el valor de puerto A a puerto B
	}
}