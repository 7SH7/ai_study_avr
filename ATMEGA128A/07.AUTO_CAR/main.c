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

#include "button.h"
#include "led.h"
#include "washing_machine.h"

extern int get_button(int button_num, int button_pin);

extern int wash_running();
extern int rinse_running(void);
extern int spin_running(void);

extern int stop_running(void);

extern void init_button(void);
extern void init_fnd(void);
extern void init_led(void);
extern void init_timer0(void);

extern int wash_time;
extern int rinse_time;
extern int spin_time;

volatile int is_use_timer_set_status = 0;
volatile int is_use_timer_running_washmach = 0;

int current_fnd_setting_value = 0;
int current_fnd_washing_value = 0;

extern void time_set_fnd(int min_time);

enum WashingMachineStatus{
	standby_state = 0,	// 대기 모드
	wash_state,			// 세탁 모드
	rinse_state,		// 헹굼 모드
	spin_state,			// 탈수 모드
	wash_time_set,		// 세탁 시간 설정
	rinse_time_set,		// 헹굼 시간 설정
	spin_time_set		// 탈수 시간 설정
};

int main()
{
	enum WashingMachineStatus machine_state;    // 열거형 변수 선언
	machine_state = standby_state;	// 처음 기본은 대기 모드.

	sei();	
	
	init_button();
	init_fnd();
	init_led();
	init_timer0();
	init_timer3_pwm();
	init_motor_driver();
	
	while(1)
	{
		// FSM대로 상태 바꿔주기.	>> 세탁 시간 설정 안 하면, button1 눌러도 못 들어가게 하는 제약 조건 필요.
		if(get_button(BUTTON0, BUTTON0PIN))
		{
			if(machine_state == standby_state && wash_time != 0 && rinse_time != 0 && spin_time != 0)
			{
				is_use_timer_running_washmach = 1;
				machine_state = wash_state;
			}
			else if((machine_state == wash_state) || (machine_state == rinse_state) || (machine_state == spin_state))
			{
				machine_state = standby_state;
			}
		} else if(get_button(BUTTON1, BUTTON1PIN))
		{
			if(machine_state == standby_state)
			{
				machine_state = wash_time_set;
				current_fnd_setting_value = wash_time;
				is_use_timer_set_status = 1;
			}
			else if(machine_state == wash_time_set)
			{
				machine_state = rinse_time_set;
				current_fnd_setting_value = rinse_time;
			}
			else if(machine_state == rinse_time_set)
			{
				machine_state = spin_time_set;
				current_fnd_setting_value = spin_time;
			}
			else if(machine_state == spin_time_set)	    
			{
				machine_state = standby_state;
				current_fnd_washing_value = wash_time*60;
			}
		} else if(get_button(BUTTON2, BUTTON2PIN))	// 버튼 2를 누르면, 분 단위 시간 증가, 이후 버튼 1 누르면, 최종 시간으로 정해지는 거
		{
			if(machine_state == wash_time_set)
			{
				wash_time = (wash_time + 1) % 3;	// max 2
				current_fnd_setting_value = wash_time;

			}
			else if(machine_state == rinse_time_set)	
			{
				rinse_time = (rinse_time + 1) % 3;
				current_fnd_setting_value = rinse_time;
		} 
			else if(machine_state == spin_time_set)		
			{
				spin_time = (spin_time + 1) % 3;
				current_fnd_setting_value = spin_time;
			}
		}
		
		// 상태에 따른 이벤트 발생시키기 : 시간 종료로 인한 상태 변화도 만들 것
		if(machine_state == wash_state){
			if(!wash_running())
			{
				machine_state = rinse_state;
				current_fnd_washing_value = rinse_time*60;
			}
		} else if(machine_state == rinse_state)		// rinse_running() 측에서 다 마치면, 수정하는 걸로.
		{
			if(!rinse_running())
			{
				machine_state = spin_state;
				current_fnd_washing_value = spin_time*60;
			}
		} else if(machine_state == spin_state)
		{
			if(!spin_running())
			{
				machine_state = standby_state;
				led_all_off();
			}
		}
		
		if(machine_state == standby_state){
			is_use_timer_set_status = 0;
			is_use_timer_running_washmach = 0;
			led_all_off();
			stop_running();
		}
	}
}

// uart는 상태 + 남은 시간을 printf로 띄워주는 거.  + 시작 및 정지 명령 >> 아, 시작 및 정지 명령을 그 comport master로 보내는구나
