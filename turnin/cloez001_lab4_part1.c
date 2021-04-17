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
enum TurnOn {TurnOn_Start, TurnOn_PB0, TurnOn_PB1} TurnOn_State;

void Blink(){
    switch(TurnOn_State){
	case TurnOn_Start:
	    TurnOn_State = TurnOn_PB0;
	    break;
	case TurnOn_PB0:
	    if(tmpA && prev == 0){
		TurnOn_State = TurnOn_PB1;
		prev = tmpA;
	    }else{
		TurnOn_State = TurnOn_PB0;
		prev = tmpA;
	    }
	    break;
	case TurnOn_PB1:
	    if(tmpA && prev == 0){
		TurnOn_State = TurnOn_PB0;
	    } else {
		TurnOn_State = TurnOn_PB1;
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

    TurnOn_State = TurnOn_Start;

    /* Insert your solution below */
    while (1) {
	tmpA = PINA & 0x01; 
        prev = 0;
	Blink();
    }

}
