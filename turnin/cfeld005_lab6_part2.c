/*	Author: Cote Feldsine
 *  Partner(s) Name: 
 *	Lab Section:023
 *	Assignment: Lab #6  Exercise #1
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


enum states {L1, L2, L3, L4, press, wait} state;
unsigned char tmpB;


void TickFct_LightGame(unsigned char tmpA, unsigned char timeCount){
	switch (state){
		case L1:
			if (tmpA){
				state = press;
			} else if (timeCount == 3) {
				state = L2;
			}
			break;
		case L2:
                        if (tmpA){
                                state = press;
                        } else if (timeCount == 3){
                                state = L3;
                        }
                        break;
		case L3:
                        if (tmpA){
                                state = press;
                        } else if (timeCount == 3){
                                state = L4;
                        }
                        break;
		case L4:
                        if (tmpA){
                                state = press;
                        } else if (timeCount == 3) {
                                state = L1;
                        }
                        break;
		case press:
			if (!tmpA){
				state = wait;
			}
			break;
		case wait:
			if (tmpA){
				state = L1;
			}
	}
	switch (state){
		case L1:
			tmpB = 0x01;
			break;
		case L2:
			tmpB = 0x02;
			break;
		case L3:
			tmpB = 0x04;
			break;
		case L4:
			tmpB = 0x02;
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
	state = L1;
	unsigned char tmpA, timeCount = 0x00;
	while(1) {
		timeCount++;
		tmpA = ~PINA;
		TickFct_LightGame(tmpA, timeCount);
		PORTB = tmpB;

		if (timeCount >= 3){
			timeCount = 0;
		}
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
