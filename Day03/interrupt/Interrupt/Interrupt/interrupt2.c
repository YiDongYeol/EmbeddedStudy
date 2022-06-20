/*
 * interrupt2.c
 *
 * Created: 2022-06-20 오전 10:41:24
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile bool check = false;

SIGNAL(INT4_vect){
	check = !check;
}
int main()
{
	DDRE = 0x00;
	DDRA = 0xff;
	EIMSK = 1<<INT4;
	EICRB = (1<<ISC41 | 0<<ISC40);
	sei();
	for(;;){
		if(check) PORTA = 0xff;
		else PORTA = 0x00;
	}
}