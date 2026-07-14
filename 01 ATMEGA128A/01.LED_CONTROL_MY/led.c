/*
 * led.c
 *
 * Created: 2026-06-10 오후 3:09:12
 *  Author: kccistc
 */ 

#include "led.h"

void init_led(void);
void led_all_on(void);
void led_all_off(void);
void led_right_on(void);
void led_left_on(void);
void led_odd_on(void);
void led_even_on(void);

void init_led(void)
{
	DDRA = 0xff;	// PORTA를 출력모드
	PORTA = 0x00;	// PORTA에 물려있는 led를 all off	
}


void led_all_on(void)
{
	PORTA=0xff;
}

void led_all_off(void)
{
	PORTA=0x00;
}

void led_right_on(void)
{
	PORTA=0x0f;
}

void led_left_on(void)
{
	PORTA=0xf0;
}

void led_odd_on(void)
{
	// todo: LED0, LED2, LED4, LED6 이런 걸 명명 해주고, 처리해주면 좀 더 깔끔해지겠다.
	PORTA = ((1<<0) | (1<<2) | (1<<4) | (1<<6));
}

void led_even_on(void)
{
	PORTA = ((1<<1) | (1<<3) | (1<<5) | (1<<7));
}
