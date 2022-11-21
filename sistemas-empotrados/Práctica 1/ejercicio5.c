#include <p18f8520.h>
#include <delays.h>
#include <xlcd.h>
#include <stdio.h>

#pragma config OSC=HS, WDT=OFF, LVP=OFF

/*
EJERCICIO 5
Utilizando el modulo de teclado, cuyo esquema se muestra en la figura, desarrollar
una aplicacion, mediante interrupciones si es posible, que realice las siguientes funciones:
- Escribir en la primera linea del LCD en valor de la tecla pulsada si esta se corresponde con un digito decimal
- En la segunda linea aparecera el mensaje 'teclas pulsadas:' y el numero de veces que se pulsó una tecla del cero al nueve
*/

//variable para ir cambiando la posicion en la linea del lcd
volatile int lcdX=1;
//variable que cuenta las veces que pulsamos un numero
volatile int teclaspulsadas=0;

//Delay10KTCYx(50); -> 5 segundos

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




//establece el vector de rutina del servicio de interrupcion para la funcion ISRPulsacion
#pragma interrupt ISRPulsacion
void ISRPulsacion(void){
	
	char c[3];	
	LATB=0x00;

	//INTERRUPCION 1, 4, 7, *
	//si detecta el flag de la primera interrupcion
	if(INTCONbits.INT0IF==1){
		INTCONbits.INT0IF=0; //Ponemos el flag a 0 para que cuando acabe las acciones de interrupcion no vuelve a ser llamado
			LATB=0x10; //cogemos la posicion 0x10 que se va a encargar de activar la linea en la que estan 1, 4, 7, *
			if(INTCONbits.INT0IF){ //si detecta el flag de interrupcion activado, comprueba que tecla esta pulsada
				if(PORTBbits.RB4){ //tecla correspondiente a 1
					INTCONbits.INT0IF=0; //baja el flag para que no detecte una interrupcion que no se esta dando
					Nop(); //el nop se incluye para que en la placa real los botones no den problemas en relacion a la electronica de la placa
					gotoxyXLCD(lcdX,1); //nos situacion en la primera posicion libre
					putcXLCD('1'); //escribimos el 1 en el LCD
					teclaspulsadas++; //incrementamos el contador
					lcdX++; //pasamos a la siguiente linea
					INTCONbits.INT0IF=0; //limpiamos el flag para que no haya problema de llamamiento a la interrupcion cuando no debe
					LATB=0x00;	//limpiamos el LAT para que no haya problemas con las futuras llamadas
				}
			}
			//de forma analoga al primer caso
			LATB=0x20;
			if(INTCONbits.INT0IF){
				if(PORTBbits.RB5){
					INTCONbits.INT0IF=0;
					Nop();
					gotoxyXLCD(lcdX,1);
					putcXLCD('4');
					teclaspulsadas++;
					lcdX++;
					INTCONbits.INT0IF=0;
					LATB=0x00;	
				}
			}
			//de forma analoga al primer caso
			LATB=0x40;
			if(INTCONbits.INT0IF){
				if(PORTBbits.RB6){
					INTCONbits.INT0IF=0;
					Nop();
					gotoxyXLCD(lcdX,1);
					putcXLCD('7');
					teclaspulsadas++;
					lcdX++;
					INTCONbits.INT0IF=0;
					LATB=0x00;	
				}
			}
	}

	//INTERRUPCIÓN 2, 5, 8, 0
	//de forma analoga a los 4 primeros botones, pero considerando distintos botones de la matriz, y puesto que van por pines distintos, hay que
	//tener en consideracion que la interrupcion en este caso INT1 y que sus flag será INT1IF, y van por INTCON3. Por lo demás, la logica de funcionamiento
	//es la misma
	if(INTCON3bits.INT1IF==1){
		INTCON3bits.INT1IF=0;
		
		LATB=0x10;
		if(INTCON3bits.INT1IF){
			if(PORTBbits.RB4){
				INTCON3bits.INT1IF=0;
				Nop();
				gotoxyXLCD(lcdX,1);
				putcXLCD('2');
				teclaspulsadas++;
				lcdX++;
				INTCON3bits.INT1IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x20;
		if(INTCON3bits.INT1IF){
			if(PORTBbits.RB5){
				INTCON3bits.INT1IF=0;
				Nop();
				gotoxyXLCD(lcdX,1);
				putcXLCD('5');
				teclaspulsadas++;
				lcdX++;
				INTCON3bits.INT1IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x040;
		if(INTCON3bits.INT1IF){
			if(PORTBbits.RB6){
				INTCON3bits.INT1IF=0;
				Nop();
				gotoxyXLCD(lcdX,1);
				putcXLCD('8');
				teclaspulsadas++;
				lcdX++;
				INTCON3bits.INT1IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x80;
		if(INTCON3bits.INT1IF){
			if(PORTBbits.RB7){
				INTCON3bits.INT1IF=0;
				Nop();
				gotoxyXLCD(lcdX,1);
				putcXLCD('0');
				teclaspulsadas++;
				lcdX++;
				INTCON3bits.INT1IF=0;
				LATB=0x00;	
			}
		}

	}
		//de forma analoga a los 4 primeros botones, pero considerando distintos botones de la matriz, y puesto que van por pines distintos, hay que
	//tener en consideracion que la interrupcion en este caso INT2 y que sus flag será INT2IF, y van por INTCON3. Por lo demás, la logica de funcionamiento
	//es la misma
	//INTERRUPCION 3, 6, 9
	if(INTCON3bits.INT2IF==1){
		INTCON3bits.INT2IF=0;
		LATB=0x10;
		if(INTCON3bits.INT2IF){
			if(PORTBbits.RB4){
				INTCON3bits.INT2IF=0;
				Nop();
				gotoxyXLCD(lcdX,1);
				putcXLCD('3');
				teclaspulsadas++;
				lcdX++;
				INTCON3bits.INT2IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x20;
		if(INTCON3bits.INT2IF){
			if(PORTBbits.RB5){
				INTCON3bits.INT2IF=0;
				Nop();
				gotoxyXLCD(lcdX,1);
				putcXLCD('6');
				teclaspulsadas++;
				lcdX++;
				INTCON3bits.INT2IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x40;
		if(INTCON3bits.INT2IF){
			if(PORTBbits.RB6){
				INTCON3bits.INT2IF=0;
				Nop();
				gotoxyXLCD(lcdX,1);
				putcXLCD('9');
				teclaspulsadas++;
				lcdX++;
				INTCON3bits.INT2IF=0;
				LATB=0x00;	
			}
		}

	}

	
	//mostramos en el 6,2 el valor del contador 
	sprintf(c,"%d",teclaspulsadas);
	gotoxyXLCD(6,2);
	putsXLCD(c);
	
	//para que no haya error tras coger un digito anteriormente
	LATB=0xF0;

	//limpiamos flag para evitar interrupciones recursivas
	INTCONbits.INT0IF=0;
	INTCON3bits.INT1IF=0;
	INTCON3bits.INT2IF=0;

	Delay10KTCYx(80);

}


//interrupcion que llama a la funcion ISRPulsacion
#pragma code inter_pulsacion=0x08
void vector_inter_pulsacion(void){
	_asm goto ISRPulsacion _endasm
} 
#pragma code


void main(void){
	INTCONbits.INT0IF=0;
	INTCONbits.INT0IE=1; //activamos la interrupcion INT0
	INTCON3bits.INT1IF=0;
	INTCON3bits.INT1IE=1; //activamos la interrupcion INT1
	INTCON3bits.INT2IF=0;
	INTCON3bits.INT2IE=1; //activamos la interrupcion INT2

	INTCONbits.GIE=1; //activamos las interrupciones generales

	TRISB=0x0F; //el nible de menor peso se configura como entrada
	LATB=0xF0; // se inicializan los LAT a 0
	OpenXLCD(EIGHT_BIT & LINES_5X7);   //Iniciamos el LCD

	gotoxyXLCD(1,2);
	putrsXLCD("N: "); //teclas pulsadas
	while(1){
		Sleep();
		
	}
		
}