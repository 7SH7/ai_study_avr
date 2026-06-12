/*
 * fnd.c
 *
 * Created: 2026-06-12 오전 10:46:18
 *  Author: kccistc
 */ 

#include "fnd.h"

void init_fnd(void);
void find_display(uint32_t sec_count, uint32_t dot_display);
int fnd_main(void);
void display_min_sec_dot(void);
void min_sec_clock();
void sec_clock();
void find_sec_clock(uint32_t sec_count, uint32_t dot_display);
void stopwatch_clock();
void run_stop_watch(uint32_t sec_count, uint32_t ms_count);	// PC7번이 1초 단위로 ON/OFF되도록

void pause_stop_watch();
void reset_stop_watch();


uint32_t ms_count = 0;	// ms를 측정하는 count uint32_t: unsigned int
uint32_t sec_count = 0;	// sec를 측정하는 count uint32_t: unsigned int
uint32_t dot_display = 0;


void pause_stop_watch(){
	run_stop_watch(sec_count, ms_count);
	_delay_ms(1);
};
	

void stopwatch_clock(){
	run_stop_watch(sec_count, ms_count);
	_delay_ms(1);
	
	ms_count++;
	if(ms_count >= 1000)
	{
		ms_count=0;
		sec_count++;
		dot_display = !dot_display;
	}
}

void min_sec_clock()
{	
	find_display(sec_count, dot_display);
	_delay_ms(1);
	
	ms_count++;	
	if(ms_count >= 1000)
	{
		ms_count=0;
		sec_count++;
		dot_display = !dot_display;		
	}
}

void sec_clock(void)
{
	find_sec_clock(sec_count, dot_display);
	_delay_ms(1);
	
	ms_count++;
	if(ms_count >= 1000)
	{
		ms_count=0;
		sec_count++;
		dot_display = !dot_display;
	}

}

void init_fnd(void)
{
	FND_DATA_DDR = 0xff;	// 출력 모드로 설정
	FND_DIGIT_DDR |= 1 << FND_DIGIT_D1 | 1 << FND_DIGIT_D2 | 1 << FND_DIGIT_D3 | 1 << FND_DIGIT_D4;
	
	// FND 전체 off 하는 작업
#if 0	// Common Anode (양극)
	FND_DATA_PORT = 0xff;

#else	// Common Cathode (음극)
	FND_DATA_PORT = ~0xff;

#endif

}

void find_display(uint32_t sec_count, uint32_t dot_display)	// PC7번이 1초 단위로 ON/OFF되도록
{	
#if 0						 
	// 각 숫자를 띄우려면, 다음 값이 필요하다. 그래서 그걸 배열로 지정해준 것
							//  0     1 	 2	   3	 4	   5 	 6 	   7	8	  9
	uint8_t find_font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98, 0x7f};	// common anode
		
#else	
   						    //  0      1 	 2	   3	 4	   5 	 6 	      7      8	    9
	uint8_t find_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0, ~0x99, ~0x92, ~0x82, ~0xd8, ~0x80, ~0x98, ~0x7f};	// common cathode

#endif
	
	static int digit_select = 0;	// 자리수 선택
	
	switch (digit_select)
	{
		case 0:  // FND쪽 1단위 (제일 첫번째 숫자)
			#if 0 // common anode
			FND_DIGIT_PORT= 0X80;	// 0100 0000		
			# else // common cathode
			FND_DIGIT_PORT = ~0X80;	// 1011 1111
			#endif
			FND_DATA_PORT =  find_font[sec_count % 10] | (0x80 * dot_display) ;	// 0 ~ 9
			break;

		case 1:	// FND쪽 10단위
			#if 0 // common anode
			FND_DIGIT_PORT= 0X40;	
			# else // common cathode
			FND_DIGIT_PORT = ~0X40;	
			#endif
			FND_DATA_PORT =  find_font[sec_count / 10 % 6] | (0x80 * dot_display) ;	// 0 ~ 59
			break;


		case 2: // FND쪽 100단위
			#if 0 // common anode
			FND_DIGIT_PORT= 0X20;
			# else // common cathode
			FND_DIGIT_PORT = ~0X20;
			#endif
			FND_DATA_PORT =  find_font[sec_count / 60 % 10];
			
			break;

		case 3:  // FND쪽 1000단위
			#if 0 // common anode
			FND_DIGIT_PORT= 0X10;
			# else // common cathode
			FND_DIGIT_PORT = ~0X10;
			#endif
			FND_DATA_PORT =  find_font[sec_count / 600 % 6];
			//FND_DATA_PORT =  find_font[10];	// 0 ~ 59
			break;
	}
	digit_select = (digit_select + 1 ) % 4;
}

