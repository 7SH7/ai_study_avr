#if 0 // 내가 작성한 코드
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
			else if(!(button2_state % 2) && 1 < button2_state) stopwatch_clock();

		}
    }
}


#else	// ai랑 수정한 리펙토링..

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

// ===== [수정] 스톱워치 내부 상태를 별도 enum으로 명확히 분리 (상태도: stop / run) =====
typedef enum {SW_STOP, SW_RUN} sw_state_t;

int main(void)
{
	int button0_state=0;

	// ===== [수정 전]
	// int button1_state=0;
	// int button2_state=0;
	// ===== [수정 후] : 누적 카운트 변수 대신 stopwatch 상태 변수 1개로 대체 =====
	sw_state_t sw_state = SW_STOP;	// 상태도상 초기 상태는 stop

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

			// ===== [추가] 모드 전환 시 stopwatch 상태도 stop으로 초기화 =====
			sw_state = SW_STOP;
		}

		if(button0_state == 0)		min_sec_clock();
		else if(button0_state == 1)		sec_clock();
		else if(button0_state == 2)
		{
			// ===== [수정 전]
			// if (get_button(BUTTON1, BUTTON1PIN))
			//     button1_state++;
			// else if (get_button(BUTTON2, BUTTON2PIN))
			//     button2_state++;
			//
			// if((button1_state % 2) == 1)	stopwatch_clock();
			// else if((button1_state % 2) == 0) pause_stop_watch();
			// if(button2_state % 2)
			// {
			//     ms_count = 0;
			//     sec_count = 0;
			//     dot_display = 0;
			// }
			// else if(!(button2_state % 2) && 1 < button2_state) stopwatch_clock();

			// ===== [수정 후] : 상태도 (stop --BTN1--> run --BTN1--> stop, stop --BTN2--> reset --> run) 반영 =====
			if (get_button(BUTTON1, BUTTON1PIN))
			{
				// run <-> stop 토글
				sw_state = (sw_state == SW_RUN) ? SW_STOP : SW_RUN;
			}

			if (get_button(BUTTON2, BUTTON2PIN))
			{
				// reset: count 초기화 후 run 상태로 전환 (상태도의 reset -> run)
				ms_count = 0;
				sec_count = 0;
				dot_display = 0;
				sw_state = SW_RUN;
			}

			if (sw_state == SW_RUN)
				stopwatch_clock();
			else
				pause_stop_watch();
		}
    }
}
#endif