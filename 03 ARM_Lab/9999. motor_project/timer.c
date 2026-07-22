#include "device_driver.h"

#define TIM2_TICK		20						// usec
#define TIM2_FREQ		(1000000. / TIM2_TICK)	// Hz
#define TIM2_1ms_Pls	(TIM2_FREQ / 1000.)		// 1ms에 생성하는 pulse 수
#define TIM2_MAX		(0xFFFFFFFF)

#define TIM4_TICK	TIM2_TICK
#define TIM4_FREQ	TIM2_FREQ
#define TIM4_1ms_Pls	TIM2_1ms_Pls
#define TIM4_MAX	(0xFFFF)

#define TIM5_FREQ		(1000000)						// Hz
#define TIM5_TICK		(1000000. / TIM5_FREQ)		// usec
#define TIM5_1ms_Pls	(TIM4_FREQ / 1000.)			// 1 ms 당 pulse 갯수
#define TIM5_MAX		(0xffffffff)

void TIM2_Stopwatch_Start(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2 -> CR1 = (0x0 << 7) | (0x1 << 4) | (0x1 << 3) | (0x0 << 0);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2 -> PSC = (int)(TIMXCLK / TIM2_FREQ + 0.5) - 1;
	// ARR 초기값 설정 => 최대값 0xFFFF 설정
	TIM2 -> ARR = 0xffff;
	// UG 이벤트 발생
	TIM2 -> EGR |= 0x1 << 0;
	// TIM2 start
	TIM2 -> CR1 |= 0x1 << 0;

}

unsigned int TIM2_Stopwatch_Stop(void)
{
	unsigned int time;

	// TIM2 stop
	TIM2 -> CR1 &= ~(0x1 << 0);
	// CNT 초기 설정값 (0xffff)와 현재 CNT의 펄스수 차이를 구하고
	// 그 펄스수 하나가 20usec이므로 20을 곱한값을 time에 저장
	time = ((TIM2 -> ARR) - (TIM2 -> CNT)) * TIM2_TICK;
	// 계산된 time 값을 리턴(단위는 usec)
	return time;

}

