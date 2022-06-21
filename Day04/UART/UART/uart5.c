/*
 * uart5.c
 *
 * Created: 2022-06-21 오전 11:44:58
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

int main(void) {
	unsigned char text[] = "input please\r\n";
	char str[20]="";
	unsigned int cnt = 0;
	DDRE = 0xfe;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
	
	while(1){
		putch_Str(text);
		cnt = getch()-'0';
		for(int j=0; j<9; j++){
			sprintf(str,"%d * %d = %d\r\n",cnt,j+1,cnt*(j+1));
			putch_Str(str);
		}
		putch_Str("\r\n");
	}
}