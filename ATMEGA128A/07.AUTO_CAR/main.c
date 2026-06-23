/*
 * 07.AUTO_CAR.c
 *
 * Created: 2026-06-22 오전 10:32:22
 * Author : kccistc
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>	// sei, cli 등등 함수 내장.
#include <stdio.h>

#include "def.h"
#include "ultrasonic.h"
#include "button.h"

extern int led_main(void);
extern void init_uart0(void);
extern void UART0_transmit(uint8_t data);
extern void pc_command_processing(void);
extern void init_ultrasonic(void);
extern void make_trigger(volatile int pin);
extern void ultrasonic_processing(volatile int *flag, volatile int pin);
extern void init_timer1_pwm(void);
extern void init_motor_driver(void);
extern void dcmotor_pwm_control_main(void);
extern void forward(int);
extern void backward(int);
extern void turn_left(int);
extern void turn_right(int);
extern void stop(void);
//extern void find_display_FST(uint32_t sec_count, uint32_t dot_display);
extern void find_display_FST(uint32_t sec_count, uint32_t dot_display, int car_direction);
extern void min_sec_clock();
extern int get_button(int button_num, int button_pin);
extern void init_button(void);
extern void init_timer0(void);
extern void init_led(void);
extern void init_fnd(void);
extern volatile uint8_t data;
extern void run_stop_watch(uint32_t sec_count, uint32_t ms_count, int car_direction);
extern void car_status_cnt(int car_direction);
extern void find_display_SND(int car_direction);

extern volatile int ultrasonic_distance_l;
extern volatile int ultrasonic_distance_c;
extern volatile int ultrasonic_distance_r;
extern volatile int flag_l;
extern volatile int flag_c;
extern volatile int flag_r;

void manual_mode(void);
void auto_mode(void);
void auto_mode_check(void);
void distance_check(void);

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);	

volatile uint32_t sec_count = 0;
volatile uint32_t dot_display = 0;
volatile uint32_t ms = 0;

int func_state = MANUAL_MODE;
volatile int is_auto = 0;

void (*fp_mode[])(void) = {
	manual_mode,
	auto_mode,
	auto_mode_check,
	distance_check
};

typedef enum { CAR_FORWARD, CAR_LEFT, CAR_RIGHT, CAR_STOP, CAR_BACK } car_state_t;
car_state_t car_direction = CAR_STOP;

typedef enum {
	LEFT_TRIG_PIN,
	CENTER_TRIG_PIN,
	RIGHT_TRIG_PIN
}sensor_step_t;

volatile sensor_step_t sensor_step = 0;

void manual_mode(void)
{
	switch(data)
	{
		case 'F':
		case 'f':
			forward(500);	// speed를 넘겨줌. 4us * 500 = 0.002sec(2ms)
			break;

		case 'B':
		case 'b':
			backward(500);
			break;

		case 'L':
		case 'l':
			turn_left(700);	// 2.8ms
			break;

		case 'R':
		case 'r':
			turn_right(700);
			break;
		
		case 'S':
		case 's':
			stop();
			break;

		default:
			break;
	}
}

void auto_mode(void)
{
	switch(car_direction)
	{
		case CAR_FORWARD: forward(400); break;
		case CAR_LEFT:    turn_left(600); break;
		case CAR_RIGHT:   turn_right(600); break;
		case CAR_BACK:	  backward(400); break;
		case CAR_STOP:    stop(); break;
	}
}

#define HOLD_CYCLES_BACK  60
#define HOLD_CYCLES_TURN  30
volatile int hold_count = 0;

// study todo: 확실히 상태를 enum처리하는 것이 더 처리하기 좋다
void auto_mode_check(void)
{
    printf("L=%d C=%d R=%d\r\n",
    ultrasonic_distance_l,
    ultrasonic_distance_c,
    ultrasonic_distance_r);

    if(hold_count > 0)
    {
	    hold_count--;
	    return;   // 아직 이전 방향 유지
    }

    if(ultrasonic_distance_c < 15)
    {
	    car_direction = CAR_BACK;
	    hold_count = HOLD_CYCLES_BACK;
		car_status_cnt(car_direction);
    }
    else if(ultrasonic_distance_l < 16)
    {
	    car_direction = CAR_RIGHT;
	    hold_count = HOLD_CYCLES_TURN;
		car_status_cnt(car_direction);
    }
    else if(ultrasonic_distance_r < 14)
    {
	    car_direction = CAR_LEFT;
	    hold_count = HOLD_CYCLES_TURN;
		car_status_cnt(car_direction);
    }
    else
    {
	    car_direction = CAR_FORWARD;
		car_status_cnt(car_direction);
    }
}


void distance_check(void)
{
	switch(sensor_step)
	{	
		case 0:
			make_trigger(LEFT_TRIG_PIN);
			sensor_step = 1;
			break;

		case 1:
		if(flag_l)
		{
			flag_l = 0;

			make_trigger(CENTER_TRIG_PIN);
			sensor_step = 2;
		}
		break;

		case 2:
		if(flag_c)
		{
			flag_c = 0;

			make_trigger(RIGHT_TRIG_PIN);
			sensor_step = 3;
		}
		break;

		case 3:
		if(flag_r)
		{
			flag_r = 0;

			sensor_step = 0;
		}

		break;
	}
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;	// TCNT0 6~256: 250개 pulse count 하기 위해

	if(is_auto)
	{
		ms++;
		find_display_FST(sec_count, dot_display,car_direction);
		
		if(1000 <= ms)
		{
			sec_count++;
			ms=0;
			dot_display = !dot_display;
		}
		
	}
}

int main(void)
{
	// want to do : 500ms 주기로 바뀌도록 하기
	init_led();
	init_timer0();
	init_uart0();
	init_fnd();
	init_button();

	sei();		// 전역(대문) interrupt 허용

	init_motor_driver();
	init_timer1_pwm();
	init_ultrasonic();

	stdout = &OUTPUT;	// printf가 동작할 수 있도록 stdout을 설정
	
    while (1) 
    {
		fp_mode[func_state]();
		
		if(get_button(BUTTON, BUTTONPIN)) 
		{	
			func_state = func_state == 1 ? 0 : 1;
			if(func_state == MANUAL_MODE) stop();
		}
		
		
		if(func_state == AUTO_MODE)
		{
			is_auto = 1;
			distance_check();
	
			if(sensor_step == 0)
			{
				auto_mode_check();
				auto_mode();
			}
		}
		else if(func_state == MANUAL_MODE)
		{
			is_auto = 0;
			run_stop_watch(sec_count, ms, car_direction);
		}
	}
}


void init_timer0(void)
{
	TCNT0 = 6;	// TCNT0 0~256 : 250개 pulse count 위해

	TCCR0 &= ~(1 << CS02 | 1 << CS01 | 1 << CS00);	// 0분주
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;	// 64분주
	
	TIMSK |= 1 << TOIE0;	// TIMER0 Overflow INT
}
