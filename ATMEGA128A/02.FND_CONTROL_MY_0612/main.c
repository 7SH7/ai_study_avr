/*
 * 02.FND_CONTROL.c
 *
 * Created: 2026-06-12 오전 10:44:01
 * Author : kccistc
 */ 

#include <avr/io.h>
#include "button.h"
#include "fnd.h"

extern void init_fnd(void);
extern int fnd_main(void);
extern void init_button(void);
extern int	get_button(int button_num, int button_pin);

extern void min_sec_clock();
extern void sec_clock();
extern void stopwatch_clock();

extern void run_stop_watch(uint32_t sec_count, uint32_t ms_count);
extern void pause_stop_watch();
extern void reset_stop_watch();


int main(void)
{

	int button0_state=0;
	int button1_state=0;
	int button2_state=0;
	init_button();
	init_fnd();
	
    while (1) 
    {
		if (get_button(BUTTON0, BUTTON0PIN))
		{
			ms_count = 0;
			sec_count = 0;
			dot_display = 0;
			button0_state = (button0_state + 1) % 3;
		}

		if(button0_state == 0)		min_sec_clock();
		else if(button0_state == 1)		sec_clock();
		else if(button0_state == 2)
		{
			if (get_button(BUTTON1, BUTTON1PIN))
				button1_state++;


			else if (get_button(BUTTON2, BUTTON2PIN)) 
				button2_state++;

					
			if((button1_state % 2) == 1)	stopwatch_clock();
			else if((button1_state % 2) == 0) pause_stop_watch();

			if(button2_state % 2)
			{
				ms_count = 0;
				sec_count = 0;
				dot_display = 0;
			} 
			else if((!button2_state % 2) && 1 < button2_state) stopwatch_clock();

		}
    }
}

