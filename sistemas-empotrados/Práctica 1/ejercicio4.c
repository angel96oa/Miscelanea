#include <p18f8520.h>
#include <delays.h>
#include <xlcd.h>

#pragma config OSC=HS, WDT=OFF, LVP=OFF

//Delay10KTCYx(50); -> 5 segundos

/*
EJERCICIO 5
Desarrollar una aplicación que escriba en el LCD del entrenador el texto siguiente:
El texto debe mostrarse de la siguiente manera:
- La linea superior debe aparecer caracter a caracter de derecha a izquierda
- La linea inferior se mostrará caracter a caracter de izquierda a derecha
- A continuacion todo debe parpadear a la vez cinco veces, con una frecuencia de 0.5 segundos
- Por ultimo, se intercambiaran la lina uno y dos, de de la formas mas rapida posible
*/

//funciones necesarias para definirlas debido a la libreria xlcd.h y delays.h
void DelayFor18TCY(void){
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
}

void DelayPORXLCD(void){
	Delay1KTCYx(75);
}
void DelayXLCD(void){
	Delay1KTCYx(25);
}

//Envia comando al LCD
void comandXLCD(unsigned char a){
	BusyXLCD();
	WriteCmdXLCD(a);
}

//Ubica cursor en: x = posición en linea, y = N de linea.
void gotoxyXLCD(unsigned char x, unsigned char y){
	unsigned char direccion;

	if(y != 1){
		direccion = 0x40;
	}else{
		direccion = 0;
	}

	direccion += x-1;
	comandXLCD(0x80 | direccion);
}

void main(void){
		int a = 7, i;
		char sistemas[8]="SISTEMAS";
		char empotrados[10]="EMPOTRADOS";

		OpenXLCD(EIGHT_BIT & LINES_5X7);   //Iniciamos el LCD			
		comandXLCD(0x01); //borra la pantalla y vuelve al origen

	for(a=8; a>=0; a--){
		gotoxyXLCD(a+5,1);  //Pasamos a la primera linea, posicion 12
		putcXLCD(sistemas[a]); //imprimimos 1 a 1 los caracteres
		Delay10KTCYx(200); //delay para poder apreciar la salida
	}
	

	a=0;

	for(a=0; a<9; a++){
		gotoxyXLCD(5+a,2); //hacemos lo mismo que antes con la línea e abajo
		putcXLCD(empotrados[a]); 
		Delay10KTCYx(200);
	}

	for(i=0;i<5;i++){
		comandXLCD(0x01);
		Delay10KTCYx(50);

		gotoxyXLCD(5,1); //imprimimos la primera linea
		putrsXLCD("SISTEMAS");
		gotoxyXLCD(5,2); //imprimimos la segunda linea
		putrsXLCD("EMPOTRADOS");

		Delay10KTCYx(50);
	}

	comandXLCD(0x01);  //Borrar pantalla y vuelve a origen	

	Delay10KTCYx(50);

	gotoxyXLCD(5,1);  
	putrsXLCD("EMPOTRADOS"); //imprimimos la primera linea

	gotoxyXLCD(5,2);  
	putrsXLCD("SISTEMAS"); //imprimimos la segunda linea

	while(1){}
		
}