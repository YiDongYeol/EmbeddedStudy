/*
 * tp2.c
 *
 * Created: 2022-06-22 오후 5:06:10
 *  Author: PKNU
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
volatile int Light = 0;
volatile unsigned char Light_flag = 1;
int main(void)
{
	DDRB = 0x80;
	DDRE = 0x00; 
	TCCR2 = 0x62;
	TCNT2 = 0x00;
	EICRB = 0xFF;
	EIMSK = 0xF0;
	EIFR = 0xF0; 
	sei();
	
	while (1)
	{
		if(Light_flag)
		{
			OCR2 = Light;
			Light_flag = 0;
		}
	}
}
SIGNAL(INT4_vect)
{
	cli();
	Light = 0;
	Light_flag = 1;
	sei();
}
SIGNAL(INT5_vect)
{
	cli();
	Light -= 51;
	if(Light < 0)
	Light = 0;
	Light_flag = 1;
	sei();
}
SIGNAL(INT6_vect)
{
	cli();
	Light += 51;
	if(Light > 255)
	Light = 255;
	Light_flag = 1;
	sei();
}
SIGNAL(INT7_vect)
{
	cli();
	Light = 255;
	Light_flag = 1;
	sei();
}