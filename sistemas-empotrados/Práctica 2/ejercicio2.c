#include <p18f8520.h>
#include <delays.h>
#include <xlcd.h>
#include <stdio.h>
#include <usart.h>

#pragma config OSC=HS, WDT=OFF, LVP=OFF


/*
EJERCICIO 1

¿Qué es un modem nulo, cómo se puede conectar a la placa UNI-DS3 al PC?

Es un cable cuya funcion es conectar terminales mediante un cable RS232.
Para que su funcionamiento sea correcto, debemos cruzar la línea de recepcion
y la linea de transmisión (RTS y CTS), asi, la linea de recepcion sera la de
transmision del otro, y de forma analoga en la otra dirección.

*/

/*
EJERCICIO 2

Escribir un programa que envíe el valor de la tecla pulsada en el teclado hexadecimal de la
placa UNI-DS3 al PC y que reciba en el LCD los mensajes que se escriban desde el teclado
del PC, utilizando recepción por interrupciones en la MCU. Se recomienda una
configuracion de la RS232 de 9600,8,N,1 ¿qué terminales de la MCU utilizarás para
trasmisión?

NOTA: para simular el terminal RS232 podéis usar el instrumento Virtual terminal de la
paleta Virtual Instruments Mode o el componente COMPIM. En este ultimo caso seria
necesario instalar previamente un software emulador de puertos COM, como por ejemplo
Virtual Serial Port Driver, Virtual Serial Port o similar.
*/

