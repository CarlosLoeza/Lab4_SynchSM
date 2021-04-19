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
unsigned char prev; // keeps track of the last state of Pin A0 to see if it still being pressed
enum TurnOn {TurnOn_Start, TurnOn_PB0, TurnOn_PB0_Wait, TurnOn_PB1, TurnOn_PB1_Wait} TurnOn_State;

void Blink(){
    switch(TurnOn_State){
	case TurnOn_Start:
	    TurnOn_State = TurnOn_PB0;
	    break;
	case TurnOn_PB0:
	    if(tmpA){
            TurnOn_State = TurnOn_PB0_Wait;
            tmpB = 0x02;
	    }else if(!tmpA) {
		TurnOn_State = TurnOn_PB0;
	    }
	    break;
	case TurnOn_PB0_Wait:
	    if(tmpA){
		TurnOn_State = TurnOn_PB0_Wait;
	    } else if(!tmpA){
		TurnOn_State = TurnOn_PB1;
	    }
	    break;
	case TurnOn_PB1:
	    if(tmpA){
            TurnOn_State = TurnOn_PB1_Wait;
            tmpB = 0x01;
	    } else if (!tmpA){
		TurnOn_State = TurnOn_PB1;
	    }
	    break;
	case TurnOn_PB1_Wait:
	    if(tmpA){
		TurnOn_State = TurnOn_PB1_Wait;
	    } else if(!tmpA){
		TurnOn_State = TurnOn_PB0;
	    }
	    break;
	default:
	    TurnOn_State = TurnOn_Start;
	    break;
    }

    switch(TurnOn_State){
	case TurnOn_PB0:
	   tmpB = 0x01;
	   break;
	case TurnOn_PB1:
	   tmpB = 0x02;
	   break;
    }
    PORTB = tmpB;

}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    TurnOn_State = TurnOn_PB0;

    /* Insert your solution below */
    while (1) {
	tmpA = PINA & 0x01; 
	Blink();
    }

}

