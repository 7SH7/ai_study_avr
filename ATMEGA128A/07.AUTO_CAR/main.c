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
extern void init_uart1();
extern void forward(int);
extern void backward(int);
extern void turn_left(int);
extern void turn_right(int);
extern void stop(void);

extern volatile uint8_t bt_data;

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

int is_right = 0;
int is_left = 0;
int is_center = 0;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);	// printf 사용..

int func_state = MANUAL_MODE;

void (*fp_mode[])(void) = {
	manual_mode,
	auto_mode,
	auto_mode_check,
	distance_check
};

// study todo: enum 지정
typedef enum { CAR_FORWARD, CAR_LEFT, CAR_RIGHT, CAR_STOP, CAR_BACK } car_state_t;
car_state_t car_direction = CAR_STOP;

typedef enum {
	TRIG_PIN_L2,
	TRIG_PIN_C2,
	TRIG_PIN_R2
}sensor_step_t;

volatile sensor_step_t sensor_step = 0;

void manual_mode(void)
{
	switch(bt_data)
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

#define HOLD_CYCLES 50   // 튜닝 필요
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

    if(ultrasonic_distance_c < 10)
    {
	    car_direction = CAR_BACK;
	    hold_count = HOLD_CYCLES;
    }
    else if(ultrasonic_distance_l < 10)
    {
	    car_direction = CAR_RIGHT;
	    hold_count = HOLD_CYCLES;
    }
    else if(ultrasonic_distance_r < 10)
    {
	    car_direction = CAR_LEFT;
	    hold_count = HOLD_CYCLES;
    }
    else
    {
	    car_direction = CAR_FORWARD;
    }
}


void distance_check(void)
{
	switch(sensor_step)
	{
		case 0:
		make_trigger(TRIG_PIN_L2);
		sensor_step = 1;
		break;

		case 1:
		if(flag_l)
		{
			flag_l = 0;

			make_trigger(TRIG_PIN_C2);
			sensor_step = 2;
		}
		break;

		case 2:
		if(flag_c)
		{
			flag_c = 0;

			make_trigger(TRIG_PIN_R2);
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

// interrupt는 main 함수 위에 배치하는 것
/*
ISR (interrupt service routine) : 인터럽트 처리 함수 ISR로 시작
TIMER0_OVF_vect : Timer 0 overflow INT 가 발생이 되면, 이곳으로 진입함.
250개의 PULSE를 COUNT(1MS)하면 이곳으로 자동 진입한다.
ISR은 가능한 짧게 작성한다.
*/
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;	// TCNT0 6~256: 250개 pulse count 하기 위해
}

int main(void)
{
	// want to do : 500ms 주기로 바뀌도록 하기
	init_led();
	init_timer0();
	init_uart0();
	init_uart1();
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
			func_state = !func_state;
			if(func_state == MANUAL_MODE) stop();
		}
		
		
		if(func_state == AUTO_MODE)
		{
			distance_check();

			if(sensor_step == 0)
			{
				auto_mode_check();
				auto_mode();
			}
		}
    }
}

init_timer0(void)
{
	TCNT0 = 6;	// TCNT0 0~256 : 250개 pulse count 위해

	TCCR0 &= ~(1 << CS02 | 1 << CS01 | 1 << CS00);	// 0분주
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;	// 64분주
	
	TIMSK |= 1 << TOIE0;	// TIMER0 Overflow INT
	//sei();	// 전역(대문)
}
