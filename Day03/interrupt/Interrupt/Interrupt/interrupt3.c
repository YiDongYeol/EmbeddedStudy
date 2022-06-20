/*
 * interrupt3.c
 *
 * Created: 2022-06-20 오전 11:22:39
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>

volatile bool check = true;

SIGNAL(INT0_vect)
{
	check = !check;
}

int main()
{
	DDRD = 0x00;
	DDRA = 0xff;
	PORTA = 0x01;
	
	EIMSK = 1 << INT0;
	EICRA = 1 << ISC01 | 1<< ISC00;
	
	sei();
	
	while(1){
		_delay_ms(500);
		if(check){
			if(PORTA == 0b10000000)
				PORTA = 0x01;
			else
				PORTA = PORTA << 1;
		}
	}
	
	return 0;
}