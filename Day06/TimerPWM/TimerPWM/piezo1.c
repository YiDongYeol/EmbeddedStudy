/*
 * piezo1.c
 *
 * Created: 2022-06-23 오전 9:32:29
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523,587, 659, 698, 783,880, 987, 1046};
int main(void)
{
	unsigned char piano=0;
	DDRB = 0x80;
	TCCR1A |= 0x0A;
	TCCR1B |= 0x19;
	TCCR1C = 0x00;
	TCNT1 = 0x0000;
	
	while(1)
	{
		ICR1 = 7372800/DoReMi[piano];
		OCR1C = ICR1/2;
		piano++;
		if(8 < piano) piano = 0;
		_delay_ms(1000);
	}
}
