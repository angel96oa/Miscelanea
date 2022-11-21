/*
Tutorial:
- Programación de interrupciones en C18
- Variables globales e interrupciones
- Uso de los puertos/regitros_SFR y acceso a bits concretos  
- Comportamiento del 'SLEEP'
*/

#include <p18f8520.h>
#pragma config OSC=HS, WDT=OFF, LVP=OFF

void interrupcion_alta(void);
//void interrupcion_baja(void);

volatile int cuenta=1;

//ALTA PRIORIDAD
#pragma code vector_altaI=0x08
void inter_vector_altaI(void)
{
	_asm goto interrupcion_alta _endasm
}
#pragma code //vuelve a la sección de código por defecto

#pragma interrupt interrupcion_alta
void interrupcion_alta(void)
{
	cuenta++;
	if (cuenta>9)  
		cuenta=0;
	INTCONbits.INT0IF=0;
}
////////////////////
/*
BAJA PRIORIDAD
inicialización vector de interrupción: 
#pragma code vector_baja=0x18
void inter_vector_bajaI(void)
{
	_asm goto interrupcion_baja _endasm
}
#pragma code //vuelve a la sección de código por defecto

#pragma interruptlow interrupcion_baja
void interrupcion_baja(void)
{
....
....
}
*/
//////////////////////
void main(void){
ADCON1=0X0f;
TRISA=0X00;
LATA=0;
TRISB=0XFF;



RCONbits.IPEN=0;
INTCONbits.INT0IE=1;
INTCONbits.GIE=1;

while(1){
	Sleep();
	LATA=cuenta;
}

}