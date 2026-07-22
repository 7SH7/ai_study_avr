/*
 * timer.c
 *
 * Created: 2026-06-18 오후 6:34:56
 *  Author: kccistc
 */ 
#include "timer.h"

extern int current_fnd_setting_value;
extern int current_fnd_washing_value;
extern volatile int is_use_timer_set_status;
extern volatile int is_use_timer_running_washmach;

extern void time_set_fnd(int min_time);

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	static int ms = 0;

	if(is_use_timer_set_status)
		time_set_fnd(current_fnd_setting_value);
	else if(is_use_timer_running_washmach)
	{	
		ms++;
		wash_running_express_fnd(current_fnd_washing_value);
		if(ms >= 1000)
		{
			if(current_fnd_washing_value > 0)
				current_fnd_washing_value--;

			ms = 0;
		}
	}
	else fnd_all_off();
}


void init_timer0(void)
{
	TCNT0 = 6;	// 250개 돌아가고, 1ms로 하겠다.
	
	TCCR0 = 0x00;	// 초기화
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);	// 64분주로.
	
	TIMSK |= (1 << TOIE0);
}