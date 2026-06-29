/*
 * 11. KEYPAD.c
 *
 * Created: 2026-06-29 오후 1:42:33
 * Author : kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> //인터럽트 관련 함수
#include <stdio.h>
#include "queue.h"

extern void init_uart0(void);
extern void UART0_transmit(void);
extern uint8_t keypad_scan(void);
extern init_keypad(void);
extern void insert_queue(uint8_t value);
extern uint8_t read_queue();
extern uint8_t read_queue_front();

void init_timer0(void);

volatile uint32_t keypad_counter = 0; // volatile 최적화 방지

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

ISR(TIMER0_OVF_vect) {
	
	volatile uint8_t keydata = 0;

	TCNT0 = 6;
	// keypad_counter 1번 누른 것에 대해서는 60만큼 기다렸다가 결과가 나오도록 하겠다.
	if(++keypad_counter >= 60)
	{
		keypad_counter = 0;
		
		if(keydata = keypad_scan()){	// keypad를 check해서 눌려진 것이 있으면
	
			insert_queue(keydata);						// circula queue에 저장한다	
		}
	}
}

extern double  calculate(char* expression);

int main(void) {

	uint8_t key_value;
	
	init_uart0();
	init_timer0();
	init_keypad();

	queue_init();

	stdout = &OUTPUT;
	sei(); // 전역(대문) interrupt 허용

	char expression[1024];
	int idx = 0;
	double result = 0;
	memset(expression, 0, sizeof(expression));

	while(1)	
	{
		// 비어있지 않으면
		if(!queue_empty())
		{
			// 값 가지고 나오고,,
			uint8_t key = read_queue(); 

			// = 인지 확인하고
			if(key == '=')
			{
				expression[idx] = '\0';	
				result = calculate(expression);
				idx = 0;
    
				// avr에서는 .2f하면 에러..
				int int_part = (int)result;
				int dec_part = (int)((result - int_part) * 100);
    
				printf("expression: %s=%d.%02d\n", expression, int_part, dec_part);
				continue;
			}
			
			// 아니면 넣는다.
			expression[idx++] = key;
		}
	}

	
	

}

void init_timer0(void) {
	TCNT0 = 6; // TCNT0 6~256 : 250개 펄스 count

	TCCR0 &= ~(1 << CS02 | 1 << CS01 | 1 << CS00); // 초기화 (0분주)
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00; //6분주
	TIMSK |= 1 << TOIE0; // TIMER0 Overflow INT

}