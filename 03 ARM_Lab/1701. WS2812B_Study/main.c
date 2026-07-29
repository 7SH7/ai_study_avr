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

// PB0, AF02 (TIM3_CH3)

#define TIM3_FRAG 	(800000.0)
#define TIM3_TICK	(unsigned int)((TIMXCLK) / TIM3_FRAG + 0.5)
#define TIM3_PLS_OF_1ms (TIM3_TICK / 1000.) 

unsigned int lookup_table[LOOKUP_TABLE_SIZE];
volatile unsigned int lookup_table_idx = 0;
volatile int check_flag = 0;

void make_lookup_table(void)
{
    // 다운카운트 + CC3P=1: 실제 HIGH시간 = ARR - CCR
    // 그러므로 CCR = ARR * (1 - 목표duty)
    unsigned int T0H = (unsigned int)(TIM3_TICK * (1.0 - 0.32)); // = TICK*0.68
    unsigned int T1H = (unsigned int)(TIM3_TICK * (1.0 - 0.68)); // = TICK*0.32
    int idx = 0;

    for (int led = 0; led < 4; led++)
    {
        for (int bit = 0; bit < 24; bit++)
        {
            lookup_table[idx++] = T1H;  // 전부 "1"(흰색) 의도
        }
    }

    for (int i = 0; i < RES_PERIOD; i++)
    {
        // RES: LOW 유지 → CCR을 최대(ARR)에 가깝게
        lookup_table[idx++] = TIM3_TICK - 1;
    }

    for (int i = 0; i < LOOKUP_TABLE_SIZE; i++)
    {
        printf("%u\r\n", lookup_table[i]);
    }
}

void init_button(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 1);            // GPIOBEN (PA=0 → PB=1)
	Macro_Write_Block(GPIOB->MODER, 0x3, 0x1, 0);  // pin0, Output
	Macro_Write_Block(GPIOB->ODR, 0x1, 0x0, 0);    // pin0 Low
}

