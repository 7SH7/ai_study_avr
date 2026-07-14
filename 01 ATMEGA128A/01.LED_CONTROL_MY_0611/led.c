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
		//led_flower_off();
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
#if 1
	
	static int i = 0;

	*(unsigned char *) 0x3b = 0x01 << i;
	_delay_ms(30);	// 240ms
	
	i = (i + 1) % 8;
		
#else 

	for(int i = 0 ; i < 8 ; i++)
	{
		//PORTA = (1 << i);
		*(unsigned char *) 0x3b = 0x01 << i;
		_delay_ms(30);	// 240ms
	}	

#endif
}

void led_shift_right_on(void)
{
#if 1

	static int i = 0;

	*(unsigned char *) 0x3b = 0x80 >> i;
	// for로 하면, 240ms동안은 다른 작업 못해. 
	// 이를 막고자 함수 하나를 계속 호출해서, 다른 작업 들어올 때, 바뀌도록 수정 한 것.
	// 하지만 이거도 30ms라는 병목 시간 존재. > 차후 수정 작업 (과제)
	_delay_ms(30);	
	
	i = (i + 1) % 8;


#else

	for(int i = 0 ; i < 8; i++)
	{
		//PORTA 의 주소 0x3b
		//PORTA = 1 << 7; // 10000000
		//PORTA = (PORTA >> i);
		
		*(unsigned char *)0x3b = 0x80 >> i;
		_delay_ms(30);
	}

#endif
}

void led_shift_left_keep_on(void)
{
#if 1

	static int i = 0;
	
	*(unsigned char *)0x3b |= (0X01 << i);
	_delay_ms(30);

	if(i==7) led_all_off();
	i = (i + 1) % 8;

#else
	
	for(int i = 0 ; i < 8 ; i++)	// 마지막에 전부 0으로 하는걸 넣어주는 게 필요..
	{
		PORTA ^= (1 << i);	// 이걸.. PORTA |= (0x01 << i); 이렇게도 가능하다..
		_delay_ms(30);
		if(i==7)	led_all_off();
	}

#endif

}

void led_shift_right_keep_on(void)
{
#if 1

	static int i = 0;

	*(unsigned char *)0x3b |= (0x80 >> i);
	_delay_ms(30);	
	
	if(i == 7)	led_all_off();
	i = (i+1)%8;

#else

	PORTA = 0; 
	for(int i = 7 ; i >= 0; i--)
	{
		PORTA ^= (1 << i);
		_delay_ms(30);
	}
		
	/*
	for(int i = 0 ; i < 8 ; i++)
	{
		PORTA |= (0x80 >> 1);  // 이런 식도 가능.
		// 1000 0000 을 그냥 한쪽씩 밀면 되는 거니까.. → 훨씬 간단하고 직관..
	}
	*/
#endif
}

void led_flower_on(void)
{
#if 1

	static int i = 0;
	*(unsigned char *)0x3b |= ((0x18) << i) | ((0x18) >> i);
	_delay_ms(30);

	if(i == 4)  led_all_off();
	i = (i + 1) % 5;
	
#else

	PORTA = 0x18; // 00011000
	for(int i = 0 ; i < 5; i++)
	{
		_delay_ms(30);
		PORTA = (PORTA << 1 | PORTA >> 1);
		// PORTA |= (0x18) << i | (0x18 >> i);
		// _delay_ms(30);

	}
	// PORTA = 0x18;
#endif
}

void led_flower_off(void)
{
#if 1
	
	static int i = 0;
	_delay_ms(30);
	
	*(unsigned char *) 0x3b = (0xff << i) & (0xff >> i);
	
	if(i == 5)	led_all_on();
	i = (i + 1) % 6;

#else

	PORTA = 0xff;
	for(int i = 0 ; i < 5 ; i++)
	{
		_delay_ms(300);
		PORTA = (PORTA >> 1) & (PORTA << 1);
		// PORTA &= ~(0x01 << i); 
		// PORTA &= ~(0x01 >> (7 - i));
	}
#endif
}

