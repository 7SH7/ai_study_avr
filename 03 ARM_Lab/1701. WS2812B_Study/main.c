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

volatile int Key_Pressed = 0;
volatile int Uart_Data_In = 0;
volatile unsigned char Uart_Data = 0;
volatile int TIM4_Expired = 0;

#if 1
// PA7, AF02 (TIM3_CH2)

#define TIM3_FRAG 	(800000.0)
#define TIM3_TICK	(unsigned int)(TIMXCLK / TIM3_FRAG)
#define TIM3_PLS_OF_1ms (TIM3_TICK / 1000.) 

void Main(void)
{
	
}

/*
T0H: duty = ccr / arr = .4 / 1.25 = 0.32
T1H: duty = ccr / arr = .85 / 1.25 = 0.68
*/
void TIM3_PWM_Generator(double duty)
{
	Macro_Set_Bit(RCC->APB1ENR, 1);
	Macro_Set_Bit(RCC->AHB1ENR, 0);
	
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x2, 14);
	Macro_Write_Block(GPIOA->AFR[0], 0xf, 0x2, 28);
	
	TIM3->CR1 = (0x0 << 7) | (0x1 << 4) | (0x0 << 3) | (0x0 << 0);
	
	// arr 최대, psc 최소
	TIM3->ARR =	TIM3_TICK - 1;
	TIM3->PSC = 0;
	
	TIM3->CCMR1 = (0x0 << 15) | (0x6 << 12) | (0x1 << 11) | (0x0 << 10) | (0x0 << 8);
	TIM3->CCER = (0x1 << 4);
	
	TIM3->CCR2 = (unsigned int)(TIM3_TICK * duty);
	
	// 적용
	Macro_Set_Bit(TIM3->EGR, 0);
	
	// 시작
	Macro_Set_Bit(TIM3->CR1, 0);
	
}

#else

void Main(void)
{
	Sys_Init(115200);
	printf("\nTimer 4 Interrupt Test\n");

	Key_ISR_Enable(1);
	Uart2_RX_Interrupt_Enable(1);
	TIM4_Repeat_Interrupt_Enable(1, 200);

	int d = 0;

	for(;;)
	{
		if(Key_Pressed)
		{
			printf("KEY Pressed!!!\n");
			Key_Pressed = 0;
		}

		if(Uart_Data_In)
		{
			printf("RX Data = %c\n", Uart_Data);
			Uart_Data_In = 0;
		}		

		if(TIM4_Expired)
	    {
			(d ^= 1) ? LED_On() : LED_Off();
			TIM4_Expired = 0;
	    }
	}
}

#endif