/*
 * fnd.h
 *
 * Created: 2026-06-12 오전 10:45:55
 *  Author: kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>		// PORTA, PORTB ... 에 대한 내용이 다 들어있음. (물리적인 symbol에 대한 정의)
#include <util/delay.h>

#define FND_DATA_DDR  DDRC
#define FND_DATA_PORT PORTC

#define FND_DIGIT_DDR  DDRB
#define FND_DIGIT_PORT PORTB
#define FND_DIGIT_D1 4
#define FND_DIGIT_D2 5
#define FND_DIGIT_D3 6
#define FND_DIGIT_D4 7

// 여기서 extern이면, .c에 있는 걸 쓸 수 있는 것
extern volatile uint32_t ms_count;
extern uint32_t sec_count;
extern uint32_t dot_display;