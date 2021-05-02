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


enum states {L1, L2, L3} state;
unsigned char tmpB;


void TickFct_ThreeLEDs(){
	switch (state){
		case L1:
			state = L2;
			break;
		case L2:
			state = L3;
			break;
		case L3:
			state = L1;
			break;
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
	}
}

int main(void) {
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	state = L1;
	while(1) {
		TickFct_ThreeLEDs();
		PORTB = tmpB;
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
