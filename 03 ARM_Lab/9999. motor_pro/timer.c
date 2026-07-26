#include "device_driver.h"
#include "timer.h"
#include "motor.h"

/* PWM 공부: 값을 전환시켜서 특정 기점(CCR) 이후로 값을 전환해주는..
분주비 N : N개의 CLK마다 CNT를 +1 GOWNRPtEK.
CK_CNT: 분주 후 카운터 주사푸(초당 몇 CNT)
ARR: 몇 카운트마다 리셋할것인가?
*/

// 분주비를 정하자. > 기준 분주비 정하기가 핵심!
extern volatile int TIM2_Expired;

// timer2의 경우,, 내부 버튼 통해서
// 인터럽트 발생시키는 함수 1개 (여기에 init도 하는 것)
// handler 1개

int TIM2_Interrupt_Enable(int en, int time)
{
	if(en)
	{
		// timer 사용 enable 해주고
		Macro_Set_Bit(RCC->APB1ENR, 0);

		// timer 설정 (CR1, PSC, ARR)
		TIM2->CR1 = (1<<4)|(1<<3);
		TIM2->PSC = (unsigned int)(TIMXCLK/TIM2_FREQ + 0.5)-1;
		TIM2->ARR = TIME2_PLS_OF_1ms * time;

		// EGR로 PSC, ARR 적용
		Macro_Set_Bit(TIM2->EGR,0);

		// 초기화
		Macro_Clear_Bit(TIM2->SR, 0);
		NVIC_ClearPendingIRQ(28);

		// Enable 설정
		Macro_Set_Bit(TIM2->DIER, 0);
		NVIC_EnableIRQ(28);

		// timer 구동 >> 제일 마지막!
		Macro_Set_Bit(TIM2->CR1, 0);

	} else {
		NVIC_DisableIRQ(28);
		Macro_Clear_Bit(TIM2->CR1, 0);
		Macro_Clear_Bit(TIM2->DIER, 0);
	}
}

// PWM에서는 주파수가 3개임. (TICK: 분주비, CK_CNT: 분주한 타이머가 CNT+1되는동안 보드 진동수 얼마나 커지나
//							, F_PWM: 파형이 초당 몇 번 반복되나)

// duty = crr / arr >> arr이 커야, ccr로 duty 영역 지정 범위가 넓어짐! > arr이 커야 duty 해상도 ↑

// PA0, PA1 둘 다 사용됨.
void TIM5_Out_Init(void)
{
	// PA0, PA1을 PWM으로 사용
	Macro_Set_Bit(RCC->AHB1ENR, 0);
	// 일단 TIM5에 대해서 설정
	Macro_Set_Bit(RCC->APB1ENR, 3);	
	// GPIO 설정
	Macro_Write_Block(GPIOA->MODER, 0xf, 0xa, 0);
	Macro_Write_Block(GPIOA->AFR[0], 0xff, 0x22, 0);
	// 타이머 설정 해주기
	TIM5->CR1 = (0x0 << 7) | (0x1 << 4) | (0x0 << 3);
	// PSC, ARR 설정 해주기
	// TIM5->PSC = (unsigned int)(TIMXCLK / TIM5_FREQ + 0.5) - 1;
	TIM5->PSC = 0;
	TIM5->ARR = TIM5_ARR;
	// 채널별로 ccr 값은 맞춰줘야함.
	TIM5->CCR1 = 0;
	TIM5->CCR2 = 0;
	// TIM 변경값 적용
	Macro_Set_Bit(TIM5->EGR, 0);
	
	// 몇 번 채널 사용할 것인지 지정 >> PA0, PA1 >> 2개
	Macro_Write_Block(TIM5->CCMR1, 0xffff, 0x6060, 0);	// 1번, 2번 채널 담당
	// PWM 활성화 포트
	Macro_Write_Block(TIM5->CCER, 0x3, 0x1, 0);
	Macro_Write_Block(TIM5->CCER, 0x3, 0x1, 4);
	// TIM 5 Enable해주면 시작~
	Macro_Set_Bit(TIM5->CR1, 0);
}


#pragma region TIM2함수(미사용)
void TIM2_Stopwatch_Start(void)
{
	// timer 사용 enable 해주고
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// timer 설정 (CR1, PSC, ARR)
	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->PSC = (unsigned int)(TIMXCLK/50000.0 + 0.5)-1;
	TIM2->ARR = TIM2_MAX;

	// EGR로 PSC, ARR 적용
	Macro_Set_Bit(TIM2->EGR,0);
	// timer 구동
	Macro_Set_Bit(TIM2->CR1, 0);
}

unsigned int TIM2_Stopwatch_Stop(void)
{
	unsigned int time;

	Macro_Clear_Bit(TIM2->CR1, 0);
	time = (TIM2_MAX - TIM2->CNT) * TIM2_TICK;
	return time;
}

/* Delay Time Extended */

void TIM2_Delay(int time)
{
	int i;
	unsigned int t = TIME2_PLS_OF_1ms * time;

	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->PSC = (unsigned int)(TIMXCLK/(double)TIM2_FREQ + 0.5)-1;
	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->ARR = 0xffffffff;
	Macro_Set_Bit(TIM2->EGR,0);

	for(i=0; i<(t/0xffffffffu); i++)
	{
		Macro_Set_Bit(TIM2->EGR,0);
		Macro_Clear_Bit(TIM2->SR, 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(Macro_Check_Bit_Clear(TIM2->SR, 0));
	}

	TIM2->ARR = t % 0xffffffffu;
	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);

	// while (Macro_Check_Bit_Clear(TIM2->SR, 0));
	// Macro_Clear_Bit(TIM2->CR1, 0);
}
#pragma endregion TIM2함수(미사용)

