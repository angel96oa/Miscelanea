;*****************************************************************
;
;Ejercicio 6 - Practica 1  				Fecha: 06/02/2018
;Escribir un programa que separe en centenas, decimas y unidades un numero dado

;******************************************************************
			#include<p16F877a.inc>
			LIST	p=16f877a ;PIC
;******************************************************************

;Variables
binario		EQU	0x20
unidades	EQU	0x21
decena		EQU	0x22
centenas	EQU	0x23
resultadoa	EQU	0x24
var1		EQU	0x25
var2		EQU	0x26
cont		EQU	0x27
cv1			EQU	0x28	
cv2			EQU	0x29
resul		EQU	0x30
cociente	EQU 0x31
resto		EQU 0x32


;******************************************************************
			ORG	0
;******************************************************************
INICIO		movlw	0x02		;Carga el valor 0x01 en w
			movwf	var1
			movwf	cv1
			movlw	0x02		;Carga el valor 0x02 en w
			movwf	var2
			movwf	cv2			
			movlw 	0x00
			movwf	resultadoa
			movlw	82
			movwf	binario
			
			
DIVI		movlw	0x00				;cociente vale 0
			movwf	cociente
			movf	var1,0				;al resto le restaremos el valor del divisor en cada iteracion
			movwf	resto
DIVI2		incf	cociente, 0
			subwf	resto, divisor
			goto	BUCLE
			goto	DIVI2
				
MULT		movf	var1,0
			addwf	resultadoa,0
			movwf	resultadoa
			decfsz	var2,1
			goto	MULT
			goto 	FIN
			
;COMPARADOR
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
			movwf	resul
;FIN COMPARADOR


			
FIN			goto	FIN
			END			;Fin del programa