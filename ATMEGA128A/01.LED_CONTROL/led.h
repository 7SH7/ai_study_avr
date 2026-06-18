/*
 * led.h
 *
 * Created: 2026-06-10 오후 3:09:22
 *  Author: user
 */ 


#ifndef LED_H_  // define 되지 않았다면, 정의해주고! 정의되어있으면 넘어가라!
#define LED_H_
#define F_CPU 16000000UL  // 16MHz
#include <avr/io.h>  // PORTA PORTB PORTD... IO관련 reg가 들어 있다.
#include <util/delay.h>  // _delay_ms _delay_us 등

#endif /* LED_H_ */