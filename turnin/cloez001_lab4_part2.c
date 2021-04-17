
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
unsigned char hold;

enum Increment_States {Increment_SMState, Increment_Up, Increment_Minus, Increment_Reset, Increment_Hold} Increment_State;


void Increment_Decrement(){

    switch(Increment_State){
	case Increment_SMState:
	    if(tmpA == 0x03 ){
 		Increment_State = Increment_Reset;
	    }
  	    else if(tmpA == 0x02 && count != 0){
		Increment_State = Increment_Minus;
	    }
	    else if(tmpA == 0x01 && count != 9){
		Increment_State = Increment_Up;
	    }
	    else if(tmpA == 0x00){
		Increment_State = Increment_Hold;
            }
	    break;
	case Increment_Up:
	    count++;
	    Increment_State = Increment_Hold;
	    hold = 1;
	    break;
	case Increment_Minus:
	    count--;
	    Increment_State = Increment_Hold;
	    hold = 1;
	    break;
	case Increment_Reset:
	    count = 0;
	    Increment_State = Increment_Hold;
	    break;
	case Increment_Hold:
	    if(tmpA == 0x00){
		Increment_State = Increment_SMState;
	    }
	    else if(tmpA == 0x03){
		Increment_State = Increment_Reset;
	    }
	    break;
	default:
	    Increment_State = Increment_SMState;
	    break;
    }

    PORTC = count;
}

int main(void)
{
    // PORTA: input   PORTC: output
    DDRA = 0x00; PORTA = 0xFF; 
    DDRC = 0xFF; PORTC = 0x07; 
    count = 7;

    while (1) 
    {
	tmpA = PINA & 0x03;
	Increment_Decrement();
    }
}
