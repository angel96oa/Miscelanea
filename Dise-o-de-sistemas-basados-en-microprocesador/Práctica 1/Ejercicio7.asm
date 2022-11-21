;*****************************************************************
;
;Ejercicio 7 - Practica 1  				Fecha: 21/02/2018
;Rutina de retardo
;Alumnos Grupo 1:
;- Pablo Olivas Auñón
;-
;-
;******************************************************************
			#include<p16F877a.inc>
			LIST	p=16f877a ;PIC
;******************************************************************

;Variables
b1		EQU	0x20				;Cada variable esta para que el bucle se ejecute el número de veces necesaria.
b2		EQU	0x21
b3		EQU	0x22
b4		EQU	0x23

;******************************************************************
			ORG	0
;******************************************************************
INICIO		movlw	0xfa		;W	
			movwf	b4						
			goto	BUCLE4		;El bucle encargado de dar W vueltas a la rutina que tarda 1ms

;--------------------------------
;Como tenemos una frecuencia de reloj de 20MHz significa que se ejcutan 20x10^6 instrucciones de 1 ciclo por segundo, 20.000 instrucciones por ms.
;Por ello, podemos pasar por w un valor que ira de 0 a 250, donde cada valor nos indicara el número de ms que durará la rutina de retardo, 
;siendo la operación para pasar de W a ms la siguiente: ms=Wx4. De esta forma, podemos hacer un bucle que de W vueltas a una rutina que tarde 4ms por dicho incremento, 
;teniendo de esta forma una rutina que tarde Wms, siendo el incremento de 4 en 4 ms. 
;
;La rutina que tarda en 4ms se puede obtenerse haciendo un bucle que ejecute 250 veces otro que a su vez ejecute 80 veces otro que ejecute 4 instrucciones.
;Tras ajustar esto para las instrucciones que ocupa cada bucle, queda de la forma expresada abajo

			
BUCLE4		movlw	0x3e		;Este bucle dará W vueltas
			movwf	b3			;BUCLE3 ejecutará 250 ciclos, pero como tiene 5 instrucciones de 1 ciclo, tendremos que ejecutarlo 250/5=50 veces
			decfsz	b4,1
			goto	BUCLE3
			goto	FIN	
			
BUCLE3		nop					
			movlw	0x14		;BUCLE2 ejecutará 80 ciclos, pero como tiene 4 instrucciones, tendrmeos que ejecutarlo 80/4=20 veces
			movwf	b2
			decfsz	b3,1
			goto	BUCLE2
			goto	BUCLE4
			
BUCLE2		movlw	0x02		;BUCLE1 ejecutará 4 ciclos, pero como tiene 2 instrucciones, tendremos que ejecutarlo 4/2=2 veces
			movwf	b1
			decfsz	b2,1
			goto	BUCLE1
			goto	BUCLE3
			
BUCLE1		decfsz	b1,1
			goto	BUCLE1
			goto	BUCLE2

			
FIN			goto	FIN
			END			;Fin del programa