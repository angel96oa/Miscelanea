#include <16f877a.h>

#USE DELAY (CLOCK=8M)
#FUSES NOWDT, HS, NOLVP

#BYTE portb=0x6
#BIT portb7=portb.7
#BIT trisb7=0x86.7


main(){
	trisb7=0;
	portb=0;
	portb7=1;
	while(1);
}