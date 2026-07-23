#include "device_driver.h"

#define TIM2_TICK         	(20) 				// usec
#define TIM2_FREQ 	  		(1000000/TIM2_TICK)	// Hz
#define TIME2_PLS_OF_1ms  	(1000/TIM2_TICK)
#define TIM2_MAX	  		(0xffffu)

#define TIM4_TICK	  		(20) 				// usec
#define TIM4_FREQ 	  		(1000000/TIM4_TICK) // Hz
#define TIME4_PLS_OF_1ms  	(1000/TIM4_TICK)
#define TIM4_MAX	  		(0xffffu)

void TIM2_Stopwatch_Start(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->PSC = (unsigned int)(TIMXCLK/50000.0 + 0.5)-1;
	TIM2->ARR = TIM2_MAX;

	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Set_Bit(TIM2->CR1, 0);
}

unsigned int TIM2_Stopwatch_Stop(void)
{
	unsigned int time;

	Macro_Clear_Bit(TIM2->CR1, 0);
	time = (TIM2_MAX - TIM2->CNT) * TIM2_TICK;
	return time;
}

/* Delay Time Max = 65536 * 20use = 1.3sec */

#if 0

void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->PSC = (unsigned int)(TIMXCLK/(double)TIM2_FREQ + 0.5)-1;
	TIM2->ARR = TIME2_PLS_OF_1ms * time;

	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);

	while(Macro_Check_Bit_Clear(TIM2->SR, 0));

	Macro_Clear_Bit(TIM2->CR1, 0);
}

#else

/* Delay Time Extended */

void TIM2_Delay(int time)
{
	int i;
	unsigned int t = TIME2_PLS_OF_1ms * time;

	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->PSC = (unsigned int)(TIMXCLK/(double)TIM2_FREQ + 0.5)-1;
	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->ARR = 0xffff;
	Macro_Set_Bit(TIM2->EGR,0);

	for(i=0; i<(t/0xffffu); i++)
	{
		Macro_Set_Bit(TIM2->EGR,0);
		Macro_Clear_Bit(TIM2->SR, 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(Macro_Check_Bit_Clear(TIM2->SR, 0));
	}

	TIM2->ARR = t % 0xffffu;
	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);
	while (Macro_Check_Bit_Clear(TIM2->SR, 0));

	Macro_Clear_Bit(TIM2->CR1, 0);
}

#endif

void TIM4_Repeat(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	TIM4->CR1 = (1<<4)|(0<<3);
	TIM4->PSC = (unsigned int)(TIMXCLK/(double)TIM4_FREQ + 0.5)-1;
	TIM4->ARR = TIME4_PLS_OF_1ms * time - 1;

	Macro_Set_Bit(TIM4->EGR,0);
	Macro_Clear_Bit(TIM4->SR, 0);
	Macro_Set_Bit(TIM4->CR1, 0);
}

int TIM4_Check_Timeout(void)
{
	if(Macro_Check_Bit_Set(TIM4->SR, 0))
	{
		Macro_Clear_Bit(TIM4->SR, 0);
		return 1;
	}
	else
	{
		return 0;
	}
}

void TIM4_Stop(void)
{
	Macro_Clear_Bit(TIM4->CR1, 0);
}

void TIM4_Change_Value(int time)
{
	TIM4->ARR = TIME4_PLS_OF_1ms * time;
}

#define TIM3_FREQ					(8000000)			// Hz
#define TIM3_TICK					(1000000/TIM3_FREQ)	// usec
#define TIME3_PLS_OF_1ms			(1000/TIM3_TICK)

void TIM3_Out_Init(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 1);
	Macro_Set_Bit(RCC->APB1ENR, 1);

	Macro_Write_Block(GPIOB->MODER, 0x3, 0x2, 0);  	// PB0 => ALT
	Macro_Write_Block(GPIOB->AFR[0], 0xf, 0x2, 0); 	// PB0 => AF02

	Macro_Write_Block(TIM3->CCMR2,0xff, 0x60, 0);
	TIM3->CCER = (0<<9)|(1<<8);
}

