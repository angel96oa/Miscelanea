;*****************************************************************
;
;Ejercicio 2 - Practica 4  				Fecha: 05/03/2018
;Contar el numero de veces que se pulsa un botón

;******************************************************************			
			#include<p16F877a.inc>
			LIST P=16f877a 		; Seleccionamos el micro
__config _WDT_OFF & _HS_OSC & _LVP_OFF	; Deshabilitamos el watch dog y fijamos el oscilador

;******************************************************************
; Asignación de etiquetas a registros.
cont		EQU	0x20
;******************************************************************	
			ORG 0 					; El programa comienza en la dirección 0
			GOTO	INICIO 			; salta a la dirección 5 para sobrepasar el vector INT.
			ORG 5
;******************************************************************	
INICIO 		bcf		STATUS, RP0
			bcf		STATUS, RP1
			clrf	PORTB
			clrf	PORTD
			bsf 	STATUS, RP0 		; Selecciona banco 1 para llegar a TRISB
			movlw 	0x01
			movwf 	TRISB 				; Se especifica que es de entrada al poner 1 en TRISB
			movlw	0x00				; Se especifica que es de salida al poner 0 en TRISD
			movwf	TRISD
			bcf 	STATUS, RP0 		; Selección del banco 0 para trabajar con el puerto
			clrf	cont

BUCLE		btfss	PORTB, 0			;Comprueba si el pulsador esta activo, si no lo esta, sigue a la espera. Cuando lo está, va a la rutina ESPERA
			goto	BUCLE
			goto	ESPERA
			
ESPERA		btfsc	PORTB, 0			;Espera a que se suelte el pulsador y entonces limpia los puertos, suma 1 al contador, lo guarda en el puerto D y vuelve a BUCLE
			goto	ESPERA				;a la espera de nuevas pulsaciones.
			clrf	PORTD
			clrf	PORTB
			movlw	0x01
			addwf	cont, 1
			movf	cont, 0
			movwf	PORTD
			goto	BUCLE

		
FIN 		GOTO FIN			
			END