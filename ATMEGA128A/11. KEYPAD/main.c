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

void init_timer0(void);

volatile uint32_t keypad_counter = 0; // volatile 최적화 방지

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

ISR(TIMER0_OVF_vect) {
	
	volatile uint8_t keydata = 0;

	TCNT0 = 6;
	if(++keypad_counter >= 60)
	{
		keypad_counter = 0;
		
		if(keydata = keypad_scan()){	// keypad를 check해서 눌려진 것이 있으면
	
			insert_queue(keydata);						// circula queue에 저장한다	
		}
	}
}

int main(void) {

	uint8_t key_value;
	
	init_uart0();
	init_timer0();
	init_keypad();

	stdout = &OUTPUT;
	sei(); // 전역(대문) interrupt 허용

	while(1)
	{
		if(queue_empty() != TRUE)
		{
			key_value = read_queue();
			printf("key_value: %c\n", key_value);
		}
	}

}

void init_timer0(void) {
	TCNT0 = 6; // TCNT0 6~256 : 250개 펄스 count

	TCCR0 &= ~(1 << CS02 | 1 << CS01 | 1 << CS00); // 초기화 (0분주)
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00; //6분주
	TIMSK |= 1 << TOIE0; // TIMER0 Overflow INT

}