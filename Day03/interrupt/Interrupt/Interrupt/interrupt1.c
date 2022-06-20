/*
 * interrupt1.c
 *
 * Created: 2022-06-20 오전 9:57:26
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char count = 0;

SIGNAL(INT0_vect)
{
	count++;
	PORTA = count;
}
int main()
{
	DDRD = 0x00;
	DDRA = 0xff;
	//EIMSK = 0x01;	// INTO 활성화
	EIMSK = 1 << INT0; // 위와 동일
	//EICRA = 0x03;	// 0b 0000 0011
	EICRA = (1 << ISC01) | (1 << ISC00);	// 위와 동일
	sei();
	
	while(1){}
	return 0;
}