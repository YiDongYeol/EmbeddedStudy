/*
 * tc2.c
 *
 * Created: 2022-06-22 오후 4:14:13
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h> 
#include <avr/interrupt.h>
volatile unsigned char LED_Data = 0x00;
int main(void)
{
	DDRC = 0x0F;
	TCCR3A = 0x00;
	TCCR3B = 0x05;
	
	TCNT3 = 58277;
	ETIMSK = 0x04;
	ETIFR |=1 << TOV3;
	sei();
	
	while (1) {
		PORTC = LED_Data;
	} 
	return 0;
}
SIGNAL(TIMER3_OVF_vect)
{
	cli();
	TCNT3 = 58277;
	LED_Data++;
	if(LED_Data>0x0F)
	LED_Data = 0;
	sei();
}