/*
 * sm4.c
 *
 * Created: 2022-06-23 오후 3:22:37
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL

#include <avr/io.h>
#include <avr/interrupt.h>
#define DIR_L 0
#define DIR_R 1
unsigned char timer0Cnt=0, mot_cnt=0;
volatile unsigned char dir=DIR_R;
unsigned char Step[] = {0x90, 0x80, 0xC0, 0x40,
0x60, 0x20, 0x30, 0x10};
SIGNAL(TIMER0_OVF_vect);
SIGNAL(TIMER1_OVF_vect);

int main(void) {
	DDRB = 0x20;
	PORTB &= ~0x20;
	DDRD = 0xF0;
	TCCR0 = 0x07;
	TCNT0 = 112;
	TCCR1A = 0;
	TCCR1B = 0x04;
	
	TCNT1H = 0xFB;
	TCNT1L = 0x0D;
	TIMSK = 0x05; 
	TIFR = 0x05;
	sei();
	while (1) {}
}
SIGNAL(TIMER0_OVF_vect)
{
	cli();
	TCNT0 = 112;
	timer0Cnt++;
	if(timer0Cnt == 200)
	{
		dir^=1;
		timer0Cnt=0;
	}
	sei();
}
SIGNAL(TIMER1_OVF_vect)
{
	cli();
	TCNT1H=0xFB;
	TCNT1L=0x0D;
	PORTD = Step[mot_cnt];
	if(dir==DIR_R)
	{
		if(mot_cnt++==7) mot_cnt=0;
	}
	else if(mot_cnt--==0) mot_cnt=7;
	sei();
}