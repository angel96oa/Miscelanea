;*****************************************************************
;
;Ejercicio 5 - Practica 1  				Fecha: 28/02/2018
;Multiplicación de dos números
;Alumnos Grupo 1:

;******************************************************************
			#include<p16F877a.inc>
			LIST	p=16f877a ;PIC
;******************************************************************

;Variables
var1		EQU	0x20
var2		EQU	0x21
cont		EQU	0x22
resultadoa	EQU	0x23
resultadob	EQU	0x24
acarreo		EQU 0x25
			
;******************************************************************
			ORG	0
;******************************************************************
INICIO		movlw	0xff		
			movwf	var1		
			movlw	0xff		
			movwf	var2		
			movlw 	0x00
			movwf	resultadoa
			movlw	0x00
			movwf	resultadob
			
			goto MULT
				
MULT		movf	var1,0
			addwf	resultadoa,0
			movwf	resultadoa
			movlw	0x01
			btfsc 	STATUS,C
			addwf	resultadob,1
			decfsz	var2,1
			goto	MULT
			goto	FIN

			
FIN			goto	FIN
			END			;Fin del programa
