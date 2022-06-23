/*
 * piezo3.c
 *
 * Created: 2022-06-23 오전 11:26:33
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[9] = {0, 523, 587, 659, 698, 783,880, 987, 1046};
unsigned char getch(){
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data=UDR0;
	UCSR0A |= 0x80;
	return data;
}	
int main(void)
{
	int input = 0;
	
	DDRB = 0x80;
	//DDRE = 0xfe;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
	TCCR1A = 0x00;
	TCCR1B |= 0x19;
	TCCR1C = 0x00;
	TCNT1 = 0x0000;
	
	//EICRB = 0xFF;
	//EIMSK = 0xF0;
	//EIFR = 0xF0;
	while(1)
	{
		input = getch()-'0';
		if(input){
			TCCR1A |= 0x0A;
			ICR1 = 7372800/DoReMi[input];
			OCR1C = ICR1/2;
			_delay_ms(100);
			TCCR1A = 0x00;
			input = 0;
		}
	}
}