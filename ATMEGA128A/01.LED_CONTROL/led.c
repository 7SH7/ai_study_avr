/*
 * led.c
 *
 * Created: 2026-06-10 오후 3:10:22
 *  Author: user
 */ 

#include "led.h"
int led_main(void);
void init_led(void);
void led_all_on(void);
void led_all_off(void);
void led_shift_left_on(void);
void led_shift_right_on(void);
void led_shift_left_keep_on(void);
void led_shift_right_keep_on(void);
void led_flower_on(void);
void led_flower_off(void);

int led_main(void)
{
	led_all_off();

	while(1)
	{
		//led_shift_left_on();
		//led_shift_right_on();	
		//led_shift_left_keep_on();	
		//led_shift_right_keep_on();
		//led_flower_on();
		led_flower_off();
	}
}

void init_led(void)
{
	DDRA=0xff;  // PORTA 를 출력 모드로 설정
	PORTA=0x00;  // PORTA에 물려있는 led를 all off
}

void led_all_on(void)
{
	PORTA=0xff;
}

void led_all_off(void)
{
	PORTA=0x00;
}

void led_shift_left_on(void)
{
	for(int i = 0 ; i < 8 ; i++)
	{
		//PORTA = (1 << i);
		*(unsigned char *) 0x3b = 0x01 << i;
		_delay_ms(30);	// 240ms
	}	
}

void led_shift_right_on(void)
{
	for(int i = 0 ; i < 8; i++)
	{
		//PORTA 의 주소 0x3b
		//PORTA = 1 << 7; // 10000000
		//PORTA = (PORTA >> i);
		
		*(unsigned char *)0x3b = 0x80 >> i;
		_delay_ms(30);
	}
}

void led_shift_left_keep_on(void)
{
	for(int i = 0 ; i < 8 ; i++)	// 마지막에 전부 0으로 하는걸 넣어주는 게 필요..
	{
		PORTA ^= (1 << i);	// 이걸.. PORTA |= (0x01 << i); 이렇게도 가능하다..
		_delay_ms(300);
		if(i==7)	led_all_off();
	}
}

void led_shift_right_keep_on(void)
{
	PORTA = 0; 
	for(int i = 7 ; i >= 0; i--)
	{
		PORTA ^= (1 << i);
		_delay_ms(300);
	}
		
	/*
	for(int i = 0 ; i < 8 ; i++)
	{
		PORTA |= (0x80 >> 1);  // 이런 식도 가능.
		// 1000 0000 을 그냥 한쪽씩 밀면 되는 거니까.. → 훨씬 간단하고 직관..
	}
	*/
}

void led_flower_on(void)
{
	PORTA = 0x18; // 00011000
	for(int i = 0 ; i < 5; i++)
	{
		_delay_ms(300);
		PORTA = (PORTA << 1 | PORTA >> 1);
		// PORTA |= (0x18) << i | (0x18 >> i);
		// _delay_ms(300);

	}
	// PORTA = 0x18;
}

void led_flower_off(void)
{
	PORTA = 0xff;
	for(int i = 0 ; i < 5 ; i++)
	{
		_delay_ms(300);
		PORTA = (PORTA >> 1) & (PORTA << 1);
		// PORTA &= ~(0x01 << i); 
		// PORTA &= ~(0x01 >> (7 - i));
	}
}

