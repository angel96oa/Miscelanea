/******************************************************************

Ejercicio 3 - Practica 6  				Fecha: 17/04/2018


*******************************************************************/

#include <16f877a.h>
#include <STDLIB.h>

#USE DELAY (CLOCK=8M)
#FUSES NOWDT,HS,NOLVP
#USE FAST_IO(B)						//Para configurar manualmente los TRIS de los puertos correspondientes
#include "lcd_digi2.c"

#BYTE PORTB=0x6

//Variables
int moscaX, moscaY, sentido, moscaFin=0;
int miraX, miraY, muerta=0;
int mSalv=0, mMuert=0;
int timer, continuar=0;
int mover;
int temporizador=100;
int menut=0;
int nMoscas=0;
int sumado=0;

void mosca();
void imprimir();
void menu();

#INT_TIMER0
void timer0_isr(){
	timer++;
	set_timer0(217);
	if (timer==temporizador){
		continuar=1;
		timer=0;
	}
}

#INT_EXT
void ext_disparar(){
	if(miraX==moscaX && miraY==moscaY && muerta==0 && menut==1){
		moscaFin=1;
		mMuert++;
		muerta=1;
		imprimir();
	}
	
	if(menut==0){
		menut=1;
	}
}

#INT_RB
void ext_mover(){
	if(menu==1){
		mover=PORTB;
		switch (mover){
			case 16:
				miraY=1;
				imprimir();
				break;
			case 32:
				miraY=2;
				imprimir();
				break;
			case 64:
				if(miraX>1){
					miraX--;
				}
				imprimir();
				break;
			case 128:
				if(miraX<13){
					miraX++;
				}
				imprimir();
				break;
		}
	}
}

void main(){
	setup_timer_0(RTCC_internal | RTCC_DIV_256);	
	ext_int_edge(l_to_h);
	enable_interrupts(int_timer0 | int_ext | int_rb | global);
	srand(get_timer0());
	set_tris_b(0xff);
	
	LCD_INIT();
	
	int i;
	
	menu();
	
	miraX=7;
	miraY=1;
	
	imprimir();
	
	for(i=0;i<nMoscas;i++){
		mosca();
	}
	
	
	LCD_PUTC('\f');	
	LCD_GOTOXY(15,1);					//Se imprime el contador de moscas salvadas
	printf(lcd_putc,"%d",mSalv);
	disable_interrupts(int_timer0 | int_ext | int_rb | global);
	LCD_GOTOXY(15,2);					//Se imprime el contador de moscas muertas
	printf(lcd_putc,"%d",mMuert);
	if(mMuert>mSalv){
		LCD_GOTOXY(6,1);					
		printf(lcd_putc,"HAS");
		LCD_GOTOXY(5,2);					
		printf(lcd_putc,"GANADO");
	} else{
		LCD_GOTOXY(6,1);					
		printf(lcd_putc,"HAS");
		LCD_GOTOXY(5,2);					
		printf(lcd_putc,"PERDIDO");
	}
	while(1);
}

void mosca(){
	moscaX=(rand() % 4)+6;
	moscaY=(rand() % 2)+1;
	sentido=(rand() % 2);				//0-> Izquierda | 1-> Derecha
	imprimir();
	timer=0;
	set_timer0(217);
	moscaFin=0;
	muerta=0;
	while(moscaFin==0){ 		
		while(continuar==0);
		continuar=0;
		if(sentido==0){
			moscaX--;
		}else{
			moscaX++;
		}
		imprimir();
		if((moscaX<=0 || moscaX >14) && moscaFin==0){
			moscaFin=1;					//La mosca se ha salvado
			mSalv++;
		}
	}
	return;
}

void imprimir(){
	LCD_PUTC('\f');						//Se limpia el LCD
	LCD_GOTOXY(moscaX,moscaY);			//Se imprime la mosca
	printf(lcd_putc,"*");
	
	LCD_GOTOXY(miraX,miraY);			//Se imprime la mira
	printf(lcd_putc,"+");
	
	LCD_GOTOXY(15,1);					//Se imprime el contador de moscas salvadas
	printf(lcd_putc,"%d",mSalv);
	
	LCD_GOTOXY(15,2);					//Se imprime el contador de moscas muertas
	printf(lcd_putc,"%d",mMuert);
	
	if(moscaX==miraX && moscaY==miraY){
		LCD_GOTOXY(miraX,miraY);
		printf(lcd_putc,"X");
	}
	return;
}

void menu(){
	LCD_PUTC('\f');
	while(menut==0){
	LCD_GOTOXY(1,1);					
	printf(lcd_putc,"!!!MATAMOSCAS!!!");
	LCD_GOTOXY(4,2);
	printf(lcd_putc,"         ");
	delay_ms(1000);
	LCD_GOTOXY(4,2);
	printf(lcd_putc,"RB0-START");
	delay_ms(1000);
	}
	
	LCD_PUTC('\f');
	LCD_GOTOXY(3,1);					
	printf(lcd_putc,"RB1-FACIL");
	LCD_GOTOXY(3,2);					
	printf(lcd_putc,"RB2-DIFICIL");
	while(PORTB!=2 && PORTB!=4){
		if(PORTB==2){
			temporizador=100;
		}
		if(PORTB==4){
			temporizador=25;
		}
	}
	while(PORTB==4);
	LCD_PUTC('\f');
	while(PORTB!=4){
		LCD_GOTOXY(1,1);					
		printf(lcd_putc,"RB1-ADD MOSCA %d",nMoscas);
		LCD_GOTOXY(2,2);					
		printf(lcd_putc,"RB2-!JUGAR!");
		if(PORTB==2 && sumado==0){
			nMoscas++;
			LCD_PUTC('\f');
			sumado=1;
		}
		if(PORTB!=2){
			sumado=0;
		}
	}
	if(nMoscas==0){
		nMoscas=20;
	}
	
	
}