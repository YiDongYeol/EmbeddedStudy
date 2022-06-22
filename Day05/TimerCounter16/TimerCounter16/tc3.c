/*
 * tc3.c
 *
 * Created: 2022-06-22 오후 4:18:33
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,
	0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,
0X79,0X71,0X08,0X80};
volatile unsigned char time_s=0;
int main(void) {
	DDRA = 0xFF;
	TCCR1A = 0x00;
	TCCR1B = 0x05;
	OCR1A = 7258;
	TIMSK = 0x10;
	TIFR |=1 << OCF1A;
	
	sei();
	while (1) {
		PORTA = FND_DATA_TBL[time_s];
	} return 0;
}

SIGNAL(TIMER1_COMPA_vect) {
	cli();
	OCR1A += 7258;
	if(time_s >= 17)
	time_s =0;
	else
	time_s++;
	sei();
}