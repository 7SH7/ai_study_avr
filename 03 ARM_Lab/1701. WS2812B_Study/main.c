#include "device_driver.h"
#include <stdio.h>
#include "timer.h"

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
volatile int TIM3_Expired = 0;


#if 1
// PA7, AF02 (TIM3_CH2)

#define TIM3_FRAG 	(800000.0)
#define TIM3_TICK	(unsigned int)((TIMXCLK) / TIM3_FRAG + 0.5)
#define TIM3_PLS_OF_1ms (TIM3_TICK / 1000.) 

/*
T0H: duty = ccr / arr = .4 / 1.25 = 0.32
T1H: duty = ccr / arr = .85 / 1.25 = 0.68
// 실측해보니 arr이 7.75.. 
// 

내 생각을 말해볼게.
지금 이건 96000000 Hz / sec 인 st야. 
여기서 나는 지금 1.25us를 만들고 싶어. 1.25us는 120Hz야. 
즉, 나는 96 Hz / sec 인 타이머를 만들고 싶은거지..
그러니까 분주비는 1000000가 되어야 하는거고, 셀 수 있는 최대는 1.25가 되어야 하는거지.
나 잘 생각한 거 맞나?

>> 정리..
지금 96MHz / sec 이야. >> 초당 96000000번 진동해
이거에서 arr, psc 선택. >> arr을 나는 120까지 셀거야. > 그러면 psc는 96000000 / 120 = 800000 이렇게 되는 거?! 
A) 잘 이해한 것 맞음.


lookup table은 for문으로
// IRQ 29
*/


unsigned int lookup_table[LOOKUP_TABLE_SIZE];			// 크기 지정은 이후에
volatile unsigned int lookup_table_idx = 0;	// 이걸로 exception에서 직접 값을 바꿔줄 것
volatile int check_flag = 0;	// check.. > 차후 사용..


void make_lookup_table(void)
{
    // 다운카운트 + CC2P=1: 실제 HIGH시간 = ARR - CCR
    // 그러므로 CCR = ARR * (1 - 목표duty)
    unsigned int T0H = (unsigned int)(TIM3_TICK * (1.0 - 0.32)); // = TICK*0.68
    unsigned int T1H = (unsigned int)(TIM3_TICK * (1.0 - 0.68)); // = TICK*0.32
    int idx = 0;

    for (int led = 0; led < 1; led++)
    {
        for (int bit = 0; bit < 12; bit++)
        {
            lookup_table[idx++] = T1H;  
        }
        for (int bit = 0; bit < 12; bit++)
        {
            lookup_table[idx++] = T0H;  
        }
    }
    for (int led = 0; led < 1; led++)
    {
        for (int bit = 0; bit < 6; bit++)
        {
            lookup_table[idx++] = T1H;  
        }
        for (int bit = 0; bit < 6; bit++)
        {
            lookup_table[idx++] = T0H;  
        }
        for (int bit = 0; bit < 6; bit++)
        {
            lookup_table[idx++] = T1H;  
        }
        for (int bit = 0; bit < 6; bit++)
        {
            lookup_table[idx++] = T0H;  
        }
    }
    for (int led = 0; led < 1; led++)
    {
        for (int bit = 0; bit < 6; bit++)
        {
            lookup_table[idx++] = T1H;  
        }
        for (int bit = 0; bit < 6; bit++)
        {
            lookup_table[idx++] = T0H;  
        }
        for (int bit = 0; bit < 12; bit++)
        {
            lookup_table[idx++] = T0H;  
        }
    }
    for (int led = 0; led < 1; led++)
    {
        for (int bit = 0; bit < 12; bit++)
        {
            lookup_table[idx++] = T1H;  
        }
        for (int bit = 0; bit < 6; bit++)
        {
            lookup_table[idx++] = T1H;  
        }
        for (int bit = 0; bit < 6; bit++)
        {
            lookup_table[idx++] = T0H;  
        }
    }

    for (int i = 0; i < RES_PERIOD; i++)
    {
        // RES: LOW를 유지해야 하므로 CCR을 최대(ARR)에 가깝게
        lookup_table[idx++] = TIM3_TICK - 1;	// 이게 시간 오래걸린 거
    }
}


void init_button(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 0);
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 14);
	Macro_Write_Block(GPIOA->ODR, 0x1, 0x0, 7);
}

// PWM 제외하고는 나머지는 버튼을 OUTPUT으로 하고, 그 이후는 GPIO를 0으로 설정하기. >> 일단 지금 거 확인 되면 수정하기
void TIM3_PWM_Generator(int en, double duty)	
{
	if(en)
	{
		Macro_Set_Bit(RCC->APB1ENR, 1);
		Macro_Set_Bit(RCC->AHB1ENR, 0);
		
		Macro_Write_Block(GPIOA->MODER, 0x3, 0x2, 14);
		Macro_Write_Block(GPIOA->AFR[0], 0xf, 0x2, 28);
		
		TIM3->CR1 = (0x0 << 7) | (0x1 << 4) | (0x0 << 3) | (0x0 << 0);
		
		TIM3->ARR =	TIM3_TICK - 1;	// 120분주	
		TIM3->PSC = 0;
		
		TIM3->CCMR1 = (0x0 << 15) | (0x6 << 12) | (0x1 << 11) | (0x0 << 10) | (0x0 << 8);
        TIM3->CCER  = (0x1 << 5) | (0x1 << 4);

		lookup_table_idx = 1; 
		TIM3->CCR2 = lookup_table[0];
		
		// 적용
		Macro_Set_Bit(TIM3->EGR, 0);

		// TIM3 Pending Clear
		Macro_Clear_Bit(TIM3->SR, 0);
		// NVIC Pending Clear
		NVIC_ClearPendingIRQ(29);

		// TIM3 Interrupt Enable
		Macro_Set_Bit(TIM3->DIER, 0);
		// NVIC Interrupt Enable
		NVIC_EnableIRQ(29);

		// 시작
		Macro_Set_Bit(TIM3->CR1, 0);
	} else {
		init_button();

		NVIC_DisableIRQ(29);
		Macro_Clear_Bit(TIM3->CR1, 0);
		Macro_Clear_Bit(TIM3->DIER, 0);
	}
}

void Main(void)
{
	Sys_Init(115200);

	init_button();
	make_lookup_table();
	TIM3_PWM_Generator(1, 0);

	while(1);
}

#endif