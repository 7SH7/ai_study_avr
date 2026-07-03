/*
 * 13. RTC_LCD_계산기.c
 *
 * Created: 2026-07-01 오전 9:38:26
 * Author : kccistc
 */ 

#include "lcd.h"
#include "button.h"
#include "uart0.h"
#include "queue.h"
#include "ds1307.h"
#include "button.h"
#include "keypad.h"
#include "calc.h"
#include "DS1307.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>    // sei 등 함수
#include <stdio.h>

#define TIMEOUT_MS      60000

extern void init_uart0(void);
extern void UART0_transmit(uint8_t data);

// enum으로 상태 처리 해서.. 특정 상태일때, 밑에 반복: pc 명령 처리 + read + 출력  돌아가도록..
typedef enum {
	RTC_CLOCK,
	CALCULATOR,
	RTC_CHG_MODE
} program_stat_t;
program_stat_t program_stat = RTC_CLOCK;

typedef enum {
	NOTHING,
	CHG_YY,
	CHG_MM,
	CHG_DD,
	CHG_HOUR,
	CHG_MIN,
	CHG_SEC
} chg_clock_stat_t ;
chg_clock_stat_t chg_clock_stat = NOTHING;


FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

volatile uint32_t keypad_counter = 0;
volatile uint32_t idle_counter = 0;

uint8_t MODE = 4;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	if (program_stat == CALCULATOR)
	{
		idle_counter++;
		if (++keypad_counter >= 60)
		{
			keypad_counter = 0;
			uint8_t keydata = keypad_scan();		// return 0;
			if (keydata != 0) insert_queue(keydata);
		}
	}
}

int main(void)
{
	char lcd_buf[32];
	t_ds1307 data;
	t_ds1307 *ds1307 = &data;   // main() 지역변수, while(1) 동안 계속 살아있음

	stdout = &OUTPUT;
	sei();                       // UART RX 인터럽트 쓰므로 전역 인터럽트 활성화 필수

	init_timer0();
	LCD_init();
	init_keypad();
	ds1307_init(ds1307);         // 1회 초기화

	// RTC_CLOCK, CALCULATOR, RTC_CHG_MODE
	// BTN4 딴에서는 RTC_CLOCK, CALCULATOR만 건들고
	// RTC_CHG_MODE로 들어와야 NOTHING, DATE, TIME 이렇게 움직이도록
	// DATE / TIME > BTN0(감소) / BTN1(증가)
	// NOTHING > BTN0 / BTN1 누르면 >> keypad로 날짜 입력할 수 있도록.. 
	
	// 현 문제: clk mode > chg clk mode 바꾸면 자동으로 다시 clk mode로 감.
	while (1)
	{
		// trouble shooting) btn4 배선을 안 하고 해서 이 부분에서 에러가 나서 여러번 눌러야 넘어갔다. >> 코드 실습할 때, 배선이 된 부분에 대한 코드만 넣어서 에러나지 않도록 해야함.
		if(get_button(BUTTON4, BUTTON4PIN))
		{
			program_stat = program_stat == RTC_CLOCK ? CALCULATOR : RTC_CLOCK;
			LCD_clear();
			if(program_stat== CALCULATOR) { calculator_processing('C'); idle_counter = 0; }
			_delay_ms(50);
		}

		// BTN3이 눌림 > print_chg_mode(ds1307);
		// BTN3눌린 상태에서 BTN2가 눌리면 CHG_DATE / CHG_TIME 이렇게 뜨는거.	* chg_clock_stat 사용(한번 BTN2로 오면 계속 설정 선택만. BTN3 눌렸을때 NOTHING으로 설정)
		if(get_button(BUTTON3, BUTTON3PIN) && (program_stat == RTC_CLOCK || program_stat == RTC_CHG_MODE)){	// 이땐 NOTHING
			chg_clock_stat = NOTHING;
			program_stat = program_stat == RTC_CLOCK ? RTC_CHG_MODE : RTC_CLOCK;
		} 
		if(get_button(BUTTON2, BUTTON2PIN) && program_stat == RTC_CHG_MODE){
			switch (chg_clock_stat)
			{
				// yy mm dd hh min sec
				case CHG_SEC:
					chg_clock_stat = NOTHING;
					break;
				default:
					chg_clock_stat++;
					break;
			}
		} 
		if(get_button(BUTTON0, BUTTON0PIN) && program_stat == RTC_CHG_MODE)
		{
			minus_specific_value(ds1307);
			rtc_update_flag = 1;
		} 
		if(get_button(BUTTON1, BUTTON1PIN) && program_stat == RTC_CHG_MODE)
		{
			plus_specific_value(ds1307);
			rtc_update_flag = 1;
		}

		if(program_stat == RTC_CLOCK || program_stat == RTC_CHG_MODE /* || chg_clock_stat != NOTHING */){
			ds1307_main(ds1307);	// 값 리뉴얼
			print_calendar(ds1307);
		} else if(program_stat == CALCULATOR)
		{
			// 계산기 모드 중엔 들어온 PC 명령을 그냥 비워버림 (반영 안 시키고 버림)
			while (front != rear) {
				memset((void*)rx_buff[front], 0, sizeof(rx_buff[front]));
				front = (front + 1) % QUEUE_SIZE;
			}

			cal_main(&idle_counter, TIMEOUT_MS, &program_stat);
		}
	}
}

void minus_specific_value(t_ds1307* ds1307)
{
	switch (chg_clock_stat)
	{
		case NOTHING:
			// keypad 기반으로 수정하는 기능
			break;
		case CHG_YY:
			ds1307->year--;
			break;
		case CHG_MM:
			ds1307->month--;
			break;
		case CHG_DD:
			ds1307->date--;
			break;
		case CHG_HOUR:
			ds1307->hours--;
			break;
		case CHG_MIN:
			ds1307->minutes--;
			break;
		case CHG_SEC:
			ds1307->seconds--;
			break;
	}
}

void plus_specific_value(t_ds1307* ds1307)
{
	switch (chg_clock_stat)
	{
		case NOTHING:
			// keypad 기반으로 수정하는 기능
			break;
		case CHG_YY:
			ds1307->year++;
			break;
		case CHG_MM:
			ds1307->month++;
			break;
		case CHG_DD:
			ds1307->date++;
			break;
		case CHG_HOUR:
			ds1307->hours++;
			break;
		case CHG_MIN:
			ds1307->minutes++;
			break;
		case CHG_SEC:
			ds1307->seconds++;
			break;
	}
}


void init_timer0(void)
{
	TCNT0 = 6;   // TCNT0 6~256 : 250개 펄스 count하기 위해 
	
	TCCR0 &= ~(1 << CS02 | 1 << CS01 | 1 << CS00);   // 
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;   // 64분주  
	TIMSK |= 1 << TOIE0;     // TIMER0 Overflow INT 
	
}

