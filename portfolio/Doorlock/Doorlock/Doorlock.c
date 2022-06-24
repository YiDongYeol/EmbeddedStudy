/*
 * Doorlock.c
 *
 * Created: 2022-06-24 오전 9:40:52
 * Author : PKNU
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "header.h"

int pad_mode = 0;		// 1 키패드 입력, 2 키보드 입력
int pass[4]={2,5,8,0};
int pass_input[4];
int ind = 0;
int press = 0;
int press_btn = 0;
int locked = 1;
int change_wait = 0;
int input;

void interrupt_init(){
	EIMSK = 0xF0;
	EICRB = 0xAA;
	sei();
}

int check_pass(){
	int fault=0;
	for(int i=0; i<4; i++){
		if(pass[i]!=pass_input[i]){
			fault=1;
			break;
		}
	}
	if(fault || ind == 5){
		return 0;
	}
	return 1;
}

int change_pass(){
	int fault=0;
	for(int i=0; i<4; i++){
		if(pass_input[i]==99){
			fault = 1;
			break;
		}
	}
	if(fault || ind == 5){
		return 0;
	}
	return 1;
}
void open(){
	unlock();
	locked = 0;
	show_open_lcd();
	open_sound();
}

void close(){
	lock();
	locked = 1;
	show_close_lcd();
	close_sound();
}

void init_pad(){
	for(int i=0; i<4; i++)	pass_input[i] = 0;
	ind = 0;
	input = 12;
	input_led_off();
	change_led_off();
}

void input_mode()
{
	input_led_on();
	press_btn = 12;
	press = 0;
	while(1){
		input=KeyScan();
		if(input == 12){
			if(press){
				if(press_btn == 10){
					init_pad();
					break;
				}
				else if(press_btn == 11){
					if(check_pass()) {
						open();
					}
					else {
						error_sound();
					}
					init_pad();
					break;
				}
				else{
					if(ind == 4 || ind == 5) {
						ind = 5;
						continue;
					}
					pass_input[ind++]=press_btn;
				}
			}
			press_btn = 12;
			press = 0;
		}
		else {
			press_btn = input;
			press = 1;
		}
	}
}

void change_mode(){
	press_btn = 12;
	press = 0;
	for(int i = 0; i<4; i++){
		pass_input[i]=99;
	}
	while(1){
		input=KeyScan();
		if(input == 12){
			if(press){
				if(press_btn == 10){
					init_pad();
					break;
				}
				else if(press_btn == 11){
					if(change_pass()) {
						for(int i=0; i<4; i++)
							pass[i] = pass_input[i];
						open_sound();
					}
					else {
						error_sound();
					}
					init_pad();
					break;
				}
				else {
					if(ind == 4 || ind == 5) {
						ind = 5;
						continue;
					}
					pass_input[ind++]=press_btn;
				}
			}
			press_btn = 12;
			press = 0;
		}
		else {
			press_btn = input;
			press = 1;
		}
	}
}

void keyboard_mode(){
	unsigned char text[] = "\r\ninput please\r\n";
	char str[20]="";
	unsigned int cnt = 0;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
	while(1){
		if(!locked){
			sprintf(str,"\r\nUNLOCKED\r\n");
			putch_Str(str);
			while(1){
				cnt = getch();
				if(cnt == 13){
					sprintf(str,"\r\nLOCKED\r\n");
					putch_Str(str);
					close();
					break;
				}
				else if(cnt == 27){
					sprintf(str,"\r\nKeyBoard Mode Off\r\n");
					putch_Str(str);
					return;
				}
			}
		}
		else{
			putch_Str(text);
			for(int i=0;i<4; i++){
				cnt = getch();
				if(cnt==27){
					init_pad();
					pad_mode=0;
					sprintf(str,"\r\nKeyBoard Mode Off\r\n");
					putch_Str(str);
					return;
				}
				cnt -= '0';
				pass_input[i] = cnt;
				putch('*');
			}
			
			if(check_pass())
			{
				open();
				sprintf(str,"\r\nOPEN\r\n");
				putch_Str(str);
			}
			else
			{
				error_sound();
				sprintf(str,"\r\nERR\r\n");
				putch_Str(str);
			}
		}
	}
}
int main(void)
{
	piezo_init();
	motor_init();
	show_close_lcd();
	interrupt_init();
	led_init();
	while(1)
	{	
		keypad_led_off();
		keyboard_led_off();
		if(pad_mode == 1) {
			keypad_led_on();
			while(1){
				input = KeyScan();
				if(input==12){
					if(press){
						if(press_btn == 10){
							pad_mode == 0;
							break;
						}
						else if(press_btn == 11){
							if(!locked) close();
							else input_mode();
						}
						else if (press_btn == 13){
							change_wait = 0;
							change_mode();
						}
						press_btn = 12;
						press = 0;
					}
				}
				else {
					if(input == 10){
						if(press){
							if(change_wait>40){
								change_led_on();
								press_btn = 13;
								continue;
							}
							change_wait++;
						}
						press_btn = 10;
						press = 1;
					}
					else if (input == 11){
						press_btn = 11;
						press = 1;
					}
				}
			}
		}
		
		else if (pad_mode == 2){
			keyboard_led_on();
			keyboard_mode();
			pad_mode=0;
		}
	}
}
SIGNAL(INT4_vect)
{
	cli();
	pad_mode = 1;
	sei();
}

SIGNAL(INT5_vect)
{
	cli();
	pad_mode = 2;
	sei();
}