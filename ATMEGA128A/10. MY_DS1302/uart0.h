/*
 * uart0.h
 *
 * Created: 2026-06-16 오전 9:57:39
 *  Author: kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>	

#define  QUEUE_SIZE 30
#define QUEUE_LENGTH 80
volatile int rear;	// interrupt에서 queue에 data를 저장하는 위치값
volatile int front;	// pc_command_processing에서 가져가는 위치값
volatile unsigned char rx_buff[QUEUE_SIZE][QUEUE_LENGTH];