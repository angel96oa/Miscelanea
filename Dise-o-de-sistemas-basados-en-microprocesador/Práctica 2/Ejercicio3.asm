;*****************************************************************
;
;Ejercicio 2 - Practica 3  				Fecha: 05/03/2018
;Los leds se encienden dando sensación de movimiento en PORTB y PORTD


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
rotb		EQU	0x24
rotd		EQU	0x25
contb		EQU	0x26
contd		EQU	0x27
bot			EQU	0x28
;******************************************************************	
			ORG 0 					; El programa comienza en la dirección 0
			GOTO	INICIO 			; salta a la dirección 5 para sobrepasar el vector INT.
			ORG 5
;******************************************************************	
INICIO 		bcf		STATUS, RP0
			bcf		STATUS, RP1
			clrf	PORTB
			clrf	PORTC
			clrf	PORTD
			bsf 	STATUS, RP0 		; Selecciona banco 1 para llegar a TRISB
			movlw 	0x00
			movwf 	TRISB 				; Y se especifica que son de salida al poner 0 en TRISB, TRISC y TRISD
			movwf	TRISC
			movwf	TRISD
			bcf 	STATUS, RP0 		; Selección del banco 0 para trabajar con el puerto
			movlw	0x7d				; Valor de W para la rutina de retardo
			movwf	b4
			movlw	0x01				; Se inicializan los rotadores para que empiecen en su lugar correspondiente
			movwf	rotb
			movlw	0x80
			movwf	rotd		
			movlw	0x08				; Se inicializan los contadores a 8 para controlar los rotadores
			movwf	contb
			movwf	contd
			movlw	0x00
			movwf	bot
			goto	BUCLEB


BUCLEB		movf	rotb,0				; Bucle que rota el bit en el puerto B. Ponemos el valor de rotb a puerto B a traves de W
			clrf	PORTB		
			movwf	PORTB
			rlf		rotb,1				; Rota el bit de rotb hacia la izquierda
			call	BUCLE4				; Va a la rutina de retardo
			clrf	PORTB				
			call	LECTURA				; Se va a la rutina LECTURA a comprobar si esta pulsado el botóm, si lo esta, la variable bot será 1
			btfsc	bot, 0				; Se comprueba si la variable bot es 0, si no lo es se finaliza el programa
			goto	FIN
			clrf	PORTB
			decfsz	contb,1				; Se decrementa el contador para ver si se han encendido los 8 leds, si lo han hecho, se procede a encender los de los otros puertos
			goto	BUCLEB
			goto	RESETB

BUCLED		movf	rotd,0				; Bucle que rota el bit en el puerto D. Ponemos el valor de rotd a puerto D a traves de W
			clrf	PORTD
			movwf	PORTD
			rrf		rotd,1				; Rota el bit de rotd hacia la derecha
			call	BUCLE4				; Va a la rutina de retardo
			clrf	PORTD
			call	LECTURA				; Se va a la rutina LECTURA a comprobar si esta pulsado el botóm, si lo esta, la variable bot será 1
			btfsc	bot, 0					; Se comprueba si la variable bot es 0, si no lo es se finaliza el programa
			goto	FIN
			clrf	PORTD
			decfsz	contd,1				; Se decrementa el contador para ver si se han encendido los 8 leds, si lo han hecho, se procede a encender los de los otros puertos
			goto	BUCLED
			goto	RESETD
			
RESETB		bcf		STATUS, 0			; Rutina que prepara el puerto D para que se enciendan los leds correctamente.
			movlw	0x08
			movwf	contd
			movlw	0x80
			movwf	rotd
			bsf		PORTC,7
			call	BUCLE4
			bcf		PORTC,7
			goto	BUCLED

RESETD		bcf		STATUS, 0			; Rutina que prepara el puerto B para que se enciendan los leds correctamente.
			movlw	0x08
			movwf	contb
			movlw	0x01
			movwf	rotb
			bsf		PORTC,0
			call	BUCLE4
			bcf		PORTC,0
			goto	BUCLEB
			
LECTURA		bsf 	STATUS, RP0
			movlw 	0x01
			movwf 	TRISB
			bcf 	STATUS, RP0
			btfsc	PORTB,0
			goto	BOTON
			bsf 	STATUS, RP0
			movlw 	0x00
			movwf 	TRISB
			bcf 	STATUS, RP0
			return
			
BOTON		bsf 	STATUS, RP0
			movlw 	0x00
			movwf 	TRISB
			bcf 	STATUS, RP0
			movlw	0xff
			movwf	PORTB
			movwf	PORTD
			bsf		PORTC,0
			bsf		PORTC,7
			movlw	0x01
			movwf	bot
			return

		
			
;RUTINA DE RETARDO
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
		
FIN 		GOTO FIN			
			END