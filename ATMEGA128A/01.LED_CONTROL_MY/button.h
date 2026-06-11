/*
 * button.h
 *
 * Created: 2026-06-10 오전 11:44:54
 *  Author: kccistc
 */ 


#define F_CPU 16000000UL	// 16MHz
#include <avr/io.h>			// PORTA, PORTB, PORTD.. ID관련 REG가 들어있다.
#include <util/delay.h>		// _delay_ms, _delay_us 등

#define BUTTON_DDR DDRD		// 복잡해지면, DDRD가 무슨 역할하는지 헷갈려지니까.. BUTTON_DDR로 명명!
#define BUTTON_PIN PIND		// PORTD를 읽는 register. 5v > 1, 0v > 0

#define BUTTON0PIN 3		// PORTD.3
#define BUTTON1PIN 4		// PORTD.4
#define BUTTON2PIN 5		// PORTD.5
#define BUTTON3PIN 6		// PORTD.6

#define BUTTON0 0			// PORTD.3의 가상 index (sw 번호)
#define BUTTON1 1			// PORTD.4의 가상 index (sw 번호)
#define BUTTON2 2			// PORTD.5의 가상 index (sw 번호)
#define BUTTON3 3			// PORTD.6의 가상 index (sw 번호)
#define BUTTON_NUMBER 4		// 버튼 개수

#define BUTTON_PRESS 1		// 버튼 누르면 high (active-high)
#define BUTTON_RELEASE 0	// 버튼 누르면 high (low)

 