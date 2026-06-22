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

void wash_running_express_led(void);
void rinse_running_express_led(void);
void spin_running_express_led(void);


extern volatile uint32_t msec_count;	// 외부에서 가져온다.

#define FUNC_NUM 6
extern int func_state;
void (*fp[])(void) ={
	led_shift_left_on,	// func_state=0
	led_shift_right_on,
	led_shift_left_keep_on,
	led_shift_right_keep_on,
	led_flower_on,
	led_flower_off // func_state=5
};

int led_main(void)
{
	uint8_t led_toggle = 0;
	
	led_all_off();

	while(1)
	{
#if 0
		if(msec_count >= 500)
		{
			msec_count=0;
			led_toggle = !led_toggle;
			if(led_toggle)
				led_all_on();
			else led_all_off();
		}

#else
		
		fp[func_state]();
	

#endif

	}
	
	return 0;
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
	
	if(msec_count >= 100)
	{
		msec_count=0;
		*(unsigned char *) 0x3B = 1 << i;	// PORTB : 0x3B
		i = (i+1) % 8;
		//if((i = (i+1) % 8 ) == 0)
			//func_state = (func_state + 1) % FUNC_NUM;	// 다음 실행할 func으로 jmp
			
	}

#endif
		
#if 0

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
	
	if(msec_count >= 100)
	{
		msec_count=0;
		*(unsigned char *)0x3B = 0x80 >> i;
		i = (i+1) % 8;
		//if((i = (i+1) % 8 ) == 0)
		//func_state = (func_state + 1) % FUNC_NUM;	// 다음 실행할 func으로 jmp
	}



#endif

#if 0

	static int i = 0;

	*(unsigned char *) 0x3b = 0x80 >> i;
	// for로 하면, 240ms동안은 다른 작업 못해. 
	// 이를 막고자 함수 하나를 계속 호출해서, 다른 작업 들어올 때, 바뀌도록 수정 한 것.
	// 하지만 이거도 30ms라는 병목 시간 존재. > 차후 수정 작업 (과제)
	_delay_ms(30);	
	
	i = (i + 1) % 8;

#endif
#if 0

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

	if(msec_count >= 100)
	{
		msec_count=0;
		*(unsigned char *) 0x3B |= 1 << i;	// PORTB : 0x3B

		i = (i+1) % 8;

		//if((i = (i+1) % 8 ) == 0)
			//{
				//led_all_off();
				//func_state = (func_state + 1) % FUNC_NUM;	// 다음 실행할 func으로 jmp
			//}
	}

#endif

#if 0

	static int i = 0;
	
	*(unsigned char *)0x3b |= (0X01 << i);
	_delay_ms(30);

	if(i==7) led_all_off();
	i = (i + 1) % 8;

#endif

#if 0
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
	
	if(msec_count >= 100)
	{
		msec_count=0;
		*(unsigned char *) 0x3B |= (0x80 >> i);	// PORTB : 0x3B

		i = (i+1) % 8;

		//if((i = (i+1) % 8 ) == 0)
			//{
				//led_all_off();
				//func_state = (func_state + 1) % FUNC_NUM;	// 다음 실행할 func으로 jmp
			//}
	}

#endif


#if 0

	static int i = 0;

	*(unsigned char *)0x3b |= (0x80 >> i);
	_delay_ms(30);	
	
	if(i == 7)	led_all_off();
	i = (i+1)%8;

#endif

#if 0

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

	if(msec_count >= 100)
	{
		msec_count=0;
		*(unsigned char *)0x3b |= ((0x18) << i) | ((0x18) >> i);

		i = (i+1) % 8;

		//if((i = (i+1) % 8 ) == 0)
			//func_state = (func_state + 1) % FUNC_NUM;	// 다음 실행할 func으로 jmp
	
	}

#endif

#if 0

	static int i = 0;
	*(unsigned char *)0x3b |= ((0x18) << i) | ((0x18) >> i);
	_delay_ms(30);

	if(i == 4)  led_all_off();
	i = (i + 1) % 5;
	
#endif


#if 0

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

	if(msec_count >= 100)
	{
		msec_count=0;
		*(unsigned char *) 0x3b = (0xff << i) & (0xff >> i);

		i = (i+1) % 8;

		//if((i = (i+1) % 8 ) == 0)
			//func_state = (func_state + 1) % FUNC_NUM;	// 다음 실행할 func으로 jmp
	
	}

#endif



#if 0
	
	static int i = 0;
	_delay_ms(30);
	
	*(unsigned char *) 0x3b = (0xff << i) & (0xff >> i);
	
	if(i == 5)	led_all_on();
	i = (i + 1) % 6;

#endif

#if 0

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

void wash_running_express_led(void)
{
	PORTA = 0x00;
	PORTA = 0b00000001;
}

void rinse_running_express_led(void)
{
	PORTA = 0x00;
	PORTA = 0b00000010;
}

void spin_running_express_led(void)
{
	PORTA = 0x00;
	PORTA = 0b00000100;
}