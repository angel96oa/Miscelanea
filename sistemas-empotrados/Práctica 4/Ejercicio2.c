#include <p18f8520.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spi.h>

#pragma config OSC=HS, WDT=OFF, LVP=OFF

/*==========================================================================================
Alumnos:
Alvaro Leon Cebrian
Angel Ortega Alfaro

Ejercicio 2 - Practica 4
Escribir un programa en lenguaje C que gestione la lectura de un generador de
señal conectado al canal cero del CI MCP3204, con salida senoidal de Vpp aproximada
de 5v y un offset adecuado para que no existan valores negativos. La señal digitalizada 
debera ser enviada al CI MCP4921, para ser comparada con la original.
==========================================================================================*/

void main(void){
	//Declaramos las variables que vamos a utilizar en el programa
	unsigned int nivelBajo, nivelAlto, digital1, digital2;
	
	//Procedemos a inicializar el Bus SPI
	//La funcion OpenSPI tiene tres parametros de configuracion: modo del reloj, modo del bus y fase
	OpenSPI(SPI_FOSC_64, MODE_11, SMPEND);
	LATEbits.LATE3 = 1; //Chip Select es la entrada de seleccion del chip y esta configurado a 1
						//para que podamos detectar el flanco de bajada en el conversor A/D
	LATEbits.LATE4 = 1; //De igual forma, lo configuramos a 1 para que podamos detectar el 
						//flanco de bajada en el conversor D/A
	LATEbits.LATE5 = 0; //El pin LDAC es utilizado para transferir el registro de entrada al registro DAC
						//Cuando este pin esta configurado a 0, el pin VOUT se actualiza con el contenido del
						//del registro de entrada
	TRISEbits.TRISE3 = 0; //Configuramos pin 'RE3' como salida
	TRISEbits.TRISE4 = 0; //Configuramos pin 'RE4' como salida
	TRISEbits.TRISE5 = 0; //Configuramos pin 'RE5' como salida
	
	while(1){
		//Conversion A/D
		LATEbits.LATE3 = 0; //0 para que coja el flanco de bajada y empiece la transmision
		WriteSPI(0x06); 	//3 primeros bits correspondientes al inicio de la transmision
		WriteSPI(0x00); //indicamos canal
		nivelAlto = 0x0F & SSPBUF; //cogemos solo la parte baja que estamos leyendo
		nivelBajo = ReadSPI(); 
		LATEbits.LATE3 = 1; //flanco de subida para que para la transmision

		//tratamiento datos
		digital1 = 0x30 | nivelAlto;
		digital2 = nivelBajo;

		//Conversion D/A - funcionamiento análogo a la conversión D/A
		LATEbits.LATE4 = 0;
		WriteSPI(digital1);
		WriteSPI(digital2);
		LATEbits.LATE4 = 1;

	}
}
