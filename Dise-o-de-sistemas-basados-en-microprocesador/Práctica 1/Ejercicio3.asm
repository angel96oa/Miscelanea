;*****************************************************************

;Ejercicio 1 - Practica 1  				Fecha: 06/02/2018
;Escribir un programa en lenguaje ensamblador para la MCU 
;16F877A que sume dos números de 16 bits almacenados en memoria 
;y almacene el resultado también en memoria.
;Practica X - Ejercicio Y
;
;Alumnos Grupo Z:
;-
;-
;******************************************************************
			#include<p16F877a.inc>
			LIST	p=16f877a ;PIC
;******************************************************************

;Variables
RESUL		EQU	0x20
var1		EQU	0x21
var2		EQU	0x22
cv1			EQU	0x23	
cv2			EQU	0x24
;cont		EQU	0x23

			
;******************************************************************
			ORG	0
;******************************************************************
INICIO		movlw	0x15		;Carga el valor 0x01 en w
			movwf	var1		;Guarda el valor de w en la dirección var1
			movwf	cv1
			movlw	0x27		;Carga el valor 0x02 en w
			movwf	var2		;Guarda el valor de w en la dirección var2
			movwf	cv2
			
BUCLE		btfsc	var1,7
			goto	COMPB
			btfsc	var2,7
			goto	BMAYOR
			goto	DESP
			
COMPB		btfsc	var2,7
			goto	DESP
			movf	cv1,0
			movwf	RESUL
			goto	FIN
			
DESP		rlf		var1,1
			rlf		var2,1
			goto	BUCLE
			goto	IGUALES

BMAYOR		movf	cv2,0
			movwf	RESUL
			goto	FIN			

IGUALES		movlw	0x00		
			movwf	RESUL			
			
FIN			goto	FIN
			END			;Fin del programa