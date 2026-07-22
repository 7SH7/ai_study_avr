/*
 * keypad.h
 *
 * Created: 2026-06-29 오후 2:11:23
 *  Author: kccistc
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define KEYPAD_DDR DDRA
#define KEYPAD_PIN PINA
#define KEYPAD_PORT PORTA

#endif /* KEYPAD_H_ */