;*****************************************************************
;
;Ejercicio 2 - Practica 2  				Fecha: 05/03/2018
;Los leds se encienden dando sensación de movimiento en PORTB


;******************************************************************			
			#include<p16F877a.inc>
			LIST P=16f877a 		; Seleccionamos el micro
__config _WDT_OFF & _HS_OSC & _LVP_OFF	; Deshabilitamos el watch dog y fijamos el oscilador

;******************************************************************
; Asignación de etiquetas a registros.		
b1			EQU	0x20				;Cada variable esta para que el bucle se ejecute el número de veces necesaria.
b2			EQU	0x21
b3			EQU	0x22
b4			EQU	0x23
rot			EQU	0x24
;******************************************************************	
			ORG 0 					; El programa comienza en la dirección 0
			GOTO	INICIO 			; salta a la dirección 5 para sobrepasar el vector INT.
			ORG 5
;******************************************************************
INICIO 		bcf		STATUS, RP0
			bcf		STATUS, RP1
			clrf	PORTB
			bsf 	STATUS, RP0 		; Selecciona banco 1 para llegar a TRISB
			movlw 	0x00
			movwf 	TRISB 				; Y se especifica que es de salida al poner 0 en TRISB
			bcf 	STATUS, RP0 		; Selección del banco 0 para trabajar con el puerto
			movlw	0x1f				; Valor de W para la rutina de retardo	
			movwf	b4
			movlw	0x01
			movwf	rot					; Se inicializa el valor del registro que va a rotar para el efecto de movimiento de los leds
			goto	BUCLE


BUCLE		movf	rot,0				; Movemos rot a W para posteriormente pasarlo a PORTB, que muestra la salida (leds)
			movwf	PORTB
			rlf		rot,1				; Rota el bit
			call	BUCLE4				; Se va a la rutina de retardo
			clrf	PORTB				; Se apagan todos los leds para encender el siguiente
			goto	BUCLE


;******************************************************************			
;RUTINA DE RETARDO
;******************************************************************
BUCLE4		movlw	0x3e		;Este bucle dará W vueltas
			movwf	b3			;BUCLE3 ejecutará 250 ciclos, pero como tiene 5 instrucciones de 1 ciclo, tendremos que ejecutarlo 250/5=50 veces
			decfsz	b4,1
			goto	BUCLE3
			movlw	0x1f				;W	
			movwf	b4
			return
			
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
;FIN RUTINA				
;******************************************************************	
FIN 		GOTO FIN			
			END