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
unsigned char prev;
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
	    	tmpB = 0;
	    } 
	    break;
    }
    PORTB = tmpB;
/*	
	case Lock_Wait:
	    if(tmpA == 0x01 || tmpA == 0x02){
		Lock_State = Lock_Wait;
		prev = tmpA;
	    } else if(tmpA ==0x04 && prev ==0){
		Lock_State = Lock_Pound;
		prev = tmpA;
	    } 
	    break;
	case Lock_Pound:
	    if(tmpA == 0x04 || tmpA != 0x01 || tmpA != 0x02){
		Lock_State = Lock_Pound;
		prev = tmpA;
	    } else if (tmpA == 0x02){
		Lock_State = Lock_Y;
		prev = tmpA;
	    } else if(tmpA == 0x01 || tmpA == 0x00){
		Lock_State = Lock_Wait;
		prev = tmpA;
	    }
	    break;
	case Lock_Y:
	    if(tmpA == 0x00){
		Lock_State = Lock_Y;
		prev = tmpA;
	    }
	    else if(tmpA == 0x80){
		Lock_State = Lock_Inside;
		prev = tmpA;
	    }else {
		Lock_State = Lock_Wait;
		prev = tmpA;
	    }
	case Lock_Inside:
	    Lock_State = Lock_Wait;
	    break;
	default:
	    Lock_State = Lock_Wait;
	    break;
    }

    switch(Lock_State){
	case Lock_Pound:
	    tmpB = 0;
	case Lock_Y:
	    tmpB = 0x01;
	case Lock_Inside:
	    tmpB = 0;
    }
    PORTB = tmpB;*/
}

int main(void)
{
    // PORTA: input   PORTC: output
    DDRA = 0x00; PORTA = 0xFF; 
    DDRB = 0xFF; PORTB = 0x00; 
    tmpB = 0;
    prev = 0;
    Lock_State = Lock_Wait; 
    while (1) 
    {
	tmpA = PINA & 0xFF;
	Lock();
    }
}
