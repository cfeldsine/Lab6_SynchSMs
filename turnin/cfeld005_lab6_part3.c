/*	Author: cfeld005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum states {init, press1, press2, hold1, hold2, wait, reset} state;
    
unsigned char tmpB = 0x07;
unsigned char hold = 0;

void TickFct(unsigned char tmpA){
	switch(state){
	    case init:
		if (!tmpA){
		    state = wait;
		} else if (tmpA == 0x01) {
		    state = press1;
		} else if (tmpA == 0x02) {
		    state = press2;
		} else {
		    state = reset;
		}
		break;
	    case press1:
                if (!tmpA){ 
                    state = wait; 
                } else if (tmpA == 0x01) {
                    state = hold1;
                } else if (tmpA == 0x02) {
                    state = press2;
                } else {
                    state = reset;
                }
		break;
	    case hold1:
		if (!tmpA){
		    state = wait;
		} else if (tmpA == 0x01) {
		    if (hold >= 10){
		    	state = press1;
		    } else {
		    	state = hold1;
		    }
		} else if (tmpA == 0x02) {
			state = press2;
		} else {
		    state = reset;
		}
		break;
	    case press2:
                if (!tmpA){ 
                    state = wait; 
                } else if (tmpA == 0x01) {
                    state = press1;
                } else if (tmpA == 0x02) {
                    state = hold2;
                } else {
                    state = reset;
                }
		break;
            case hold2:
                if (!tmpA){
                    state = wait;
                } else if (tmpA == 0x01) {
                    state = press1;
                } else if (tmpA == 0x02) {
		    if (hold >= 10){
		    	state = press2;
		    } else{
                    	state = hold2;
		    }
                } else {
                    state = reset;
                }
                break;
            case wait:
                if (!tmpA){ 
                    state = wait; 
                } else if (tmpA == 0x01) {
                    state = press1;
                } else if (tmpA == 0x02) {
                    state = press2;
                } else {
                    state = reset;
                }
                break;
            case reset:
                if (!tmpA){ 
                    state = wait; 
                } else if (tmpA == 0x01) {
                    state = press1;
                } else if (tmpA == 0x02) {
                    state = press2;
                } else {
                    state = reset;
                }
                break;
	    default:
		state = reset;
		break;
	}
	
	switch(state){
	    case press1:
		if (tmpB < 9){
		    tmpB += 1;
		}
		hold = 0;
		break;
	    case press2:
		if (tmpB > 0){
		    tmpB -= 1;
		}
		hold = 0;
		break;
	    case hold1:
		hold++;
		break;
	    case hold2:
		hold++;
		break;
	    case reset:
		tmpB = 0x00;
		break;
	    default:
		break;
	}
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    TimerSet(100);
    TimerOn();

    unsigned char tmpA = 0x00;
    state = init;
    while (1) {
	tmpA = ~PINA;
	TickFct(tmpA);
	PORTB = tmpB;

        while (!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

