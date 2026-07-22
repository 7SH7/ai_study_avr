/*
 * 05.ULTRASONIC.c
 *
 * Created: 2026-06-17 오후 1:30:11
 * Author : kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>	// sei, cli 등등 함수 내장.
#include <stdio.h>

extern int led_main(void);
extern void init_uart0(void);
extern void UART0_transmit(uint8_t data);
extern void pc_command_processing(void);
extern void init_ultrasonic(void);
extern void make_trigger(void);
extern void ultrasonic_processing(void);

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);	// printf 사용..

volatile uint32_t msec_count = 0;	// volatile 최적화 방지
volatile int ultrasonic_check_time = 0; 

// interrupt는 main 함수 위에 배치하는 것
/*
ISR (interrupt service routine) : 인터럽트 처리 함수 ISR로 시작
TIMER0_OVF_vect : Timer 0 overflow INT 가 발생이 되면, 이곳으로 진입함.
250개의 PULSE를 COUNT(1MS)하면 이곳으로 자동 진입한다.
ISR은 가능한 짧게 작성한다.
*/
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;	// TCNT0 6~256: 250개 pulse count 하기 위해
	msec_count++;	// 1ms count
	ultrasonic_check_time++;
}

int main(void)
{
	// want to do : 500ms 주기로 바뀌도록 하기
	init_led();
	init_timer0();
	init_uart0();
	init_ultrasonic();

	stdout = &OUTPUT;	// printf가 동작할 수 있도록 stdout을 설정
	sei();		// 전역(대문) interrupt 허용
	
//	led_main();

    while (1) 
    {
//		pc_command_processing();	//	 circular queue 끄집어내서 처리하는 거
		ultrasonic_processing();
    }
}

/*
1. timer0을 초기화 한다.
   AVR에서 8bit timer 0 / 2 중에서 0번을 초기화 한다.
   임베디드에서 가장 신경을 써야 할 부분이 초기화 하는 부분. ☆
   초기화가 잘못되면, 이후 과정이 꼬이니까
2. 8bit가지고 1ms를 측정하는 timer/counter를 만들고자 한다.
 2-1. 분주비를 설정 (64분주)
      : 기존에 n번만큼 진동하고, 이어서 반응함. 그런데 그걸 k분주만큼 진동해야, 1회 반응 하는도록 하는 것이 분주
	    > 16MHz / 64 = 250,000Hz 
 2-2. 1주기가 잡아먹는 시간을 계산
	    > T = 1 / f = 1 / 250,000 = 0.000004 sec = 4 us = 0.004ms
 2-3. 8bit로 카운트 하는 시간을 계산
 	    > 8 bit timer overflow : 256이 되는 순간 overflow
		> 0.04ms * 256개 ==> 0.001024 sec = 1024 us (1.024ms) 
		> 0.04ms * 250개 ==> 0.001sec (1ms)

> 256 / 16MHz * 64 이거 아냐? 맞는데.. 과정을 그냥 나열한거구나..
*/
init_timer0(void)
{
	TCNT0 = 6;	// TCNT0 0~256 : 250개 pulse count 위해

	TCCR0 &= ~(1 << CS02 | 1 << CS01 | 1 << CS00);	// 0분주
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;	// 64분주
	
	TIMSK |= 1 << TOIE0;	// TIMER0 Overflow INT
	sei();	// 전역(대문)
}

