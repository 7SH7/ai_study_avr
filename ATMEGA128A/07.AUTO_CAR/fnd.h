/*
 * fnd.h
 *
 * Created: 2026-06-12 오전 10:45:55
 *  Author: kccistc
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>		// PORTA, PORTB ... 에 대한 내용이 다 들어있음. (물리적인 symbol에 대한 정의)
#include <util/delay.h>

#define FND_DATA_DDR  DDRD
#define FND_DATA_PORT PORTD

#define FND_DIGIT_DDR  DDRC
#define FND_DIGIT_PORT PORTC
#define FST_FND_DIGIT_D1 0
#define FST_FND_DIGIT_D2 1
#define FST_FND_DIGIT_D3 2
#define FST_FND_DIGIT_D4 3

#define SND_FND_DIGIT_D1 4
#define SND_FND_DIGIT_D2 5
#define SND_FND_DIGIT_D3 6
#define SND_FND_DIGIT_D4 7
