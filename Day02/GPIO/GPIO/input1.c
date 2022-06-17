/*
 * input1.c
 *
 * Created: 2022-06-17 오후 3:19:54
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>

int main()
{
	DDRD = 0x00;	//포트 D 입력으로 설정
	DDRA = 0xFF;	//포트 A 출력으로 설정
	while(1)
	{
		if(PIND!=0x00){
			PORTA = 0x00;
			int tmp = PIND;
			while(tmp!=0x00){
				tmp = tmp>>1;
				PORTA = PORTA<<1;
				PORTA++;
			}
		}
		else
			PORTA = 0x00;
	}
	return 0;
}