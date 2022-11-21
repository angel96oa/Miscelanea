/******************************************************************

Ejercicio 3 - Practica 6  				Fecha: 17/04/2018


*******************************************************************/

#include <16f877a.h>

#USE DELAY (CLOCK=8M)
#FUSES NOWDT,HS,NOLVP
#USE FAST_IO(B)						//Para configurar manualmente los TRIS de los puertos correspondientes
#include "lcd_digi2.c"

void main(){
	signed int i;
	int j,ms=100;
	char ing[10] = "INGENIERIA";
	char inf[11] = "INFORMATICA";
	LCD_INIT();
	LCD_GOTOXY(4,1);
	for(i=0;i<10;i++){
		delay_ms(ms);
		printf(lcd_putc,"%c",ing[i]);
	}
	
	j=14;
	for(i=10;i>=0;i--){
		LCD_GOTOXY(j,2);
		delay_ms(ms);
		printf(lcd_putc,"%c",inf[i]);
		j--;
	}
	
	while(1);
}