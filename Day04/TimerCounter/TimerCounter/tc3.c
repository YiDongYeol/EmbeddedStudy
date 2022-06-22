/*
 * tc3.c
 *
 * Created: 2022-06-22 오전 9:04:21
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
volatile unsigned char LED_Data = 0x00;
unsigned int timer0Cnt=0;
SIGNAL(TIMER0_OVF_vect);
int main(void)
{
	DDRC = 0x0F;
	TCCR0 = 0x06;
	TCNT0 = 112;
	TIMSK = 0x01;
	TIFR |=1 << TOV0;
	
	sei();
	while (1)
	{
		PORTC = LED_Data;
	} return 0;
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 112;
	timer0Cnt++;
	if(timer0Cnt == 400)
	{
		LED_Data++;
		if(LED_Data>0x0F) LED_Data = 0;
		timer0Cnt=0;
	} sei();
}