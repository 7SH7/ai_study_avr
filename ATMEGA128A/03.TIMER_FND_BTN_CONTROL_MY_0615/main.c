#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"
#include "fnd.h"

extern void init_fnd(void);
extern void init_button(void);
extern int	get_button(int button_num, int button_pin);
extern void min_sec_clock();
extern void sec_clock();
extern void stopwatch_clock();
extern void run_stop_watch(uint32_t sec_count, uint32_t ms_count);
extern void pause_stop_watch();
extern void reset_stop_watch();

typedef enum {SW_STOP, SW_RUN} sw_state_t;

volatile uint32_t ms_count = 0;

ISR(TIMER2_OVF_vect)
{
	TCNT2 = 194;
	//TCNT2 = 6;
	ms_count++;
}

void init_timer2(void)
{
	TCNT2 = 194;
	//TCNT2 = 6;
	TCCR2 = 0x00;
	//TCCR2 |= 0 << CS22 | 1 << CS21 | 1 << CS20;	// 64분주
	TCCR2 |= 1 << CS22 | 0 << CS21 | 0 << CS20;	// 256분주
	TIMSK |= 1 << TOIE2;	// TIMER2 Overflow INT
	
	sei();
}

int main(void)
{
	int button0_state = 0;
	int button2_cnt = 0;
	sw_state_t sw_state = SW_STOP;

	init_button();
	init_fnd();
	init_timer2();

	while (1)
	{
		if (get_button(BUTTON0, BUTTON0PIN))
		{
			cli();
			ms_count = 0;	// 공유되는 값 보존을 위해..
			sei();
			sec_count = 0;
			dot_display = 0;
			button0_state = (button0_state + 1) % 3;
			sw_state = SW_STOP;
		}
		if(button0_state == 0)		min_sec_clock();
		else if(button0_state == 1)		sec_clock();
		else if(button0_state == 2)
		{
			if (get_button(BUTTON1, BUTTON1PIN))
			{
				sw_state = (sw_state == SW_RUN) ? SW_STOP : SW_RUN;
			}
			if (get_button(BUTTON2, BUTTON2PIN))
			{
				if(button2_cnt == 0)
				{
					ms_count = 0;
					sec_count = 0;
					dot_display = 0;
					sw_state = SW_STOP;
					button2_cnt = 1;
				}
				else
				{
					sw_state = SW_RUN;
					button2_cnt = 0;
				}
			}
			
			if (sw_state == SW_RUN){
				sei();
				stopwatch_clock();
			}
			else{				
				cli();	
				pause_stop_watch();
			}
		}
	}
}