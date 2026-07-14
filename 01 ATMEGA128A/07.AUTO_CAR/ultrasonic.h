/*
 * ultrasonic.h
 *
 * Created: 2026-06-17 오후 1:32:38
 *  Author: kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TRIG_DDR  DDRA
#define TRIG_PORT PORTA
#define TRIG_PIN_L  0
#define TRIG_PIN_C  1
#define TRIG_PIN_R  2

#define ECHO_DDR   DDRE
#define ECHO_PORT  PINE	// external int 4
#define ECHO_PIN_L   4	 // 각각 발생할때, TIMSK 에서 해당 ECHO PIN을 1로, 나머진 0으로 처리 해주는 방식?
#define ECHO_PIN_C   5
#define ECHO_PIN_R   6
