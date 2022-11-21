;*****************************************************************
;
;Ejercicio 4 - Practica 3  				Fecha: 26/03/2018
;

;******************************************************************			
			#include<p16F877a.inc>
			LIST P=16f877a 					; Seleccionamos el micro
__config _WDT_OFF & _HS_OSC & _LVP_OFF		; Deshabilitamos el watch dog y fijamos el oscilador

;******************************************************************

;Variables auxiliares
binario		EQU	0x20
centenas	EQU	0x21
decenas		EQU	0x22
unidades	EQU	0x23
resto		EQU	0x24
var1		EQU	0x25
var2		EQU	0x26
cont		EQU	0x27
cv1			EQU	0x28	
cv2			EQU	0x29
resul		EQU	0x2a
divisor		EQU	0x2b
;******************************************************************
			ORG 0 							; El programa comienza en la dirección 0
			GOTO	INICIO 					; salta a la dirección 5 para sobrepasar el vector INT.
			ORG 5
;******************************************************************
INICIO		bcf		STATUS, RP0				; inicializo PORTA
			bcf		STATUS, RP1
			clrf 	PORTA					
			clrf	PORTB
			clrf	PORTC
			clrf	PORTD
			bsf		STATUS, RP0
			movlw	0x06
			movwf	ADCON1					
			movlw	0x00					
			movwf	TRISA					; TRISA es de salida
			movwf	TRISB
			movwf	TRISC
			movlw	0xff					
			movwf	TRISD					; TRISB es de entrada
			bcf 	STATUS, RP0				; Selección del banco 0 para trabajar con el puerto
			
ACTUAL		movf	PORTD,0
			movwf	binario
			call 	CONVERSOR
			goto	ACTUAL
			

			
CONVERSOR	movlw	0x00			;Se inicializan las variables a 0
			movwf	unidades
			movwf	decenas
			movwf	centenas
			movwf	resto

			movlw	0x64			;Primero almacenamos un 100 decimal en la variable divisor, para saber cuantas centenas hay en nuestro número binario
			movwf	divisor
			call	DIVI			;Dividimos binario/100, en binario se nos queda en resultado
			movf	resto,0			;Guardamos el resto de la división (resto) en centenas
			movwf	centenas
			
			movlw	0x00			;inicializamos resto a 0 para que la división funcione correctamente
			movwf	resto
			movlw	0xa				;Se almacena en divisor un 10 decimal, para saber las decenas
			movwf	divisor
			call	DIVI			;Dividimos binario/10, en binario se nos queda el resultado
			movf	resto,0			;En el resto se nos queda el número de decenas
			movwf	decenas
			
			movf	binario,0		;En binario solo quedan el número de unidades, por lo que guardamos los que hay en binario en la varibale unidades
			movwf	unidades
			
			movf	centenas,0
			movwf	PORTA
			movf	decenas,0
			movwf	PORTB
			movf	unidades,0
			movwf	PORTC
			
			return
			
;---------------------------------------------------------------------------------------------------------------------------------------------------			
;COMPARADOR	 --	var1 y cv1 deben ser el dividendo  --  var2 y cv2 deben ser el divisor
;***************************************************************************************************************************************************
;En el comparador, se comparará bit a bit, siempre mirando de mayor a menor peso si dos números son iguales.
;Aquel número que primero tenga un bit a 1, será el mayor. Si al mirar los 8 bits, no se encuentra que ninguno se mayor, son iguales.
;En este caso, para realizar la división corectamente, si var1(dividendo) es mayor o si son iguales, se devuelve 0 en la variable resul.
;Si var2(divisor) es mayor, se devuelve 1 en al variable resul
;***************************************************************************************************************************************************
BUCLE		btfsc	var1,7			
			goto	COMPB
			btfsc	var2,7
			goto	BMAYOR
			goto	DESP
			
COMPB		btfsc	var2,7
			goto	DESP
			movlw	0x00			;cv1 mayor
			movwf	resul
			goto	DIVIB
			
DESP		rlf		var1,1
			rlf		var2,1
			decfsz	cont,1
			goto	BUCLE
			goto	IGUALES

BMAYOR		movlw	0x01			;cv2 mayor
			movwf	resul
			goto	DIVIB		

IGUALES		movlw	0x00		
			movwf	resul
			goto	DIVIB
;FIN COMPARADOR
;---------------------------------------------------------------------------------------------------------------------------------------------------


;---------------------------------------------------------------------------------------------------------------------------------------------------
;DIVISION
;***************************************************************************************************************************************************
;La división utiliza el comparador para ir restando al dividendo (binario) el divisor(divisor) mientras que dividendo>=divisor.
;El resultado de la división se va quedando en resto, mientras que el resto se quedará en la variable binario.
;***************************************************************************************************************************************************
DIVI		movf	binario,0		
			movwf	var1
			movwf	cv1
			movf	divisor,0		
			movwf	var2
			movwf	cv2
			movlw	0x07
			movwf	cont
			goto 	BUCLE

DIVIB		btfsc	resul,0
			goto	FINDIV
			movf	divisor,0
			subwf	binario,1
			movlw	0x01
			addwf	resto,1
			goto	DIVI
			
FINDIV
			return
		
FIN 		GOTO FIN			
			END