void TIM3_PWM_Generator(int en, double duty)	
{
	if(en)
	{
		Macro_Set_Bit(RCC->APB1ENR, 1);   // TIM3EN (동일)
		Macro_Set_Bit(RCC->AHB1ENR, 1);   // GPIOBEN (PA=0 → PB=1)
		
		Macro_Write_Block(GPIOB->MODER, 0x3, 0x2, 0);  // pin0, AF모드
		Macro_Write_Block(GPIOB->AFR[0], 0xf, 0x2, 0); // pin0 → AFRL, position 0, AF02
		
		TIM3->CR1 = (0x0 << 7) | (0x1 << 4) | (0x0 << 3) | (0x0 << 0); // DIR=1(다운카운트) 유지
		
		TIM3->ARR =	TIM3_TICK - 1;	// 120분주	
		TIM3->PSC = 0;
		
		// CH3용 레지스터: CCMR1(CH1/2) 대신 CCMR2(CH3/4) 사용
		// OC3M(bit6:4)=110, OC3PE(bit3)=1, OC3FE(bit2)=0, CC3S(bit1:0)=00
		TIM3->CCMR2 = (0x6 << 4) | (0x1 << 3) | (0x0 << 2) | (0x0 << 0);
		
		// CC3E(bit8)=1, CC3P(bit9)=1 (반전, 기존 CC2P=1과 동일 의미)
		TIM3->CCER  = (0x1 << 9) | (0x1 << 8);

		lookup_table_idx = 0;
		TIM3->CCR3 = lookup_table[lookup_table_idx++]; // table[0] → preload, shadow로 강제 로드
		Macro_Set_Bit(TIM3->EGR, 0);                    // UG: 강제 update

		TIM3->CCR3 = lookup_table[lookup_table_idx++]; // table[1] 미리 preload (경합 방지)

		Macro_Clear_Bit(TIM3->SR, 0);
		NVIC_ClearPendingIRQ(29);

		Macro_Set_Bit(TIM3->DIER, 0);
		NVIC_EnableIRQ(29);

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
	init_button();
	make_lookup_table();
	TIM3_PWM_Generator(1, 0);

	while(1);
}

#if 0
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

lookup table은 for문으로
// IRQ 29
*/


unsigned int lookup_table[LOOKUP_TABLE_SIZE];			// 크기 지정은 이후에
volatile unsigned int lookup_table_idx = 0;	// 이걸로 exception에서 직접 값을 바꿔줄 것
volatile int check_flag = 0;	// check.. > 차후 사용..

// 96개짜리 배열을 만들어서.. 24 * 4.. >> [0 + (4 * i)] [1 + (4 * i)] [2 + (4 * i)] [3 + (4 * i)] 이런 식으로 해서 처리
// 내가 띄우고 싶은 색을 미리 넣어두는 것. >> 24, 24, 24, 24 >> LED 1개씩 처리함.
// void make_lookup_table(void)	
// {
// 	// T0H, T1H 대신에 LED 4개 각각에 들어가야하는 값을 넣어주는 방식으로 수정해야함.
// 	int T0H = (unsigned int)(TIM3_TICK * 0.32);
// 	int T1H = (unsigned int)(TIM3_TICK * 0.68);
// 	int idx = 0;

// 	// led 4개에 대해서
// 	for(int led = 0 ; led < 4 ; led++)
// 	{
// 		for(int bit = 0 ; bit < 24 ; bit++)
// 		{
// 			lookup_table[idx++] = T1H; //T0H;	// 실제는 여기에 각 LED마다 어떤 색 띄울지 하나하나 넣어주고, 계산해줘야하는것.
// 		}
// 	}

// 	for(int i = 0 ; i < RES_PERIOD ; i++)
// 	{
// 		lookup_table[idx++] =  0;
// 	}

//     for (int i = 0; i < LOOKUP_TABLE_SIZE; i++)
//     {
//         printf("%u\r\n", lookup_table[i]);
//     }
// }

void make_lookup_table(void)
{
    // 다운카운트 + CC2P=1: 실제 HIGH시간 = ARR - CCR
    // 그러므로 CCR = ARR * (1 - 목표duty)
    unsigned int T0H = (unsigned int)(TIM3_TICK * (1.0 - 0.32)); // = TICK*0.68
    unsigned int T1H = (unsigned int)(TIM3_TICK * (1.0 - 0.68)); // = TICK*0.32
    int idx = 0;

    for (int led = 0; led < 4; led++)
    {
        for (int bit = 0; bit < 24; bit++)
        {
            lookup_table[idx++] = T1H;  // 전부 "1"(흰색) 의도 → 반전된 T1H 사용
        }
    }

    for (int i = 0; i < RES_PERIOD; i++)
    {
        // RES: LOW를 유지해야 하므로 CCR을 최대(ARR)에 가깝게
        lookup_table[idx++] = TIM3_TICK - 1;
    }

    for (int i = 0; i < LOOKUP_TABLE_SIZE; i++)
    {
        printf("%u\r\n", lookup_table[i]);
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
		
		#pragma region 설명
		// arr 최대, psc 최소
		// arr을 그냥 최대로.. 0.15us..로 하면..
		// timeout이 걸렸어. > 그럼 그때 바뀌도록 crr, arr을 갈아줘. 그럼 이제 다다음 pulse에 적용되어서 작동되겠지.
		// exception handler >> 바로 적용하도록.. (if문 같은거 쓰기보다는 다른 방식으로 delay를 최소로 해야해. >> led가 4개가 있으면, led마다 키고 싶은 생상을 배열에 {ccr, arr}을 미리 계산해서 넣어둔 표(lookup table)을 만들어서 바로 대입하기)
		// 96개짜리 배열을 만들어서.. 24 * 4.. >> [0 + (4 * i)] [1 + (4 * i)] [2 + (4 * i)] [3 + (4 * i)] 이런 식으로 해서 처리
		// 이런 기기 받으면 제일 먼저 할 일 > 기기를 검증해라.
		// 0만 계속 만드는 코드
		// 1만 계속 만드는 코드
		// 리턴 코드 (Tout은 나가게 하고, 이 신호를 GPIO로 뽑아서 처리하는 거..)
		// 위의 3개 하는데 필요한 psc, arr ... 을 구해서 하나로 통일
		#pragma endregion 설명

		TIM3->ARR =	TIM3_TICK - 1;	// 120분주	
		TIM3->PSC = 0;
		
		TIM3->CCMR1 = (0x0 << 15) | (0x6 << 12) | (0x1 << 11) | (0x0 << 10) | (0x0 << 8);
        TIM3->CCER  = (0x1 << 5) | (0x1 << 4);

		// check 필요
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
	init_button();
	make_lookup_table();
	TIM3_PWM_Generator(1, 0);

	// TIM3_PWM_Generator(0.68);
	// TIM3_PWM_Generator(0.85);

	while(1);
}

#endif

#if 0
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

lookup table은 for문으로
// IRQ 29
*/
void TIM3_PWM_Generator(double duty)
{
	Macro_Set_Bit(RCC->APB1ENR, 1);
	Macro_Set_Bit(RCC->AHB1ENR, 0);
	
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x2, 14);
	Macro_Write_Block(GPIOA->AFR[0], 0xf, 0x2, 28);
	
	TIM3->CR1 = (0x0 << 7) | (0x1 << 4) | (0x0 << 3) | (0x0 << 0);
	
	#pragma region 설명
	// arr 최대, psc 최소
	// arr을 그냥 최대로.. 0.15us..로 하면..
	// timeout이 걸렸어. > 그럼 그때 바뀌도록 crr, arr을 갈아줘. 그럼 이제 다다음 pulse에 적용되어서 작동되겠지.
	// exception handler >> 바로 적용하도록.. (if문 같은거 쓰기보다는 다른 방식으로 delay를 최소로 해야해. >> led가 4개가 있으면, led마다 키고 싶은 생상을 배열에 {ccr, arr}을 미리 계산해서 넣어둔 표(lookup table)을 만들어서 바로 대입하기)
	// 96개짜리 배열을 만들어서.. 24 * 4.. >> [0 + (4 * i)] [1 + (4 * i)] [2 + (4 * i)] [3 + (4 * i)] 이런 식으로 해서 처리
	// 이런 기기 받으면 제일 먼저 할 일 > 기기를 검증해라.
	// 0만 계속 만드는 코드
	// 1만 계속 만드는 코드
	// 리턴 코드 (Tout은 나가게 하고, 이 신호를 GPIO로 뽑아서 처리하는 거..)
	// 위의 3개 하는데 필요한 psc, arr ... 을 구해서 하나로 통일
	#pragma endregion 설명

	Macro_Set_Bit(TIM3->DIER, 0);	// interrupt 허용

	TIM3->ARR =	TIM3_TICK - 1;	// 120분주	
	TIM3->PSC = 0;
	
	TIM3->CCMR1 = (0x0 << 15) | (0x6 << 12) | (0x1 << 11) | (0x0 << 10) | (0x0 << 8);
	TIM3->CCER = (0x1 << 5) | (0x1 << 4);
	
	TIM3->CCR2 = (unsigned int)(TIM3_TICK * duty);
	
	// 적용
	Macro_Set_Bit(TIM3->EGR, 0);
	
	// 시작
	Macro_Set_Bit(TIM3->CR1, 0);
	
}

void Main(void)
{
	TIM3_PWM_Generator(0.32);
	// TIM3_PWM_Generator(0.68);
	// TIM3_PWM_Generator(0.85);
}

#endif

#if 0

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