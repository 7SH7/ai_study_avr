/*
 * 01.LED_CONTROL.cpp
 *
 * Created: 2026-06-10 오전 10:20:21
 * Author : kccistc
 */ 
#define F_CPU 16000000UL	// 16MHz
#include <avr/io.h>	// PORTA PORTD 등의 I/O register들이 들어이다.
#include <util/delay.h> // _delay_ms, _delay_us 등의 함수가 들어있다.
#include "button.h"
#include "led.h"

extern void init_led(void);		// init_led함수는 내 파일에 들어있는 게 아니라, 다른 화일에 들어 있음을 compiler에게 신고
extern void init_button(void);
extern int get_button(int button_num, int button_pin);
extern void led_all_off(void);
extern void led_all_on(void);
extern void led_right_on(void);
extern void led_left_on(void);
extern void led_odd_on(void);
extern void led_even_on(void);

#if 1

void (*fp1[])()={
	led_all_off,
	led_all_on,
	led_right_on,
	led_left_on
};

void (*fp2[])()={
	led_all_off,
	led_odd_on,
	led_even_on,
	led_all_on
};

int main(void)
{
	int button0_state=0;	// 초기 상태를 LED all of로 출발하자
	int button1_state=0;	// 초기 상태를 LED all of로 출발하자
	
	init_button();

	while (1)
	{
		// Recommendation) if(get_button) { 변수값 증가 작업 } 
		//				   그 밑에 따로, if(변수값 == target) {  발생 작업  }
		// 위의 방식을 추천. 이유는 기능의 연쇄성 때문에..
		// 최대한 연관된 기능을 따로 명명해주는 것이 좋다...
		
		// 버튼 0 > led_all_off > led_all_on > led_right_on > led_left_on
		if(get_button(BUTTON0, BUTTON0PIN))
		{
			if(button0_state==4)	button0_state=0;
			fp1[button0_state]();
			button0_state++; 
		}
		
		// 버튼 1 > led_all_off > led_odd_on > led_even_on > led_all_on 반복
		if(get_button(BUTTON1, BUTTON1PIN))
		{
			if(button1_state==4)	button1_state=0;
			fp2[button1_state]();
			button1_state++;
		}

		// 버튼 3 > 초기화
		if(get_button(BUTTON3, BUTTON3PIN)){
			led_all_off();
			button0_state=0;
			button1_state=0;
		}
	}
}


#endif

#if 0

void (*fp1[])()={
	led_all_off,
	led_all_on,
	led_right_on,
	led_left_on
};

void (*fp2[])()={
	led_all_off,
	led_odd_on,
	led_even_on,
	led_all_on
};

int main(void)
{
	int button0_state=0;	// 초기 상태를 LED all of로 출발하자
	int button1_state=0;	// 초기 상태를 LED all of로 출발하자
	
	init_button();

	while (1)
	{
		// Recommendation) if(get_button) { 변수값 증가 작업 }
		//				   그 밑에 따로, if(변수값 == target) {  발생 작업  }
		// 위의 방식을 추천. 이유는 기능의 연쇄성 때문에..
		// 최대한 연관된 기능을 따로 명명해주는 것이 좋다...
		
		// 버튼 0 > led_all_off > led_all_on > led_right_on > led_left_on
		if(get_button(BUTTON0, BUTTON0PIN))
		{
			if(button0_state==4)	button0_state=0;
			button0_state++;
		}
	
		if(button0_state==1) fp1[button0_state]();
		
		// 버튼 1 > led_all_off > led_odd_on > led_even_on > led_all_on 반복
		if(get_button(BUTTON1, BUTTON1PIN))
		{
			if(button1_state==4)	button1_state=0;
			button1_state++;
		}

		if(button0_state==1)	fp2[button1_state]();


		// 버튼 3 > 초기화
		if(get_button(BUTTON3, BUTTON3PIN)){
			led_all_off();
			button0_state=0;
			button1_state=0;
		}
	}
}


#endif

#if 0

int main(void)
{
	// DDR: data direction register
	// 1: 출력, 0: 입력
	DDRA = 0b11111111;		// PortA의 LED가 8개 연결되어 있으므로, ALL 1(출력)으로 설정한다..
	
	while (1) 
    {
		PORTA = 0b11111111;  // all on (전부 켜)
		_delay_ms(1000);	 // 1000ms 만큼 유지	
		
		PORTA = 0b00000000;  // all off (전부 꺼)
		_delay_ms(1000);	 // 1000mx 만큼 유지
    }
}


#endif