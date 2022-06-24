/*
 * stepmotor.c
 *
 * Created: 2022-06-24 오전 10:10:12
 *  Author: PKNU
 */ 

#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>

unsigned char Step[4] = {0x10,0x20,0x40,0x80};
	
void motor_init(){
	DDRB = 0x20;
	DDRD = 0xF0;
	PORTB &= ~0x20;
}
void unlock()
{
	unsigned char i, t = 0;
	for ( i = 0; i < 24 ; i++ )
	{
		PORTD = Step[t];
		if(t == 3) t = 0;
		else t++;
		_delay_ms(10);
	}
}

void lock(){
	unsigned char i, t = 3;
	for ( i = 0; i < 24 ; i++ )
	{
		PORTD = Step[t];
		if(t == 0) t = 3;
		else t--;
		_delay_ms(10);
	}
}
