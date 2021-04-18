

/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tmpA;
unsigned char count;
enum Count_States {Count_Start, Count_Wait, Count_Up, Count_Up_Wait, Count_Down, Count_Down_Wait, Count_Zero, Count_Reset} Count_State;

void Increment_Decrement(){

    switch(Count_State){
	case Count_Start:
	    Count_State = Count_Wait;
	    break;
	case Count_Wait:
	    if(tmpA == 0){
		Count_State = Count_Wait;
	    } else if(tmpA == 0x01){
		Count_State = Count_Up;
	    } else if(tmpA == 0x02){
		Count_State = Count_Down;
	    } else if(tmpA == 0x03){
		Count_State = Count_Zero;
	    }
	    break;
	case Count_Up:
	    if(tmpA == 0x01){
	        Count_State = Count_Up_Wait;
	    } else if (tmpA == 0x02){
	   	Count_State = Count_Down;
	    } else if(tmpA == 0x03){
		Count_State = Count_Zero;
	    } else if(tmpA == 0){
		Count_State = Count_Wait;
	    }
	    break;
	case Count_Up_Wait:
	    if(tmpA == 0){
		Count_State = Count_Wait;
	    }
	    else if(tmpA == 0x01){
		Count_State = Count_Up_Wait;
	    }else if (tmpA == 0x02){
		Count_State = Count_Down;
	    } else if (tmpA == 0x03){
		Count_State = Count_Zero;
	    } 
	    break;
	case Count_Down:
	    if(tmpA == 0x01){
	        Count_State = Count_Up;
	    } else if(tmpA == 0x02){
		Count_State = Count_Down_Wait;
  	    } else if(tmpA == 0x03){
		Count_State = Count_Zero;
	    } else if(tmpA == 0){
		Count_State = Count_Wait;
	    }
  	    break;
	case Count_Down_Wait:
	    if(tmpA ==0){
		Count_State = Count_Wait;
	    }
	    else if(tmpA == 0x01){ 
                Count_State = Count_Up;
            } else if (tmpA == 0x02){ 
                Count_State = Count_Down_Wait;
            } else if (tmpA == 0x03){ 
                Count_State = Count_Zero;
            }
	case Count_Zero:
	    if(tmpA == 0x03){
		Count_State = Count_Zero;
	    }
	    else if(tmpA == 0x01){
		Count_State = Count_Up;
	    } else if(tmpA ==0x02){
		Count_State = Count_Down;
	    }else if(tmpA == 0){
		Count_State = Count_Wait;
	    }
	    break;
	default:
	    Count_State = Count_State;
	    break;
    }

    switch(Count_State){
	case Count_Up:
	    if(count <9){
		++count;
	    }
	    break;
	case Count_Down:
	    if(count > 0){
		--count;
	    }
	    break;
   	case Count_Zero:
	    count = 0;
	    break;
    }

    PORTC = count;
}

int main(void)
{
    // PORTA: input   PORTC: output
    DDRA = 0x00; PORTA = 0xFF; 
    DDRC = 0xFF; PORTC = 0x00; 
    count = 7;
    
    Count_State = Count_Start; 
    while (1) 
    {
	tmpA = PINA & 0x03;
	Increment_Decrement();
    }
}
