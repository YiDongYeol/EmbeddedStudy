/*
 * lcd1.c
 *
 * Created: 2022-06-20 오후 2:55:13
 *  Author: PKNU
 */ 

#define F_CPU	7372800UL
#include <avr/io.h>
#include "Lcd.h"

int main()
{
	Byte str1[] = "LCD TEST";
	Byte str2[] = "ATmega128";
	DDRA = 0xff;
	DDRG = 0x0f;
	
	Lcd_Init();
	while(1){
		
		Lcd_Pos(0, 0);
		Lcd_STR(str1);
		Lcd_Pos(1, 0);
		Lcd_STR(str2);
	}
	
	return 0;
}