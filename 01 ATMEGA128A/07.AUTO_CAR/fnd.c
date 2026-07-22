/*
 * fnd.c
 *
 * Created: 2026-06-12 오전 10:46:18
 *  Author: kccistc
 */ 

#include "fnd.h"
#include <avr/interrupt.h>	

void init_fnd(void);
void find_display_FST(uint32_t sec_count, uint32_t dot_display, int car_direction);
int fnd_main(void);
void display_min_sec_dot(void);
void min_sec_clock();
void sec_clock();
void find_sec_clock(uint32_t sec_count, uint32_t dot_display);
void stopwatch_clock();
void run_stop_watch(uint32_t sec_count, uint32_t ms_count, int car_direction);	// PC7번이 1초 단위로 ON/OFF되도록

void pause_stop_watch();
void reset_stop_watch();

void time_set_fnd(int min_time);
void fnd_all_off(void);

int wash_running_express_fnd(int wash_time);

extern volatile uint32_t ms;
extern volatile uint32_t sec_count;	
extern volatile uint32_t dot_display;

/*
typedef enum { CAR_FORWARD, CAR_LEFT, CAR_RIGHT, CAR_STOP, CAR_BACK } car_state_t;
car_state_t car_direction = CAR_STOP;
car_direction_cnt[0] : forward
car_direction_cnt[1] : left
car_direction_cnt[2] : right
car_direction_cnt[3] : stop
car_direction_cnt[4] : back
*/
int car_direction_cnt[5] = {0,};	
void car_status_cnt(int car_direction);

void find_display_SND();


void init_fnd(void)
{
	// 두 개 FND에 대해 모두 초기화
	FND_DATA_DDR = 0xff; 
		
	PORTC |= 0xff;	// 출력 모드로 설정
	FND_DIGIT_DDR |= 1 << FST_FND_DIGIT_D1 | 1 << FST_FND_DIGIT_D2 | 1 << FST_FND_DIGIT_D3 | 1 << FST_FND_DIGIT_D4 | 1 << SND_FND_DIGIT_D1 | 1 << SND_FND_DIGIT_D2 | 1 << SND_FND_DIGIT_D3 | 1 << SND_FND_DIGIT_D4;

	
	FND_DATA_PORT = ~0xff;

}

void find_display_FST(uint32_t sec_count, uint32_t dot_display, int car_direction)
{
	static uint8_t find_font[] = {
		~0b11000000, ~0b11111001, ~0b10100100, ~0b10110000,
		~0b10011001, ~0b10010010, ~0b10000010, ~0b11011000,
		~0b10000000, ~0b10011000, ~0b01111111
	};

	// F       L       r       S       b
	static uint8_t car_status_font[] = {
		~0b10001110, ~0b11000111, ~0b10101111, ~0b10010010, ~0b00000011
	};

	static int digit_select = 0;

	// 전체 끄기 + 데이터 클리어
	PORTC = 0xff;
	FND_DATA_PORT = 0x00;

	switch(digit_select) {
		// FST FND 분초타이머 (PC0~PC3)
		case 0:
		FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count % 10];
		PORTC &= ~(1 << FST_FND_DIGIT_D4);
		break;
		case 1:
		FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 10 % 6];
		PORTC &= ~(1 << FST_FND_DIGIT_D3);
		break;
		case 2:
		FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 60 % 10] | (0x80 * dot_display);
		PORTC &= ~(1 << FST_FND_DIGIT_D2);
		break;
		case 3:
		FND_DIGIT_PORT = 0xff;
		FND_DATA_PORT = find_font[sec_count / 600 % 6];
		PORTC &= ~(1 << FST_FND_DIGIT_D1);
		break;

		// SND FND 방향표시 (PC4~PC7) - 1자리만 사용
		case 4:
			FND_DATA_PORT = car_status_font[car_direction];
			PORTC &=  ~(1 << SND_FND_DIGIT_D4);  // PC5만 LOW
			break;

		case 5:
			FND_DATA_PORT = car_status_font[car_direction];
			PORTC &= ~(1 << SND_FND_DIGIT_D3);  // PC5만 LOW
			break;

		case 6:

			FND_DATA_PORT = car_status_font[car_direction];
			PORTC &= ~(1 << SND_FND_DIGIT_D2);  // PC5만 LOW
			break;

		case 7:
			FND_DATA_PORT = car_status_font[car_direction];
			PORTC &= ~(1 << SND_FND_DIGIT_D1);  // PC5만 LOW
		break;
	}

	digit_select = (digit_select + 1) % 8;
}

void run_stop_watch(uint32_t sec_count, uint32_t ms, int car_direction)	
{
	//  0      1 	 2	   3	 4	   5 	 6 	      7      8	    9
	static uint8_t find_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0, ~0x99, ~0x92, ~0x82, ~0xd8, ~0x80, ~0x98, ~0x7f};	// common cathode

	static uint8_t car_status_font[] = {
		~0b10001110, ~0b11000111, ~0b10101111, ~0b10010010, ~0b00000011
	};

	static int digit_select = 0;	// 자리수 선택

	FND_DIGIT_PORT = 0xff;
	
	switch(digit_select) {
		case 0:
		FND_DATA_PORT = find_font[sec_count % 10]; 
		FND_DIGIT_PORT &= (uint8_t)~(1 << FST_FND_DIGIT_D4);
		break;

		case 1:
		FND_DATA_PORT = find_font[sec_count / 10 % 6];
		FND_DIGIT_PORT &= (uint8_t)~(1 << FST_FND_DIGIT_D3);
		break;

		case 2:
		FND_DATA_PORT = find_font[sec_count / 60 % 10] | (0x80 * dot_display);;
		FND_DIGIT_PORT &= (uint8_t)~(1 << FST_FND_DIGIT_D2);
		break;

		case 3:
		FND_DATA_PORT = find_font[sec_count / 600 % 6];
		FND_DIGIT_PORT &= (uint8_t)~(1 << FST_FND_DIGIT_D1);
		break;
		
/*
car_direction_cnt[0] : forward 횟수!
car_direction_cnt[1] : left
car_direction_cnt[2] : right
car_direction_cnt[3] : stop
car_direction_cnt[4] : back
*/
			
		// SND FND 방향표시 (PC4~PC7) - 1자리만 사용
		// FORWARD
		case 4:
		FND_DATA_PORT = find_font[car_direction_cnt[0]];
		PORTC &=  ~(1 << SND_FND_DIGIT_D4);  // PC5만 LOW
		break;

		// BACKWARD
		case 5:
		FND_DATA_PORT = find_font[car_direction_cnt[4]];
		PORTC &= ~(1 << SND_FND_DIGIT_D3);  // PC5만 LOW
		break;

		// LEFT
		case 6:
		FND_DATA_PORT = find_font[car_direction_cnt[1]];
		PORTC &= ~(1 << SND_FND_DIGIT_D2);  // PC5만 LOW
		break;

		// RIGHT
		case 7:
		FND_DATA_PORT = find_font[car_direction_cnt[2]];
		PORTC &= ~(1 << SND_FND_DIGIT_D1);  // PC5만 LOW
		break;
	}
	
	digit_select = (digit_select + 1 ) % 8;
}

void car_status_cnt(int car_direction)
{	
	switch (car_direction){
		case 0:
			car_direction_cnt[car_direction]++;
			break;
		
		case 1:
			car_direction_cnt[car_direction]++;
			break;
		
		case 2:
			car_direction_cnt[car_direction]++;
			break;
		
		case 3:
			car_direction_cnt[car_direction]++;
			break;
		
		case 4:
			car_direction_cnt[car_direction]++;
			break;
	}
}
