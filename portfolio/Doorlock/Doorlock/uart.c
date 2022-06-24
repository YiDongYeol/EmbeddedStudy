/*
 * uart.c
 *
 * Created: 2022-06-24 오후 2:17:53
 *  Author: PKNU
 */ 
#include <avr/io.h>

void putch(unsigned char data) {
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}
void putch_Str(char *str){
	unsigned char i=0;
	while(str[i]!='\0')
	putch(str[i++]);
}
unsigned char getch(){
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data=UDR0;
	UCSR0A |= 0x80;
	return data;
}