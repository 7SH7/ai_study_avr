/*
 * fnd.c
 *
 * Created: 2026-06-12 오전 10:46:18
 *  Author: kccistc
 */ 

#include "fnd.h"
#include <avr/interrupt.h>	

void init_fnd(void);
void find_display_FST(uint32_t sec_count, uint32_t dot_display);
int fnd_main(void);
void display_min_sec_dot(void);
void min_sec_clock();
void sec_clock();
void find_sec_clock(uint32_t sec_count, uint32_t dot_display);
void stopwatch_clock();
void run_stop_watch(uint32_t sec_count, uint32_t ms_count);	// PC7번이 1초 단위로 ON/OFF되도록

void pause_stop_watch();
void reset_stop_watch();

void time_set_fnd(int min_time);
void fnd_all_off(void);

int wash_running_express_fnd(int wash_time);

extern volatile uint32_t ms;
extern volatile uint32_t sec_count;	
extern volatile uint32_t dot_display;

void pause_stop_watch(){
	run_stop_watch(sec_count, ms);
};

void init_fnd(void)
{
	FND_DATA_DDR = 0xff; 
		
	PORTC |= 0xff;	// 출력 모드로 설정
	FST_FND_DIGIT_DDR |= 1 << FST_FND_DIGIT_D1 | 1 << FST_FND_DIGIT_D2 | 1 << FST_FND_DIGIT_D3 | 1 << FST_FND_DIGIT_D4;

	//SND_FND_DIGIT_DDR = 0xf0;	// 출력 모드로 설정
	SND_FND_DIGIT_DDR |= 1 << SND_FND_DIGIT_D1 | 1 << SND_FND_DIGIT_D2 | 1 << SND_FND_DIGIT_D3 | 1 << SND_FND_DIGIT_D4;

	
	FND_DATA_PORT = ~0xff;

}

void find_display_FST(uint32_t sec_count, uint32_t dot_display)	// PC7번이 1초 단위로 ON/OFF되도록
{
	//  0      1 	 2	   3	 4	   5 	 6 	      7      8	    9
	static uint8_t find_font[] = {~0b11000000, ~0b11111001, ~0b10100100, ~0b10110000, ~0b10011001, ~0b10010010, ~0b10000010, ~0b11011000, ~0b10000000, ~0b10011000, ~0b01111111};  // common cathode

	static int digit_select = 0;	// 자리수 선택

	switch(digit_select) {
		case 0:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count % 10];
		FST_FND_DIGIT_PORT = (uint8_t)~(1 << FST_FND_DIGIT_D4);
		break;

		case 1:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 10 % 6];
		FST_FND_DIGIT_PORT = (uint8_t)~(1 << FST_FND_DIGIT_D3);
		break;

		case 2:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 60 % 10] | (0x80 * dot_display);
		FST_FND_DIGIT_PORT = (uint8_t)~(1 << FST_FND_DIGIT_D2);
		break;

		case 3:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 600 % 6];
		FST_FND_DIGIT_PORT = (uint8_t)~(1 << FST_FND_DIGIT_D1);
		break;
	}

	digit_select = (digit_select + 1 ) % 4;
}


void run_stop_watch(uint32_t sec_count, uint32_t ms)	// PC7번이 1초 단위로 ON/OFF되도록
{
	//  0      1 	 2	   3	 4	   5 	 6 	      7      8	    9
	static uint8_t find_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0, ~0x99, ~0x92, ~0x82, ~0xd8, ~0x80, ~0x98, ~0x7f};	// common cathode

	static int digit_select = 0;	// 자리수 선택
	
	switch(digit_select) {
		case 0:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count % 10];
		FST_FND_DIGIT_PORT = (uint8_t)~(1 << FST_FND_DIGIT_D4);
		break;

		case 1:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 10 % 6];
		FST_FND_DIGIT_PORT = (uint8_t)~(1 << FST_FND_DIGIT_D3);
		break;

		case 2:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 60 % 10] | (0x80 * dot_display);;
		FST_FND_DIGIT_PORT = (uint8_t)~(1 << FST_FND_DIGIT_D2);
		break;

		case 3:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 600 % 6];
		FST_FND_DIGIT_PORT = (uint8_t)~(1 << FST_FND_DIGIT_D1);
		break;
	}
	
	digit_select = (digit_select + 1 ) % 4;
}


void find_display_2nd(uint32_t sec_count, uint32_t dot_display)	// PC7번이 1초 단위로 ON/OFF되도록
{
	//  0      1 	 2	   3	 4	   5 	 6 	      7      8	    9
	uint8_t find_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0, ~0x99, ~0x92, ~0x82, ~0xd8, ~0x80, ~0x98, ~0x7f};	// common cathode

	static int digit_select = 0;	// 자리수 선택

	switch(digit_select) {
		case 0:
		FST_FND_DIGIT_PORT = 0xff;	// 이 과정이 없으면 잔상이 많이 나타남..
		FND_DATA_PORT = find_font[sec_count % 10] | (0x80 * dot_display);
		FST_FND_DIGIT_PORT = (uint8_t)~0x80;
		break;

		case 1:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 10 % 6] | (0x80 * dot_display);
		FST_FND_DIGIT_PORT = (uint8_t)~0x40;
		break;

		case 2:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 60 % 10];
		FST_FND_DIGIT_PORT = (uint8_t)~0x20;
		break;

		case 3:
		FST_FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 600 % 6];
		FST_FND_DIGIT_PORT = (uint8_t)~0x10;
		break;
	}

	digit_select = (digit_select + 1 ) % 4;

}
