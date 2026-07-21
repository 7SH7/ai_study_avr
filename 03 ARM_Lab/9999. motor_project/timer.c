#include "device_driver.h"

// magic number 줄이기  >> define 만드는 거 연습하기
#define TIM2_TICK (20)							// us
#define TIM2_FREQ (1000000. / TIM2_TICK)		// Hz
#define TIM2_1ms_Pls (TIM2_FREQ / 1000.)		// 1sec = 1000ms >> 따라서 freq / 1000
#define TIM2_MAX (0xffffU)	// U는 unsigned로 해주는. (int가 아니면, 붙여주는게 좋음)

void TIM2_Stopwatch_Start(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (0x0 << 7) | (0x1 << 4) | (0x1 << 3);	
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)	
	// 분주비: (unsigned int)(현재 CPU CLK / 내가 바꾸기를 원하는 Hz크기) 를 계산하면 나옴.
	// PSC  : PSC_buf에서 분주비를 + 1 해서 보내줌. 
	// 그래서 PSC는 - 1 을 추가로 해줘야함.
	TIM2->PSC = (unsigned int)(TIMXCLK/50000) - 1;	// 96000000 / 50000
	// ARR 초기값 설정 => 최대값 0xFFFF 설정	// ARR이 LOAD인거잖아?
	TIM2->ARR = 0xffff;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR, 0);
	// TIM2 start
	Macro_Set_Bit(TIM2->CR1, 0); // en = 1이 되면, 시작
}

unsigned int TIM2_Stopwatch_Stop(void)
{
	unsigned int time;

	// TIM2 stop
	Macro_Clear_Bit(TIM2->CR1, 0); // en = 1이 되면, 시작
	// CNT 초기 설정값 (0xffff)와 현재 CNT의 펄스수 차이를 구하고
	// 그 펄스수 하나가 20usec이므로 20을 곱한값을 time에 저장
	time = (TIM2->ARR - TIM2->CNT) * TIM2_TICK;
	// 계산된 time 값을 리턴(단위는 usec)
	return time;

}

// #define TIM2_TICK (20U)				// us  (10 -6 sec)
// #define TIM2_FREQ (1 / TIM2_TICK)	// MHz (10 6  Hz)
// 1msec 만들때 필요한 시간 * msec

#if 0
void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (0x1 << 4) | (0x1 << 3);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)  
	TIM2->PSC = (unsigned int)((TIMXCLK/TIM2_FREQ) + 0.5) - 1;	// 
	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	TIM2->ARR = time * TIM2_1ms_Pls;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR, 0);

	// UIF(Update Interrupt Pending) Clear	// 수동 flag의 경우, 반드시 clear 한 다음, 사용하기.
	Macro_Clear_Bit(TIM2->SR, 0);			// pending..
	// TIM2 start
	Macro_Set_Bit(TIM2->CR1, 0);
	// Wait timeout
	while(!Macro_Check_Bit_Set(TIM2->SR, 0));
	// TIM2 Stop
	Macro_Clear_Bit(TIM2->CR1, 0);
}
#endif

void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (0x1 << 4) | (0x1 << 3);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)  
	TIM2->PSC = (unsigned int)((TIMXCLK/TIM2_FREQ) + 0.5) - 1;	// 

	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	unsigned int pls = TIM2_1ms_Pls * time;
	int n = pls / TIM2_MAX;
	int m = pls % TIM2_MAX;
	int i;

	for(i = 0 ; i < n ; i++)
	{
		TIM2->ARR = TIM2_MAX;
		Macro_Set_Bit(TIM2->EGR,0);
		Macro_Clear_Bit(TIM2->SR, 0);			// pending..
		Macro_Set_Bit(TIM2->CR1, 0);
		while(!Macro_Check_Bit_Set(TIM2->SR, 0));
	}

	TIM2->PSC = m;
	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);			// pending..
	Macro_Set_Bit(TIM2->CR1, 0);
	while(!Macro_Check_Bit_Set(TIM2->SR, 0));

	Macro_Clear_Bit(TIM2->CR1, 0);
}


#define TIM4_TICK (20U)						// us (10 -6 cm)
#define TIM4_FRAG (1000000. / TIM4_TICK)	// Hz
#define TIM4_1MS_FLAG (TIM4_FRAG / 1000.)	// 1ms에서 frag

void TIM4_Repeat(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	// TIM4 CR1: ARPE=0, down counter, repeat mode
	TIM4->CR1 = (0x0 << 7);
	Macro_Write_Block(TIM4->CR1, 0x3, 0x2, 3);
	// PSC(50KHz),  ARR(reload시 값) 설정
	TIM4->PSC = (unsigned int)((TIMXCLK / TIM4_FRAG) + 0.5) - 1;
	TIM4->ARR = (time * TIM4_1MS_FLAG); // 여기까지 왔다가 끝.. > 반복..
	// UG 이벤트 발생
	Macro_Set_Bit(TIM4->EGR, 0);
	// Update Interrupt Pending Clear
	Macro_Clear_Bit(TIM4->SR, 0);
	// TIM4 start
	Macro_Set_Bit(TIM4->CR1, 0);
}

int TIM4_Check_Timeout(void)
{
	// 타이머가 timeout 이면 1 리턴, 아니면 0 리턴	>> flag를 clear해주고, 리턴해줘야한다.
	int res = Macro_Check_Bit_Set(TIM4->SR, 0); 
	if(res == 1)
	{
		Macro_Clear_Bit(TIM4->SR, 0);
	}
	return res;
}

void TIM4_Stop(void)
{
	Macro_Clear_Bit(TIM4->CR1, 0);
}

void TIM4_Change_Value(int time)
{
	TIM4->ARR = 50 * time;
}