void find_sec_clock(uint32_t sec_count, uint32_t dot_display)	// PC7번이 1초 단위로 ON/OFF되도록
{
	#if 0
	// 각 숫자를 띄우려면, 다음 값이 필요하다. 그래서 그걸 배열로 지정해준 것
	//  0     1 	 2	   3	 4	   5 	 6 	   7	8	  9
	uint8_t find_font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98, 0x7f};	// common anode
	
	#else
	//  0      1 	 2	   3	 4	   5 	 6 	      7      8	    9
	uint8_t find_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0, ~0x99, ~0x92, ~0x82, ~0xd8, ~0x80, ~0x98, ~0x7f};	// common cathode

	#endif
	
	uint8_t third_num[] = {0x08, 0x06, 0x01, 0x00, 0x00, 0x00};
	uint8_t fourth_num[] = {0x00, 0x00, 0x00, 0x01, 0x30, 0x08};
	
	static int digit_select = 0;	// 자리수 선택
	
	switch (digit_select)
	{
		case 0:  // FND쪽 1단위 (제일 첫번째 숫자)
		#if 0 // common anode
		FND_DIGIT_PORT= 0X80;	// 0100 0000
		# else // common cathode
		FND_DIGIT_PORT = ~0X80;	// 1011 1111
		#endif
		FND_DATA_PORT =  find_font[sec_count % 10];
		break;

		case 1:	// FND쪽 10단위
		#if 0 // common anode
		FND_DIGIT_PORT= 0X40;
		# else // common cathode
		FND_DIGIT_PORT = ~0X40;
		#endif
		FND_DATA_PORT =  find_font[sec_count / 10 % 6]; 
		break;


		case 2: // FND쪽 100단위
		#if 0 // common anode
		FND_DIGIT_PORT= 0X20;
		# else // common cathode
		FND_DIGIT_PORT = ~0X20;
		#endif
		FND_DATA_PORT =  third_num[sec_count % 6];
		break;

		case 3:  // FND쪽 1000단위
		#if 0 // common anode
		FND_DIGIT_PORT= 0X10;
		# else // common cathode
		FND_DIGIT_PORT = ~0X10;
		#endif
		FND_DATA_PORT =  fourth_num[sec_count % 6];
		break;
	}
	digit_select = (digit_select + 1) % 4;
}

void run_stop_watch(uint32_t sec_count, uint32_t ms_count)	// PC7번이 1초 단위로 ON/OFF되도록
{
	#if 0
	// 각 숫자를 띄우려면, 다음 값이 필요하다. 그래서 그걸 배열로 지정해준 것
	//  0     1 	 2	   3	 4	   5 	 6 	   7	8	  9
	uint8_t find_font[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x98, 0x7f};	// common anode
	
	#else
	//  0      1 	 2	   3	 4	   5 	 6 	      7      8	    9
	uint8_t find_font[] = {~0xc0, ~0xf9, ~0xa4, ~0xb0, ~0x99, ~0x92, ~0x82, ~0xd8, ~0x80, ~0x98, ~0x7f};	// common cathode

	#endif
	
	static int digit_select = 0;	// 자리수 선택
	
	switch (digit_select)
	{
		case 0:  // FND쪽 1단위 (제일 첫번째 숫자)
		#if 0 // common anode
		FND_DIGIT_PORT= 0X80;	// 0100 0000
		# else // common cathode
		FND_DIGIT_PORT = ~0X80;	// 1011 1111
		#endif
		FND_DATA_PORT =  find_font[ms_count / 10 % 10];
		break;

		case 1:	// FND쪽 10단위
		#if 0 // common anode
		FND_DIGIT_PORT= 0X40;
		# else // common cathode
		FND_DIGIT_PORT = ~0X40;
		#endif
		FND_DATA_PORT =  find_font[ms_count / 100 % 10];
		break;


		case 2: // FND쪽 100단위
		#if 0 // common anode
		FND_DIGIT_PORT= 0X20;
		# else // common cathode
		FND_DIGIT_PORT = ~0X20;
		#endif
		FND_DATA_PORT =  find_font[sec_count % 10];
		
		break;

		case 3:  // FND쪽 1000단위
		#if 0 // common anode
		FND_DIGIT_PORT= 0X10;
		# else // common cathode
		FND_DIGIT_PORT = ~0X10;
		#endif
		FND_DATA_PORT =  find_font[sec_count / 10 % 6];
		break;
	}
	digit_select = (digit_select + 1 ) % 4;
}
