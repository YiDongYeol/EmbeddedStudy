/*
 * lcd2.c
 *
 * Created: 2022-06-20 오후 4:58:03
 *  Author: PKNU
 */ 

#define F_CPU	7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

int main()
{
	DDRA = 0xff;
	DDRG = 0x0f;
	Byte str1[13]; 
	
	Lcd_Init();
	while(1){
		for(int i = 2; i<=9; i++){
			for(int j = 1; j<=9; j++){
				Lcd_Pos(0, 0);
				sprintf(str1, "%d * %d = %d", i, j, i*j);
				Lcd_STR(str1);
				_delay_ms(1000);
			}
		}
	}
	
	return 0;
}