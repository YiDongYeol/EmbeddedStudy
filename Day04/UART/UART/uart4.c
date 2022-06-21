/*
 * uart4.c
 *
 * Created: 2022-06-21 오전 11:34:05
 *  Author: PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TX_flag = 0;
volatile char TX_data = 0;

unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79,0x71,0x08,0x80};

void putch(unsigned char data){
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch(void){
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data=UDR0;
	UCSR0A |= 0x80;
	return data;
}

int main(void){
	unsigned char RX_data = 0;
	DDRE = 0x0e;
	DDRA = 0xFF;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
	while(1){
		RX_data = getch();
		
		if((RX_data >= 0x30) && (RX_data <= 0x39)){
			PORTA = FND_DATA_TBL[RX_data - 0x30];
		}
	}
}