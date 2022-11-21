/******************************************************************

Ejercicio 1 - Practica 8  				Fecha: 16/04/2018


*******************************************************************/

#include <16f877a.h>
#device adc= 10

#USE DELAY (CLOCK=8M)
#FUSES NOWDT, HS, NOLVP
#USE FAST_IO(B)						//Para configurar manualmente los TRIS de los puertos correspondientes

#include "lcd_digi2.c"

main(){
	long var;
	float calc;
	
	setup_adc(ADC_CLOCK_INTERNAL);
	setup_adc_ports(AN0);
	LCD_INIT();
	
	while(1){
		delay_us(20);
		var = read_adc();
		set_adc_channel(0);
		calc=var*4.883/1000
		LCD_PUTC('\f');	
		LCD_GOTOXY(1,1);
		printf(lcd_putc,"%ld",var);
		LCD_GOTOXY(1,2);
		printf(lcd_putc,"%f",calc);
		delay_ms(100);
	}
}