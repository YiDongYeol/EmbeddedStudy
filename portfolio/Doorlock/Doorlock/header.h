/*
 * header.h
 *
 * Created: 2022-06-24 오전 9:43:01
 *  Author: PKNU
 */ 


#ifndef HEADER_H_
#define HEADER_H_

int KeyScan(void);
void motor_init();
void lock();
void unlock();
void show_open_lcd();
void show_close_lcd();

void led_init();
void input_led_on();
void input_led_off();
void change_led_on();
void change_led_off();
void keypad_led_on();
void keypad_led_off();
void keyboard_led_on();
void keyboard_led_off();

void putch(unsigned char data);
void putch_Str(char *str);
unsigned char getch();

void piezo_init();
void open_sound();
void close_sound();
void error_sound();

#endif /* HEADER_H_ */