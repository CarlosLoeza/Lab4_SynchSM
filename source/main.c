

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
enum Lock_States {Lock_Start, Lock_Wait, Lock_Pound, Lock_Y, Lock_Inside} Lock_State;

void Lock(){
    switch(Lock_State){
	case Lock_Start:
	    Lock_State = Lock_Wait;
	    break;
	case Lock_Wait:
	    if(tmpA == 0x01 || tmpA == 0x02){
		Lock_State = Lock_Wait;
	    } else if(tmpA ==0x04){
		Lock_State = Lock_Pound;
	    } 
	    break;
	case Lock_Pound:
	    if(tmpA == 0x04 || tmpA != 0x01 || tmpA != 0x02){
		Lock_State = Lock_Pound;
	    } else if (tmpA == 0x02){
		Lock_State = Lock_Y;
	    } else if(tmpA == 0x01 || tmpA == 0x02){
		Lock_State = Lock_Wait;
	    }
	    break;
	case Lock_Y:
	    if(tmpA == 0x00){
		Lock_State = Lock_Y;
	    }
	    else if(tmpA == 0x80){
		Lock_State = Lock_Inside;
	    }else {
		Lock_State = Lock_Wait;
	    }
	case Lock_Inside:
	    
	default:
	    Lock_State = Lock_Wait;
	    break;
    }

    switch(Lock_State){
	case Lock_Pound:
	    tmpB = 0;
	case Lock_Y:
	    tmpB = 1;
	case Lock_Inside:
	    tmpB = 0;
    }

    PORTB = tmpB;
}

int main(void)
{
    // PORTA: input   PORTC: output
    DDRA = 0x00; PORTA = 0xFF; 
    DDRB = 0xFF; PORTB = 0x00; 
    tmpB = 0;
    Lock_State = Lock_Wait; 
    while (1) 
    {
	tmpA = PINA & 0x03;
	Lock();
    }
}
