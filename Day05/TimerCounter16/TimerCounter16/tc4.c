/*
 * tc4.c
 *
 * Created: 2022-06-22 오후 4:22:15
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h> 

unsigned char FND_DATA_TBL[]={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,
	0X07,0X7F,0X67,0X77,0X7C,0X39,0X5E,
0X79,0X71,0X08,0X80};
volatile unsigned char time_s=0;
volatile unsigned char FND_flag=0, edge_flag = 0;
int main(void)
{
	DDRA = 0xFF;
	DDRE = 0x00;
	TCCR3A = 0x00;
	
	TCCR3B = 0x45;
	ETIMSK = 0x20;
	ETIFR |=1 << ICF3;
	sei();
	PORTA = FND_DATA_TBL[0];
	while (1) {
		if(FND_flag) {
			if(time_s > 15)
			time_s = 15;
			PORTA = FND_DATA_TBL[time_s];
			FND_flag = 0;
		}
	} return 0;
}

SIGNAL(TIMER3_CAPT_vect) {
	cli();
	unsigned int count_check;
	
	if(edge_flag == 0) {
		TCCR3B = 0x05;
		TCNT3 = 0;
		ICR3 = 0;
		edge_flag = 1;
	}
	else 
	{
		TCCR3B = 0x45;
		count_check = ICR3;
		time_s = count_check/726;
		FND_flag = 1;
		edge_flag = 0;
	} 
	sei();
}