void TIM2_Delay(int time)
{
	unsigned int pls = TIM2_1ms_Pls * time;
	int n = pls / TIM2_MAX;
	int m = pls % TIM2_MAX;
	int i;

	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	// UG 이벤트 발생

	// UIF(Update Interrupt Pending) Clear
	// TIM2 start
	// Wait timeout

	TIM2 -> CR1 = (0x0 << 7) | (0x1 << 4) | (0x1 << 3) | (0x0 << 0);
	TIM2 -> PSC = (int)(TIMXCLK / TIM2_FREQ + 0.5) - 1;

	for(i = 0; i < n; i ++)
	{
		TIM2 -> ARR = TIM2_MAX;
		TIM2 -> EGR |= 0x1 << 0;
		TIM2 -> SR &= ~(0x1 << 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(!Macro_Check_Bit_Set(TIM2 -> SR, 0));
		TIM2 -> SR &= ~(0x1 << 0);

		Macro_Clear_Bit(TIM2->CR1, 0);
	}

	TIM2 -> ARR = m;	// time 단위: msec, TIM2_1ms_Pls 단위 : Hz
	TIM2 -> EGR |= 0x1 << 0;

	TIM2 -> SR &= ~(0x1 << 0);
	Macro_Set_Bit(TIM2->CR1, 0);
	while(!Macro_Check_Bit_Set(TIM2 -> SR, 0));
	TIM2 -> SR &= ~(0x1 << 0);

	// TIM2 Stop
	Macro_Clear_Bit(TIM2->CR1, 0);
}

void TIM4_Repeat(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	TIM4 -> CR1 = (0x0 << 7) | (0x1 << 4) | (0x0 << 3) | (0x0 << 0);
	TIM4 -> PSC = (int)(TIMXCLK / TIM4_FREQ + 0.5) - 1;
	TIM4 -> ARR = (int) (time * TIM4_1ms_Pls);
	TIM4 -> EGR |= (0x1 << 0);
	TIM4 -> SR &= ~(0x1 << 0);
	Macro_Set_Bit(TIM4->CR1, 0);
	// TIM4 CR1: ARPE=0, down counter, repeat mode
	// PSC(50KHz),  ARR(reload시 값) 설정
	// UG 이벤트 발생
	// Update Interrupt Pending Clear
	// TIM4 start

}

void TIM4_1Pls(int time)
{
    Macro_Set_Bit(RCC->APB1ENR, 2);

    // TIM2 CR1 설정: down count, one pulse
    TIM4->CR1 = (0x1 << 4)|(0x1 << 3) | (0x0 << 0);
    // PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
    TIM4->PSC = (int)(TIMXCLK/TIM2_FREQ + 0.5) - 1;
    // ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
    TIM4->ARR = (int)(TIM2_1ms_Pls * time);
    // UG 이벤트 발생
    Macro_Set_Bit(TIM4->EGR, 0);

    // UIF(Update Interrupt Pending) Clear
    Macro_Clear_Bit(TIM4->SR, 0);
    // TIM2 start
    Macro_Set_Bit(TIM4->CR1, 0);
}

int TIM4_Check_Timeout(void)
{
	// 타이머가 timeout 이면 1 리턴, 아니면 0 리턴
	if(Macro_Check_Bit_Set(TIM4 -> SR, 0))
	{
		TIM4 -> SR &= ~(0x1 << 0);
		return 1;
	}

	return 0;

}

void TIM4_Stop(void)
{
	Macro_Clear_Bit(TIM4->CR1, 0);
}

void TIM4_Change_Value(int time)
{
	TIM4->ARR = 50 * time;
}
#if 0
void TIM2_Oneshot(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2 -> CR1 = (0x0 << 7) | (0x1 << 4) | (0x1 << 3) | (0x0 << 0);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2 -> PSC = (int)(TIMXCLK / TIM2_FREQ + 0.5) - 1;
	// ARR 초기값 설정 => 최대값 0xFFFF 설정
	TIM2 -> ARR = (int)(TIM2_1ms_Pls * time + 0.5);
	// UG 이벤트 발생
	TIM2 -> EGR |= 0x1 << 0;

	TIM2 -> SR &= ~(0x1 << 0);
	// TIM2 start
	TIM2 -> CR1 |= 0x1 << 0;

}
#endif

void TIM2_1Pls(int time)
{
    Macro_Set_Bit(RCC->APB1ENR, 0);

    // TIM2 CR1 설정: down count, one pulse
    TIM2->CR1 = (0x1 << 4)|(0x1 << 3) | (0x0 << 0);
    // PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
    TIM2->PSC = (int)(TIMXCLK/TIM2_FREQ + 0.5) - 1;
    // ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
    TIM2->ARR = (int)(TIM2_1ms_Pls * time);
    // UG 이벤트 발생
    Macro_Set_Bit(TIM2->EGR, 0);

    // UIF(Update Interrupt Pending) Clear
    Macro_Clear_Bit(TIM2->SR, 0);
    // TIM2 start
    Macro_Set_Bit(TIM2->CR1, 0);
}

int TIM2_Check_Timeout(void)
{
    // 타이머가 timeout 이면 1 리턴, 아니면 0 리턴
    if(Macro_Check_Bit_Set(TIM2->SR, 0))
    {
        Macro_Clear_Bit(TIM2->SR, 0);
        return 1;
    } else
    {
        return 0;
    }
}

void TIM2_Stop(void)
{
    Macro_Clear_Bit(TIM2->CR1, 0);
}

void TIM5_Out_Init(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 3);

	Macro_Write_Block(GPIOA->MODER, 0xf, 0xa, 0);  	// PB0 => ALT
	Macro_Write_Block(GPIOA->AFR[0], 0xff, 0x22, 0); 	// PB0 => AF02

	Macro_Write_Block(TIM5->CCMR1,0xffff, 0x6060, 0);
	TIM5->CCER = (0x1<<4)|(0x1<<0);
}


void TIM5_Out_PWM_Generation(unsigned short freq, int duty, int a0, int a1)
{
	TIM5->CCER = (0x1<<4)|(0x1<<0);
	TIM5 -> CR1 |= (0x0 << 7) | (0x1 << 4) | (0x0 << 3) | (0x0 << 0);
	// Timer 주파수가 TIM3_FREQ가 되도록 PSC 설정
	TIM5 -> PSC = (int)((double)TIMXCLK / TIM5_FREQ + 0.5) - 1;
	// 요청한 주파수가 되도록 ARR 설정
	TIM5 -> ARR = (int)((double)(TIM5_FREQ / freq) + 0.5);
	// Duty Rate 50%가 되도록 CCR3 설정
	TIM5 -> CCR1 = (int)((TIM5 -> ARR) * a0 * (duty / 100.));
	TIM5 -> CCR2 = (int)((TIM5 -> ARR) * a1 * (duty / 100.));
	// Manual Update(UG 발생)
	TIM5 -> EGR |= 0x1 << 0;
	// Down Counter, Repeat Mode, Timer Start
	TIM5 -> CR1 |= (0x1 << 0);

}

void TIM5_Out_Stop(void)
{
	Macro_Clear_Bit(TIM5->CR1, 0);
}