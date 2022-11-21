;*****************************************************************
;
;Ejercicio 3 - Practica 3  				Fecha: 26/03/2018
;Encender leds de PORTA cuando se pulsen botones de PORTB

;******************************************************************			
			#include<p16F877a.inc>
			LIST P=16f877a 					; Seleccionamos el micro
__config _WDT_OFF & _HS_OSC & _LVP_OFF & _BOREN_OFF		; Deshabilitamos el watch dog y fijamos el oscilador

;******************************************************************
			ORG 0 							; El programa comienza en la dirección 0
			GOTO	INICIO 					; salta a la dirección 5 para sobrepasar el vector INT.
			ORG 5
;******************************************************************
INICIO		bcf		STATUS, RP0				; inicializo PORTA
			bcf		STATUS, RP1
			clrf 	PORTA					
			clrf	PORTB
			bsf		STATUS, RP0
			movlw	0x06
			movwf	ADCON1					
			movlw	0x00					
			movwf	TRISA					; TRISA es de salida
			movlw	0xff					
			movwf	TRISB					; TRISB es de entrada
			bcf 	STATUS, RP0				; Selección del banco 0 para trabajar con el puerto
			bcf		PORTA, 6				; Se apagan el bit 6 y el 7 del puerto A
			bcf		PORTA, 7


BUCLE 		btfsc	PORTB,0					;Se comprueba el estado del boton del puerto B y se enciende el led del puerto A correspondiente
			bsf		PORTA,0
			btfss	PORTB,0
			bcf		PORTA,0
			
			btfsc	PORTB,1
			bsf		PORTA,1
			btfss	PORTB,1
			bcf		PORTA,1
			
			btfsc	PORTB,2
			bsf		PORTA,2
			btfss	PORTB,2
			bcf		PORTA,2
			
			btfsc	PORTB,3
			bsf		PORTA,3
			btfss	PORTB,3
			bcf		PORTA,3
			
			btfsc	PORTB,4
			bsf		PORTA,4
			btfss	PORTB,4
			bcf		PORTA,4
			
			btfsc	PORTB,4
			bsf		PORTA,4
			btfss	PORTB,4
			bcf		PORTA,4

			btfsc	PORTB,5
			bsf		PORTA,5
			btfss	PORTB,5
			bcf		PORTA,5

			
			goto	BUCLE
						
		
FIN 		GOTO FIN			
			END