void TIM3_Out_Freq_Generation(unsigned short freq)
{
	// Timer 주파수가 TIM3_FREQ가 되도록 PSC 설정
	TIM3->PSC = (unsigned int) (TIMXCLK / TIM3_FREQ + 0.5) - 1;
	// 요청한 주파수가 되도록 ARR 설정
	TIM3->ARR = TIM3_FREQ / freq - 1;	// 원하는 주파수로 수정
	// Duty Rate 50%가 되도록 CCR3 설정
	TIM3->CCR3 = TIM3->ARR * 0.5;
	// Manual Update(UG 발생)
	Macro_Set_Bit(TIM3->EGR, 0);
	// Down Counter, Repeat Mode, Timer Start
	TIM3->CR1 = (0x1 << 4) | (0x0 << 3) | (0x1 << 0);
}

// 주파수 1KHz
void TIM3_Out_PWM_Generation(unsigned short freq, int duty)
{
	// Timer 주파수가 TIM3_FREQ가 되도록 PSC 설정
	TIM3->PSC = (unsigned int) (TIMXCLK / TIM3_FREQ + 0.5) - 1;
	// 요청한 주파수가 되도록 ARR 설정
	TIM3->ARR = (TIM3_FREQ / freq - 1);	// 원하는 주파수로 수정
	// Duty Rate 50%가 되도록 CCR3 설정
	TIM3->CCR3 = TIM3->ARR * duty / 100;
	// Manual Update(UG 발생)
	Macro_Set_Bit(TIM3->EGR, 0);
	// Down Counter, Repeat Mode, Timer Start
	TIM3->CR1 = (0x1 << 4) | (0x0 << 3) | (0x1 << 0);
}

/*  // 내가 이해한 내용 정리
// 흐름..
stm32는 TIMx 라는 걸로 타이머가 제공해주고, 이를 조정하려면, PSC/PSC_Buf, ARR/CNT, CRR/CRR_Buf.. 
저런 것들을 조정해주면 된다.
여기서 PSC/PSC_Buf는 분주비 설정을 해주는 거다. 분주비 설정이란 기본적으로 stm32는 TIMXCLK가 96MHz인데, 이거를 조절해주는 거야.
분주비를 20Hz로 해주고 싶다는 것은 20Hz마다 1초를 세고 싶다는 거지. 20Hz로 바꿔주려면 TIMXCLK를 바꿔줘야겠지.
이를 설정해주기 위해 다음처럼 할 수 있어.
#define TIMx_TICK 		(20)	// 20us
#define TIMx_FRAG 		(1000000. / TIMx_TICK)	// 50MHz/sec
#define TIMx_ms_FRAG 	(TIMx_FRAG / 1000.)		// 1ms의 frga

TIMx->PSC = (unsigned int)(TIMXCLK / TIMx_FRAG + 0.5) - 1; 	// 분주비는 PSC_Buf에서 + 1 해서 반환해주니까, PSC에서는 -1을 해줘야함.
이렇게 설정을 해주면, PSC(분주비)가 바뀐 거지! 저 위의 식에 따르면 20Hz 분주로 바뀐거지!
그리고 여기서 CCR도 바꿔야하는거잖아? 그리고 ARR을 세팅해줘야지. ARR은 내가 세고 싶은 값을 넣어주면 되는거잖아?
ARR = 10이면, PSC에서 설정한 진동수만큼 와야 1초가 지나는 거고, 그게 10번 지나면, 이 TIMx는 time out이 오니까, UIF를 1로 set해서, 수동으로 내려주세요! 해주겠지?
그리고 여기서 (TIMx->ARR - TIMx->CNT ) * TIMx_TICK 을 해주면, 얼마나 타이머가 흘렀는지를 알 수 있는 거고..
TIMx->CRR은 TIMx가 활성화 되어있는 rate를 구하기 위한 거고,, 정규화된 신호의 경우, ARR의 절반이 CRR인거지..
CRR은 주파수를 증폭해주는 역할을 하는.. < 왜 있는건지 아직 잘 모르겠네.. >> 아, 이게 있어야, pwm이 되는 건가?

그리고 CRR 사용해서 PWM 작업을 하려면, CCMR1/2를 사용해서 작업해주는거고,, TIMx->CCER은 enable 해주는 거지!?
*/

void TIM3_Out_Stop(void)
{
	Macro_Clear_Bit(TIM3->CR1, 0);
}
