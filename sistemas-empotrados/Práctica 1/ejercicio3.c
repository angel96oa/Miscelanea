#include <p18f8520.h>
#pragma config OSC=HS, WDT=OFF, LVP=OFF

/*
EJERCICIO 3

Desarrollar una aplicacion que cuente el número de veces que se cierra el pulsador RB0
y las muestre en binario natural por el puerto D, evitando posibles rebotes.
*/

//variable sobre la que iremos haciendo las sumas
volatile int suma=0;

void main(void){

	ADCON1=0x0f; //ponemos los puertos en digital
	TRISB=0xff;  //ponemos el PORTB de entrada
	LATB=0x00;   //Al iniciar su LAT a 0, evitaremos sumas innecesarias al inicio de la ejecucion del programa
	TRISD=0x00;  //ponemos el PORTD de salida 
	LATD=0x00;   //ponemos un 0 en el LATD para evitar que ningun valor residual afecte a nuestro programa

	while(1){
		if(PORTBbits.RB0==1){	 //si detecta la pulsacion en RB0
			while(PORTB & 0x0f); //evitamos rebotes
			suma=suma+1;		 //sumamos
			LATD=suma;			 //mostramos el valor en binario natural
		}

	}
}