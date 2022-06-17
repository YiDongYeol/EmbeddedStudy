/*
 * fnd2.c
 *
 * Created: 2022-06-17 오후 4:26:26
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	int Num[9] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F};
	DDRA = 0xFF;
	DDRD = 0x00;
	while(1){
		
		if(PIND!=0x00){
			int tmp = PIND;
			int count = 0;
			while(tmp!=0x00){
				tmp=tmp>>1;
				count++;
			}
			PORTA = Num[count];
		}
		else{
			PORTA = Num[0];
		}
	}
	return 0;
}