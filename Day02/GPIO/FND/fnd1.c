/*
 * fnd1.c
 *
 * Created: 2022-06-17 오후 4:22:01
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0xFF;
	
	while(1){
		PORTA = 0x3F;	//0b 0011 1111	
		
	}
	return 0;
}