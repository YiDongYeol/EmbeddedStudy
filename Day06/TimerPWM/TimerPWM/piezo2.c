/*
 * piezo2.c
 *
 * Created: 2022-06-23 오전 10:18:34
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783,880, 987, 1046};
volatile unsigned char sound_flag = 1;
int main(void)
{
	DDRE = 0x08;
	
	TCCR3A = 0x00;
	TCCR3B = 0x19;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	EICRB = 0xFF;
	EIMSK = 0xF0;
	EIFR = 0xF0;
	sei();
	while(1)
	{
		if(sound_flag)
		{
			_delay_ms(2000);
			TCCR3A = 0x00;
			sound_flag = 0;
		}
	}
}
SIGNAL(INT4_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[0]/2;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[1]/2;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT6_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[2]/2;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}
SIGNAL(INT7_vect)
{
	cli();
	ICR3 = 7372800/DoReMi[3]/2;
	TCCR3A = 0x40;
	sound_flag = 1;
	sei();
}