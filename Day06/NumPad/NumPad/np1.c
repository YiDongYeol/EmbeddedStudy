/*
 * np1.c
 *
 * Created: 2022-06-23 오후 4:09:34
 * Author : PKNU
 */ 

#include <avr/io.h>


//0 = c0
//1 = c1
//2 = c2
//3 = r0
//4 = r1
//5 = r2
//6 = r3
int KeyScan(void)
{
	PORTA = 0x08;
	if(PINA&0x01) return 1;
	if(PINA&0x02) return 2;
	if(PINA&0x04) return 3;
	PORTA = 0x00;
	
	PORTA = 0x10;
	if(PINA&0x01) return 4;
	if(PINA&0x02) return 5;
	if(PINA&0x04) return 6;
	PORTA = 0x00;
	
	PORTA = 0x20;
	if(PINA&0x01) return 7;
	if(PINA&0x02) return 8;
	if(PINA&0x04) return 9;
	PORTA = 0x00;
	
	PORTA = 0x40;
	if(PINA&0x01) return 0;
	if(PINA&0x02) return 0;
	if(PINA&0x04) return 0;
	PORTA = 0x00;
	
	return 0;
}

int main(void)
{
	int Num[10] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	DDRA = 0xF8;
	DDRD = 0xFF;
	
	while(1){
		PORTD = Num[KeyScan()];
	}
}