//variable
unsigned char caracterTeclado;



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
	while(BusyXLCD());
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
					caracterTeclado='1'; //indicamos el caracter que vamos a enviar por la usart
					putc1USART(caracterTeclado); //enviamos el caracter por la usart
					INTCONbits.INT0IF=0; //limpiamos el flag para que no haya problema de llamamiento a la interrupcion cuando no debe
					LATB=0x00; //limpiamos el LAT para que no haya problemas con las futuras llamadas
				}
			}
			//de forma analoga al primer caso
			LATB=0x20;
			if(INTCONbits.INT0IF){
				if(PORTBbits.RB5){
					INTCONbits.INT0IF=0;
					Nop();
					caracterTeclado='4';
					putc1USART(caracterTeclado);
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
					caracterTeclado='7';
					putc1USART(caracterTeclado);
					INTCONbits.INT0IF=0;
					LATB=0x00;	
				}
			}
			//de forma analoga al primer caso
			LATB=0x80;
			if(INTCONbits.INT0IF){
				if(PORTBbits.RB7){
					INTCONbits.INT0IF=0;
					Nop();
					caracterTeclado='*';
					putc1USART(caracterTeclado);
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
					caracterTeclado='2';
					putc1USART(caracterTeclado);
				INTCON3bits.INT1IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x20;
		if(INTCON3bits.INT1IF){
			if(PORTBbits.RB5){
				INTCON3bits.INT1IF=0;
				Nop();
					caracterTeclado='5';
					putc1USART(caracterTeclado);
				INTCON3bits.INT1IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x040;
		if(INTCON3bits.INT1IF){
			if(PORTBbits.RB6){
				INTCON3bits.INT1IF=0;
				Nop();
					caracterTeclado='8';
					putc1USART(caracterTeclado);
				INTCON3bits.INT1IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x80;
		if(INTCON3bits.INT1IF){
			if(PORTBbits.RB7){
				INTCON3bits.INT1IF=0;
				Nop();
					caracterTeclado='0';
					putc1USART(caracterTeclado);
				INTCON3bits.INT1IF=0;
				LATB=0x00;	
			}
		}
	}
	
	//INTERRUPCION 3, 6, 9, #
	//de forma analoga a los 4 primeros botones, pero considerando distintos botones de la matriz, y puesto que van por pines distintos, hay que
	//tener en consideracion que la interrupcion en este caso INT2 y que sus flag será INT2IF, y van por INTCON3. Por lo demás, la logica de funcionamiento
	//es la misma
	if(INTCON3bits.INT2IF==1){
		INTCON3bits.INT2IF=0;
		LATB=0x10;
		if(INTCON3bits.INT2IF){
			if(PORTBbits.RB4){
				INTCON3bits.INT2IF=0;
				Nop();
				caracterTeclado='3';
				putc1USART(caracterTeclado);
				INTCON3bits.INT2IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x20;
		if(INTCON3bits.INT2IF){
			if(PORTBbits.RB5){
				INTCON3bits.INT2IF=0;
				Nop();
				caracterTeclado='6';
				putc1USART(caracterTeclado);
				INTCON3bits.INT2IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x40;
		if(INTCON3bits.INT2IF){
			if(PORTBbits.RB6){
				INTCON3bits.INT2IF=0;
				Nop();
				caracterTeclado='9';
				putc1USART(caracterTeclado);
				INTCON3bits.INT2IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x80;
		if(INTCON3bits.INT2IF){
			if(PORTBbits.RB7){
				INTCON3bits.INT2IF=0;
				Nop();
				caracterTeclado='#';
				putc1USART(caracterTeclado);
				INTCON3bits.INT2IF=0;
				LATB=0x00;	
			}
		}
	}
	
	//INTERRUPCION A, B, C, D
	//de forma analoga a los 4 primeros botones, pero considerando distintos botones de la matriz, y puesto que van por pines distintos, hay que
	//tener en consideracion que la interrupcion en este caso INT3 y que sus flag será INT3IF, y van por INTCON3. Por lo demás, la logica de funcionamiento
	//es la misma
	if(INTCON3bits.INT3IF==1){
		INTCON3bits.INT3IF=0;
		LATB=0x10;
		if(INTCON3bits.INT3IF){
			if(PORTBbits.RB4){
				INTCON3bits.INT3IF=0;
				Nop();
				caracterTeclado='A';
				putc1USART(caracterTeclado);
				INTCON3bits.INT3IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x20;
		if(INTCON3bits.INT3IF){
			if(PORTBbits.RB5){
				INTCON3bits.INT3IF=0;
				Nop();
				caracterTeclado='B';
				putc1USART(caracterTeclado);
				INTCON3bits.INT3IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x40;
		if(INTCON3bits.INT3IF){
			if(PORTBbits.RB6){
				INTCON3bits.INT3IF=0;
				Nop();
				caracterTeclado='C';
				putc1USART(caracterTeclado);
				INTCON3bits.INT3IF=0;
				LATB=0x00;	
			}
		}
		LATB=0x80;
		if(INTCON3bits.INT3IF){
			if(PORTBbits.RB7){
				INTCON3bits.INT3IF=0;
				Nop();
				caracterTeclado='D';
				putc1USART(caracterTeclado);
				INTCON3bits.INT3IF=0;
				LATB=0x00;	
			}
		}
	}
	
	//para que no haya error tras coger un digito anteriormente
	LATB=0xF0;

	//limpiamos flag para evitar interrupciones recursivas

	//flags teclado
	INTCONbits.INT0IF=0;
	INTCON3bits.INT1IF=0;
	INTCON3bits.INT2IF=0;
	INTCON3bits.INT3IF=0;



	Delay10KTCYx(80);

}


//interrupcion que llama a la funcion ISRPulsacion
#pragma code inter_pulsacion=0x08
void vector_inter_pulsacion(void){
	_asm goto ISRPulsacion _endasm
} 
#pragma code


void main(void){

	char vector[100];
	int contadorX = 0;
	char caracter;
	int i = 0;
	int j = 0;
	int lcdX=1;


	//usart
	RCONbits.IPEN =0;     //  Deshabilitamos  Prioridades
	//teclado
	INTCONbits.INT0IF=0;
	INTCONbits.INT0IE=1; //activamos la interrupcion INT0
	INTCON3bits.INT1IF=0;
	INTCON3bits.INT1IE=1; //activamos la interrupcion INT1
	INTCON3bits.INT2IF=0;
	INTCON3bits.INT2IE=1; //activamos la interrupcion INT2
	INTCON3bits.INT3IF=0;
	INTCON3bits.INT3IE=1; //activamos la interrupcion INT3
	INTCONbits.PEIE =1;   //  Habilitamos  interrupcion  de  perifericos.-
	INTCONbits.GIE=1; //activamos las interrupciones generales

	//usart
	TRISC = 0x80; //tx1 a salida, rx0 entrada

	TRISB=0x0F; //el nible de menor peso se configura como entrada
	LATB=0xF0; //se inicializan los LAT a 0


	OpenXLCD(EIGHT_BIT & LINES_5X7);   //Iniciamos el LCD
	
	comandXLCD(0x06); //aseguramos incremento de direccion

	//USART
	//INICIALIZAMOS USART
	Open1USART(USART_TX_INT_OFF & USART_RX_INT_OFF &USART_ASYNCH_MODE & USART_EIGHT_BIT &USART_CONT_RX & USART_BRGH_HIGH ,64);
	gotoxyXLCD(1,1);

	while(1){
		//USART
		if(DataRdy1USART()){
				caracter=Read1USART(); //leemos el dato
				while(BusyXLCD());
				putcXLCD(caracter); //ponemos en el LCD el dato
				vector[i]=caracter; //vamos almacenando caracteres
				i++; //pasamos a la siguiente posicion del vector
				contadorX++; //contador para comprobar la linea en la que estamos
				if(i==100){ //si el vector se llena, lo reiniciamos
					i=0;
					comandXLCD(0x01);
					gotoxyXLCD(1,1);
					contadorX=0;					
				}

			//scroll - respecto al scroll, hay un pequeño error donde no coge la linea
			//correctamente y las muestra con un una posicion del lcd anterior
			if(contadorX == 16){ //comprueba que llega al final de la primera linea
				gotoxyXLCD(1,2); //nos movemos abajo
			} 
			if (contadorX == 32) { //si llega al final del lcd
				comandXLCD(0x01); //borramos XLCD
				gotoxyXLCD(1,1); //nos ponemos en la primera posicion
				for(j=i-17; j<=i; j++){ //mostramos las ultimas posiciones del vector 
					putcXLCD(vector[j]);
					gotoxyXLCD(lcdX,1);
					lcdX++;
				}
				lcdX=1;
				gotoxyXLCD(1,2); //nos movemos al principio de la segunda linea
				contadorX=17; //el contador lo ponemos a 17 para que no entre en el if de la primera linea
			}
		}
	}
}


/*
EJERCICIO 3

¿Cual es la maxima velocidad de transmisión que se puede conseguir? ¿Podrías explicar la razon por la que no
se puede aumentar más la velocidad de transferencia?

Tras realizar distintos calculos de baud rate, hemos concluido que la velocidad maxima a la que se puede transmitir
es de 57600 baudios, ya que cuando probamos con 115200 baudios, el error es demasiado grande y la comunicación no se realiza
correctamente.

*/