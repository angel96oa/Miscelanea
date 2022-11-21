;*****************************************************************
;
;Ejercicio 1 - Practica 2  				Fecha: 05/03/2018
;Encender leds de PORTB cuando se pulsen botones de PORTA

;******************************************************************			
			#include<p16F877a.inc>
			LIST P=16f877a 		; Seleccionamos el micro
__config _WDT_OFF & _HS_OSC & _LVP_OFF	; Deshabilitamos el watch dog y fijamos el oscilador

;******************************************************************
			ORG 0 					; El programa comienza en la dirección 0
			GOTO	INICIO 			; salta a la dirección 5 para sobrepasar el vector INT.
			ORG 5
;******************************************************************
INICIO		bcf		STATUS, RP0
			bcf		STATUS, RP1
			clrf	PORTB
			bsf 	STATUS, RP0  		; Selecciona banco 1 para llegar a TRISB
			movlw 	0x00
			movwf 	TRISB 				; Y se especifica que es de salida al poner 0 en TRISB
			movlw	0x06
			movwf	ADCON1
			movlw	0xcf
			movwf	TRISA
			bcf 	STATUS, RP0 		; Selección del banco 0 para trabajar con el puerto
			bcf		PORTB, 6			; Se apagan el bit 6 y el 7 del puerto B
			bcf		PORTB, 7
			

BUCLE 		btfsc	PORTA, 0				;Se comprueba el estado del boton del puerto A y se enciende el led del puerto B correspondiente
			bsf		PORTB, 0
			btfss	PORTA, 0
			bcf		PORTB, 0
			
			btfsc	PORTA, 1
			bsf		PORTB, 1
			btfss	PORTA, 1
			bcf		PORTB, 1
			
			btfsc	PORTA, 2
			bsf		PORTB, 2
			btfss	PORTA, 2
			bcf		PORTB, 2
			
			btfsc	PORTA, 3
			bsf		PORTB, 3
			btfss	PORTA, 3
			bcf		PORTB, 3
			
			btfsc	PORTA, 4
			bsf		PORTB, 4
			btfss	PORTA, 4
			bcf		PORTB, 4
			
			btfsc	PORTA, 5
			bsf		PORTB, 5
			btfss	PORTA, 5
			bcf		PORTB, 5
			goto	BUCLE

						
		
FIN 		GOTO FIN			
			END