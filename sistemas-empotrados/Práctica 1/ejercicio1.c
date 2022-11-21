#include <p18f8520.h>

#pragma config OSC=HS, WDT=OFF, LVP=OFF

//EJERCICIO 1
/*Dsarrollar una aplicacion que permita visualizar sobre cada led asignado
a un bit del puerto A, el estado del pulsador de igual peso correspondiente al
puerto B. De tal manera que si se pulsa RBi se encienda el led RAi.
*/

void main(void){
ADCON1=0x0f;		//ponemos los pines en digital
TRISA=0x00;			//Puerto A de salida
LATA=0;				//Los lat del A los inicializamos a 0 por si queda algun resto residual
TRISB=0xff;			//ponemos el puerto B como entrada

while(1){			//tenemos un bucle infinito para que el programa no se pare

LATA=PORTB;			//el latA tendrá el valor que tenga el puerto B
}

}