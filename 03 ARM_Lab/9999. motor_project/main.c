#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
}

// 스위치: PC13									>> INPUT
// PA0, PA1 :: PA0: 1A / PA1: 2A			   >> OUTPUT >> 모터 움직이는거..  

#define TIM2_MAX    (0xffffffff)	// TIM2
#define TIM2_TICK	(20)   // 주기 us
#define TIM2_FRAG	(1000000. / TIM2_TICK)   // 진동수(pulse) Hz
#define TIM2_1ms_FRAG  (TIM2_FRAG / 1000.)	// 1ms의 pulse


void init_out_gpio(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 0);
	GPIOA->MODER = (0x0 << 3) | (0x1 << 2) | (0x0 << 1) | (0x1 << 0);
	GPIOA->OTYPER = (0x0 << 1) | (0x0 << 0);
}

void init_in_gpio(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 2);
	GPIOC->MODER = (0x0 << 27) | (0x0 << 26);
	GPIOC->PUPDR = (0x0 << 27) | (0x1 << 26);	// pull up
}

void start_stopwatch(void)
{
	// timer2 사용 set
	Macro_Set_Bit(RCC->APB1ENR, 0);			// tim2 en

	TIM2->CR1 = (0x1 << 4) | (0x1 << 3);	// down count + 1회만 돌리는

	// TIMXCLK / (희망하는 진동수) = 분주기
	TIM2->PSC = (unsigned int)(TIMXCLK / TIM2_FRAG + 0.5) - 1; 	// PSC_buf에서 +1로 분주기 해주니까..
	TIM2->ARR = TIM2_MAX;
	
	// 메뉴얼 모드 > 값 수정 시, 바로 작동
	Macro_Set_Bit(TIM2->EGR, 0);

	// timer 사용 set
	Macro_Set_Bit(TIM2->CR1, 0);	// CEN = 1 >> T2시작
}

unsigned int stop_stopwatch(void)
{
	unsigned int time = 0;

	Macro_Clear_Bit(TIM2->CR1, 0);	// clear 해주면, 멈춤.
	time = (TIM2_MAX - TIM2->CNT) * TIM2_TICK;

	return time;
}

int delay_stopwatch(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);
	TIM2->CR1 = (0x1 << 4) | (0x0 << 3); 	// delay니까 repeat이지 않나..
	
	TIM2->PSC = (unsigned int)(TIMXCLK / TIM2_FRAG + 0.5) - 1;
	unsigned int pls = time * TIM2_1ms_FRAG;
	int n = pls / TIM2_MAX;
	int m = pls % TIM2_MAX;
	int i;

	for(i = 0; i < n; i++)
	{
		// 여기서 한 일
		TIM2->ARR = TIM2_MAX;
		Macro_Set_Bit(TIM2->EGR, 0);
		Macro_Clear_Bit(TIM2->SR, 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(!Macro_Check_Bit_Set(TIM2->SR, 0));
	}

	// 동일하게 여기서도
	TIM2->PSC = m;	// m분주
	Macro_Set_Bit(TIM2->EGR, 0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);
	while(!Macro_Check_Bit_Set(TIM2->SR, 0));

	Macro_Clear_Bit(TIM2->CR1, 0);

	return 0;
}

void init_motor(void)
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
}

void stop_motor(void)
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
}

void turn_left_motor()
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
}

void turn_right_motor()
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
}

void Main(void)
{
	Sys_Init(115200);
	printf("start\n");

	int flag = 0;

	init_out_gpio();
	init_in_gpio();
	init_motor();

	int check_time;
	for(;;)
	{
		// 눌렸어?
		// 바로 시간 측정해
		// 3sec 되기 전에 또 눌렸으면, 방향바꾸고, 시간 초기화
		if(!Macro_Check_Bit_Set(GPIOC->IDR, 13))
		{
			start_stopwatch();
			check_time = 0;

			while(!Macro_Check_Bit_Set(GPIOC->IDR, 13))
			{
				int pls = TIM2_TICK * (TIM2_MAX - TIM2->CNT);
				if(pls >= 3000000)
				{
					check_time = 1;
					break;
				}
			}
			stop_stopwatch();
			if(check_time)
			{
				stop_motor();
			}
			else{
				if(flag == 0)
				{
					turn_left_motor();
					flag = 1;
				} else if(flag == 1)
				{
					turn_right_motor();
					flag = 0;
				}

			}
			while(!Macro_Check_Bit_Set(GPIOC->IDR, 13));
		}
	}

}

