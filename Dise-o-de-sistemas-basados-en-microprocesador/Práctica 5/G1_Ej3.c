/******************************************************************

Ejercicio 3 - Practica 5  				Fecha: 16/04/2018


*******************************************************************/

#include <16f877a.h>

#USE DELAY (CLOCK=8M)
#FUSES NOWDT, HS, NOLVP
#USE FAST_IO(B)									//Para configurar manualmente los TRIS de los puertos correspondientes

#BYTE PORTB=0x6
#BYTE PORTD=0x8
int boton();
void finalizar();
main(){
	int i;
	set_tris_b(0);								//Puertos B,C y D como salida y se inicializan a 0
	set_tris_c(0);
	set_tris_d(0);
	output_b(0);
	output_c(0);
	output_d(0);
	
	while(1){
		/*Puerto B - Rota el bit hacia la izquierda, cuando termina se enciende el bit 7 del puerto C y se pasa al puerto D*/
		output_b(1);
		delay_ms(500);
		for(i=0;i<7;i++){
			 rotate_left(&PORTB,1);
			 delay_ms(500);
			 if(boton()%2!=0) finalizar(); //Comprueba el estado del boton
		}
		/*Paso a puerto D - Se inicializa el puerto D para que comience a rotar*/
		output_b(0);
		output_c(0x80);
		delay_ms(500);
		output_c(0);
		/*Puerto D - Rota el bit hacia la derecha, cuando termina se enciende el bit 0 del puerto C y se pasa al puerto B*/
		output_d(0x80);
		delay_ms(500);
		for(i=0;i<7;i++){
			 rotate_right(&PORTD,1);
			 delay_ms(500);
			 if(boton()%2!=0) finalizar(); //Comprueba el estado del boton
		}
		/*Paso a puerto B - Se inicializa el puerto B para que comience a rotar*/
		output_d(0);
		output_c(1);
		delay_ms(500);
		output_c(0);
	}
}

//Se comprueba que el pulsador asignado al bit 0 del puerto B esta pulsado y si esta pulsado, se vá a la rutina finalizar.
int boton(){										
	int boton;
	set_tris_b(1);
	boton=input_b();
	set_tris_b(0);
	return boton;
}

//Se pone a 1 todos los bits de los puertos B y D (0xff) y los bits 0 y 7 del puerto C (0x81)
void finalizar(){
	output_b(0xff);
	output_d(0xff);
	output_c(0x81);
	while(1);
}