/*
 * led2.c
 *
 * Created: 2022-06-17 오후 1:54:30
 *  Author: PKNU
 */ 
#define F_CPU	7432800
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	bool dir = true;
	DDRA = 0xff;
	
	PORTA = 0xFE;
	while(1)
	{
		_delay_ms(300);
		if(PORTA == 0x7F)
			dir = false;
		if(PORTA == 0xFE)
			dir = true;
		if(dir)
			PORTA = (PORTA << 1) + 0x01;
		else
			PORTA = (PORTA >> 1) + 0x80;
	}
	return 0;
}