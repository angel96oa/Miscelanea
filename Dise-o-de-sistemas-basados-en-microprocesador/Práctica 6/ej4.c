/******************************************************************

Ejercicio 3 - Practica 6  				Fecha: 17/04/2018


*******************************************************************/

#include <16f877a.h>

#USE DELAY (CLOCK=8M)
#FUSES NOWDT,HS,NOLVP
#USE FAST_IO(B)						//Para configurar manualmente los TRIS de los puertos correspondientes
#include "lcd_digi2.c"

#BIT PORTB0=0x6.0

void main(){
	signed int i;
	int j;
	char ing[10] = "INGENIERIA";
	char inf[11] = "INFORMATICA";
	LCD_INIT();
	
	for(i=0;i<5;i++){
		LCD_PUTC('\f');
		delay_ms(1000);
		LCD_GOTOXY(6,1);
		printf(lcd_putc,"ESCUELA");
		LCD_GOTOXY(4,2);
		printf(lcd_putc,"SUPERIOR DE");
		delay_ms(3000);
	}
	
	while(PORTB0!=1);
	LCD_PUTC('\f');
	
	LCD_GOTOXY(4,1);
	for(i=0;i<10;i++){
		delay_ms(500);
		printf(lcd_putc,"%c",ing[i]);
	}
	
	j=14;
	for(i=10;i>=0;i--){
		LCD_GOTOXY(j,2);
		delay_ms(500);
		printf(lcd_putc,"%c",inf[i]);
		j--;
	}
	
	while(1);
}