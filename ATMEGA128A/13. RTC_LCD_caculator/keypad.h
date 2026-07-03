/*
 * keypad.h
 *
 * Created: 2026-07-02 오후 2:22:42
 *  Author: kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define KEYPAD_DDR DDRA
#define KEYPAD_PIN PINA
#define KEYPAD_PORT PORTA

#define BUZZER_DDR   DDRG
#define BUZZER_PORT  PORTG
#define BUZZER_PIN   PG2  // 또는 숫자 2로 적으셔도 됩니다.

void buzzer_beep(void);