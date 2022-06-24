/*
 * piezo.c
 *
 * Created: 2022-06-24 오전 10:11:04
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


unsigned int DoReMi[4] = {523, 659, 783, 1046};

void piezo_init(){
	DDRE = 0x08;
	TCCR3A = 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	EICRB = 0xFF;
	EIMSK = 0xF0;
	EIFR = 0xF0;
}
void open_sound(){
	for(int i=0; i<4; i++){
		ICR3 = 7372800/DoReMi[i]/2;
		TCCR3A = 0x40;
		_delay_ms(200);
		TCCR3A = 0x00;
	}
}

void close_sound(){
	for(int i=3; i>-1; i--){
		ICR3 = 7372800/DoReMi[i]/2;
		TCCR3A = 0x40;
		_delay_ms(200);
		TCCR3A = 0x00;
	}
}
void error_sound(){
	ICR3 = 7372800/DoReMi[2]/2;
	TCCR3A = 0x40;
	_delay_ms(500);
	TCCR3A = 0x00;
}