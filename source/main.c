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
unsigned char tmpB;
unsigned char firstLoop;
enum Lock_States {Lock_Start, Lock_Wait, Lock_Pound, Lock_Pound_Held, Lock_Y, Lock_Y_Held, Lock_Inside} Lock_State;

void Lock(){
    switch(Lock_State){
	case Lock_Start:
	    Lock_State = Lock_Wait;
	    break;
	case Lock_Wait:
	    if(tmpA == 0x04){
 		Lock_State = Lock_Pound;
	    } else if(tmpA == 0x01 || tmpA == 0x02){
		Lock_State = Lock_Wait;
	    }
	    break;
	case Lock_Pound:
	    if (tmpA == 0x04){ 
                Lock_State = Lock_Pound_Held;  
            } else if(tmpA == 0x02){
		Lock_State = Lock_Y;
	    } else if (tmpA == 0x00){
		Lock_State = Lock_Pound;
	    } else{
		Lock_State = Lock_Wait;
	    }
	    break;
	case Lock_Pound_Held:
	    if(tmpA == 0x04){
		Lock_State = Lock_Pound_Held;
	    } else if(tmpA == 0){
		Lock_State = Lock_Y;
	    }
	case Lock_Y:
	    if(tmpA == 0){
		Lock_State = Lock_Y;
 	    }
	    else if(tmpA == 0x01 || tmpA == 0x04){
		Lock_State = Lock_Wait;
	    }
	    else if (tmpA == 0x02){
		Lock_State = Lock_Y_Held;
	    } 
	    break;
	case Lock_Y_Held:
	    if(tmpA == 0){
		Lock_State = Lock_Inside;
	    } else if(tmpA == 0x02){
		Lock_State = Lock_Y_Held;
	    }
	    break;
	case Lock_Inside:
	    if(tmpA == 0){
		Lock_State = Lock_Wait;
	    }
    }

    switch(Lock_State){
	case Lock_Wait:
	    tmpB = 0;
	    break;
	case Lock_Pound:
	    tmpB = 0;
	    break;
	case Lock_Y:
	    tmpB = 1;
	    break;
	case Lock_Inside:
	    if(tmpA == 0x80){
	    	if(tmpB == 0 && firstLoop){
		    tmpB = 0;
	 	} else if(tmpB ==0 && !firstLoop){
		    tmpB = 1;
		} 
		else if(tmpB == 1) {
		    tmpB = 0;
		}
	    } 
	    break;
    }
    PORTB = tmpB;
}

int main(void)
{
    // PORTA: input   PORTC: output
    DDRA = 0x00; PORTA = 0xFF; 
    DDRB = 0xFF; PORTB = 0x00; 
    tmpB = 0;
    firstLoop = 1;
    Lock_State = Lock_Wait; 
    while (1) 
    {
	tmpA = PINA & 0xFF;
	Lock();
    }
}
