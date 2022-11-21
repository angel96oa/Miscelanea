;*****************************************************************

;Ejercicio 1 - Practica 1  				Fecha: 06/02/2018
;Escribir un programa en lenguaje ensamblador para la MCU 
;16F877A que sume dos números de 16 bits almacenados en memoria 
;y almacene el resultado también en memoria.
;******************************************************************
			#include<p16F877a.inc>
			LIST	p=16f877a ;PIC
;******************************************************************

;Variables
var1a		EQU	0x20
var1b		EQU	0x21
var2a		EQU	0x22
var2b		EQU	0x23
resultadoa	EQU	0x24
resultadob	EQU	0x25
signo		EQU	0x26
acarreo		EQU 0x27
			
;******************************************************************
			ORG	0
;******************************************************************
INICIO		movlw	0x01		;Carga el valor 0x01 en w
			movwf	var1a		;Guarda el valor de w en la dirección var1
			movlw	0x02		;Carga el valor 0x02 en w
			movwf	var2a		;Guarda el valor de w en la dirección var2
			movf	var1a,0		;Guarda el valor que se encuentra en la posición de memoria var1 en w
			subwf	var2a,0		;Suma en w el contenido de w y lo que se encuentra en la dirección var2
			movwf 	resultadoa	;Guarda el contenido de w en resultado
			movlw	0x0F
			btfss 	STATUS,C
			movwf	acarreo
				

			movlw	0xFF		;Carga el valor 0x01 en w
			movwf	var1b		;Guarda el valor de w en la dirección var1
			movlw	0x04		;Carga el valor 0x02 en w
			movwf	var2b		;Guarda el valor de w en la dirección var2
			movf	var1b,0		;Guarda el valor que se encuentra en la posición de memoria var1 en w
			subwf	var2b,0		;Suma en w el contenido de w y lo que se encuentra en la dirección var2
			movwf 	resultadob	;Guarda el contenido de w en resultado
			
			movlw	0x0F
			btfss 	STATUS,C
			movwf	signo
	
			movf	acarreo,0		;Guarda el valor que se encuentra en la posición de memoria var1 en w
			addwf	resultadob,0	;Suma en w el contenido de w y lo que se encuentra en la dirección var2
			
			movf	signo,0
			btfss 	STATUS,C
			addlw	0x0F
			movwf	signo
				
			
			return
			END			;Fin del programa