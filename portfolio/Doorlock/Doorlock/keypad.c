/*
 * keypad.c
 *
 * Created: 2022-06-24 오전 9:41:30
 *  Author: PKNU
 */ 

#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int KeyScan(void)
{
	DDRA = 0xF8;
	PORTA = 0x08;
	_delay_ms(1);
	if(PINA&0x01) return 1;
	if(PINA&0x02) return 2;
	if(PINA&0x04) return 3;
	PORTA = 0x00;
	_delay_ms(10);
	
	PORTA = 0x10;
	_delay_ms(1);
	if(PINA&0x01) return 4;
	if(PINA&0x02) return 5;
	if(PINA&0x04) return 6;
	PORTA = 0x00;
	_delay_ms(10);
	
	PORTA = 0x20;
	_delay_ms(1);
	if(PINA&0x01) return 7;
	if(PINA&0x02) return 8;
	if(PINA&0x04) return 9;
	PORTA = 0x00;
	_delay_ms(10);
	
	PORTA = 0x40;
	_delay_ms(1);
	if(PINA&0x01) return 10;
	if(PINA&0x02) return 0;
	if(PINA&0x04) return 11;
	PORTA = 0x00;
	_delay_ms(10);
	
	return 12;
}