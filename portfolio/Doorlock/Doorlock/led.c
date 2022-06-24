/*
 * led.c
 *
 * Created: 2022-06-24 오후 1:47:10
 *  Author: PKNU
 */
 #include <avr/io.h>
 
void led_init(){
	DDRB |= 0x0F;
}
void input_led_on(){
	PORTB |= 0x04;
}
void input_led_off(){
	PORTB &= ~0x04;
}
void change_led_on(){
	PORTB |= 0x08;
}
void change_led_off(){
	PORTB &= ~0x08;
}
void keypad_led_on(){
	PORTB = 0x01;
}
void keypad_led_off(){
	PORTB &= ~0x01;
}
void keyboard_led_on(){
	PORTB |= 0x02;
}
void keyboard_led_off(){
	PORTB &= ~0x02;
}