#pragma region TIM4 함수(미사용)
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

void TIM4_Repeat_Interrupt_Enable(int en, int time)
{
	if(en)
	{
		// TIM4 Clock On

		TIM4->CR1 = (1<<4)|(0<<3);
		TIM4->PSC = (unsigned int)(TIMXCLK/(double)TIM4_FREQ + 0.5)-1;
		TIM4->ARR = TIME4_PLS_OF_1ms * time;
		Macro_Set_Bit(TIM4->EGR,0);

		// TIM4 Pending Clear
		Macro_Clear_Bit(TIM4->SR, 0);
		// NVIC Pending Clear
		NVIC_ClearPendingIRQ(30);

		// TIM4 Interrupt Enable
		Macro_Set_Bit(TIM4->DIER, 0);
		// NVIC Interrupt Enable
		NVIC_EnableIRQ(30);

		// TIM4 Start
		Macro_Set_Bit(TIM4->CR1, 0);

	}

	else
	{
		NVIC_DisableIRQ(30);
		Macro_Clear_Bit(TIM4->CR1, 0);
		Macro_Clear_Bit(TIM4->DIER, 0);
	}
}
#pragma endregion TIM4 함수(미사용)

#pragma region TIM3 함수(미사용)

#define TIM3_FREQ 	  			(8000000) 	      	// Hz
#define TIM3_TICK	  			(1000000/TIM3_FREQ)	// usec
#define TIME3_PLS_OF_1ms  		(1000/TIM3_TICK)

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
	TIM3->PSC = (unsigned int)(TIMXCLK/(double)TIM3_FREQ + 0.5)-1;
	TIM3->ARR = (double)TIM3_FREQ/freq-1;
	TIM3->CCR3 = TIM3->ARR/2;

	Macro_Set_Bit(TIM3->EGR,0);
	TIM3->CR1 = (1<<4)|(0<<3)|(0<<1)|(1<<0);
}

void TIM3_Out_Stop(void)
{
	Macro_Clear_Bit(TIM3->CR1, 0);
}

#pragma endregion TIM3 함수(미사용)

#pragma region 공부 구역
/*
타이머의 정체) 숫자 세는 카운터!

클럭이 옴 > cnt +1 > 클럭이 옴 > cnt +1 > .. > .. : '반복'
TIMXCLK(96MHz) > PSC로 분주 > CK_CNT > CNT + 1 처리.
설명) 타이머에 96M번 CLK이 오면, CNT + 1 해줬어. 
그런데 저 96M번이 너무 빨랐던 거야. 초당 96M번 진동하는게 심하고..
그래서 PSC라는 걸 설정해서 저 진동수를 나눠줌. (분주) :: 여기서 분주한 값 + 1 한 걸로 분주비 결정됨.

그래서 분주 이후, CNT가 올라가는 속도 > CK_CNT라고 함.

----

CNT를 세다가 ARR에 도달함. > SR의 UIF flag가 1로 set. > 인터럽트 켜면, 인터럽트 발생

결국..
timer programming은 저 uev(uif set)이 언제 일어나게 arr를 맞추고, uif가 set되었는지 sr로 확인하는 것!

----

여기서 왜 항상 EGR을 치는가? >> EGR은 UG 비트를 쳐서 UEV를 강제로 한번 일으켜서,
PSC/ARR를 즉시 실제 레지스터로 적용하는 것을 의미.

----

인터럽트로 확장! :: DIER 사용
UEV 발생 > DIER의 0번째 비트(UIE)를 SET해주면, update interrupt enable이 set이 된다.


*/

/*
timer의 arr을 10ms로 하겠다.

기존FRAG: 96000000Hz / sec = 96000Hz / ms
위와 같으니까.. 내가 만들 timer는 9600Hz / ms가 되어야 하고,, 이에 맞춰 ARR도 맞춰야지..
음.. 잘 모르겠다..

공부 결과) 그냥 cnt가 +1이 되기 위해서 clk 몇 개가 들어와야하는지(분주)를 내가 정한다!

예)
CLK = 계란             					= 96000000Hz	
분지비 = 계란 1판 개수					  = 48
CK_CNT = 그래서 초당 몇 개 계란판이 나오나? = 96000000 / 48 = 2000000
PWM) CCR = 몇 번째 계란판부터 불을 켜줄까? (premium light 켜주는 느낌)
>> PWM에서 추가된 register: 
>> CCR(면 판째에 불 끌까?), CCMR(특정 채널을 PWM 모드로), CCER(채널 출력 켜기), GPIO AF(이 핀은 타이머가 사용할 것이다.)
* PWMD은 보통 1~20kHz를 사용한다!

#define TIMx_TICK   	(48)					// 몇 개가 하나의 계란판?
#define TIMx_FRAG		(TIMXCLK / TIMx_TICK)	// 초당 몇 개 계란판 생성 가능?
#define TIMx_PLS_OF_1ms (TIMx_FRAG / 1000)		// 1ms당 몇 개 계란판 생성 가능?

// TICK이 48 >> 분주비 48분주! >> PSC는 -1한 값!
TIMx->PSC = (unsigned int) (TIMXCLK / TIMx_FRAG + 0.5) - 1;
TIMx->ARR = (TIMx_PLS_OF_1ms * time - 1); // 새로 만든 타이머의 한 주기! (cnt는 0부터 세기 때문에 -1 해주기!)

----

모터에 관해서!
모터의 속도는 ccr(duty)에 달려 있다! >> duty가 높으면 빨리 돌고, 낮으면 느리고 돌아. >> 불 켜져있는 시간이 긴만큼 빨라지는거니까

*/
#pragma endregion 공부 구역
