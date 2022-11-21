#include <p18f8520.h>
#include <delays.h>
#include <stdio.h>

#pragma config OSC=HS, WDT=OFF, LVP=OFF

/*
EJERCICIO 2
Desarrollar una aplicacion que encienda cada 0.5 segundos un led del puerto B
(de menor a mayor peso), durante 0.5 segundos y posteriormente los leds correspondientes
al puerto D (de mayor a menor peso). El proceso debe repetirse hasta que se active el pulsador
correspondiente a RB0, quedando a partir de ese momento encendidos los leds del puerto B y D.
*/

//variables que vamos a usar para controlar que leds se activan

volatile int i = 0;
volatile int cuenta=1;

//llamada a la funcion de interrupcion
void interrupcion(void);

//establece el vector de rutina del servicio de interrupcion para la funcion interrupcion
#pragma code vector_interrupcion=0x08

//interrupcion que nos llama a la funcion interrupcion(void)
void inter_interrupcion(void){
	_asm goto interrupcion _endasm
}

#pragma interrupt interrupcion
void interrupcion(void){
	if(PORTBbits.RB0 == 1){ //comprueba que se esté pulsando RB0
		TRISBbits.RB0 = 0; //lo pone a 0 para que no haya rebotes ni nuevas llamadas de interrupcion
		TRISB=0x00;		//ponemos el trisb de salida
		//Si queremos activar todo el registro, poniendo el registro a FF, en activan todos los bits
		LATB=0xff;
		LATD=0xff;
		while(1){};	//bucle infinito para que el estado de los puertos no cambie
	}
}

void main(void){
	ADCON1=0x0f;	//ponemos los pin en modo digital
	//ponemos el puerto B y D de salida y sus respectivos LAT a 0
	TRISB=0x00;
	LATB=0x00;
	TRISD=0x00;
	LATD=0x00;
		
	RCONbits.IPEN=0; //Desabilitamos las interrupciones por prioridad
	INTCONbits.INT0IE=0; //Desactivamos interrupciones externas
	INTCONbits.INT0IF=0; //Descativamos el flag de la interrupcion
	INTCONbits.GIE=1;    //Habilitamos las interrupciones globales

	while(1){
		INTCONbits.INT0IF=0; //desactivamos el flag
		INTCONbits.INT0IE=0; //activamos la interrupcion ya que ahoramismo el puerto B está puesto de entrada y si se activa RB0 es necesario que lo detecte
		TRISBbits.RB0 = 0;//Ahora mismo no lee pero imprime
		LATB=cuenta;	//el latb tiene el valor de cuenta, que en un principio, es 1
		Delay10KTCYx(125); //Delay para apreciar el encendido del led

		for(i=0; i<8;i++){ //vamos a recorrer el puerto
			TRISB=0x00;		//el trisb de salida
			cuenta=cuenta*2; //como cada posicion del led es un numero en binario, necesitamos que se exprese en potencia de 2, por ello, 
							 //si empezamos por el 1 y vamos multiplicando por 2, iremos obteniendo el valor con el que se activa cada bit
			INTCONbits.INT0IF=0; //desactivamos el flag
			INTCONbits.INT0IE=1; //activamos la interrupcion ya que ahoramismo el puerto B está puesto de entrada y si se activa RB0 es necesario que lo detecte
			TRISBbits.RB0 = 1;
			LATB=cuenta; //le pasamos el valor al LATB para que lo represente sobre los leds
			Delay10KTCYx(5000); //Delay para que se aprecie la activacion de cada led
		}
		//como el puerto D queremos que se active de mayor a menor, y el ultimo valor obtenido en el bucle anterior es 128, se lo pasamos al LATD para que lo
		//represente sobre su led correspondiente
        LATD=cuenta;
		//ponemos el LATB a 0 para dejar todos los leds del puerto desactivados 
		LATB=0x00;
		//el funcionamiento de este bucle es el mismo que el anterior pero al reves, vamos buscando la potencia de 2 pero de mayor a menor partiendo 
		//de 128 y llegando a 1
		for(i=8;i>=0; i--){
				LATD=cuenta;
				cuenta=cuenta/2;
				INTCONbits.INT0IF=0; //desactivamos el flag
				INTCONbits.INT0IE=1; //activamos la interrupcion ya que ahoramismo el puerto B está puesto de entrada y si se activa RB0 es necesario que lo detecte
				TRISBbits.RB0 = 1;
				Delay10KTCYx(5000);
		}
		//para dar sensacion de que rotacion, le pasamos al LATB el valor como 1 y, puesto que estamos en un bucle while infinito, volverá 
		// a realizar los mismos pasos descritos anteriormente
		cuenta=1;
		LATB=cuenta;
		LATD=0x00;
		INTCONbits.INT0IF=0; //desactivamos el flag
	}	
}