/*
 * interrupt4.c
 *
 * Created: 2022-06-20 오전 11:37:42
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char Shift_flag = 1;

int main(void) {
	unsigned char LED_Data = 0x01;
	
	DDRC = 0x0F;
	DDRE = 0x00;
		
	EICRB = 0xC8;
	
	EIMSK = 0xA0;
	//EIFR = 0xA0;
	
	sei();
	
	while(1){
		
		PORTC = LED_Data;
		if(Shift_flag == 1){
			if(LED_Data == 0x08) LED_Data = 0x01;
			
			else LED_Data <<= 1;
		}
		
		else if(Shift_flag == 2)
		{
			if(LED_Data == 0x01) LED_Data = 0x08;
			else LED_Data >>= 1;
		}
		_delay_ms(100);
	}
}

SIGNAL(INT5_vect){
	cli();
	Shift_flag = 1;
	sei();
}
SIGNAL(INT7_vect){
	cli();
	Shift_flag = 2;
	sei();
}