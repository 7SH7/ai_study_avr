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

// 다운카운트 + CC2P=1 이므로 실제 HIGH 시간(틱) = ARR - CCR
// => CCR = ARR - 원하는 HIGH 틱수
//
// 구형 WS2812B와 WS2812B-V5의 스펙 교집합을 노린 값:
//   T0H : 구형 250~550ns / V5 220~380ns  => 교집합 250~380ns  -> 32틱 = 333ns
//   T1H : 구형 650~950ns / V5 580~1000ns => 교집합 650~950ns  -> 77틱 = 802ns
#define T0H_TICKS	(32)						// 32 / 96MHz = 333ns
#define T1H_TICKS	(77)						// 77 / 96MHz = 802ns

#define T0H_CCR		(TIM3_TICK - 1 - T0H_TICKS)	// 119 - 32 = 87
#define T1H_CCR		(TIM3_TICK - 1 - T1H_TICKS)	// 119 - 77 = 42
#define RES_CCR		(TIM3_TICK - 1)				// 119 -> HIGH 0틱 (LOW 유지)

// WS2812B 프로토콜: G → R → B 순서, 각 바이트 MSB first
static void set_led_color(int led, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned int grb  = ((unsigned int)g << 16) | ((unsigned int)r << 8) | (unsigned int)b;
	unsigned int base = led * 24;

	for(int bit = 0 ; bit < 24 ; bit++)
	{
		// bit0 = grb의 MSB(bit23)부터 전송
		lookup_table[base + bit] = (grb & (0x800000u >> bit)) ? T1H_CCR : T0H_CCR;
	}
}

void make_lookup_table(void)
{
	// [진단용] 빨강만, 아주 어둡게.
	//   - 흰색 풀밝기(0xFF,0xFF,0xFF)는 LED당 약 60mA → 4개면 240mA라 USB 전원이 못 버틴다.
	//   - 3.3V 구동 시 파랑(Vf 약 3.0~3.2V)은 거의 안 켜지지만 빨강(Vf 약 2.0V)은 켜진다.
	//   => 전원/레벨 문제를 배제하기에 가장 유리한 조합.
	for(int led = 0 ; led < LED_COUNT ; led++)
	{
		set_led_color(led, 0x20, 0x00, 0x00);
	}

	for(int i = 0 ; i < RES_PERIOD ; i++)
	{
		lookup_table[BIT_COUNT + i] = RES_CCR;
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
		Macro_Write_Block(GPIOA->OSPEEDR, 0x3, 0x3, 14);	// PA7 High speed: T0H 400ns 에지 확보 (리셋값 00 = Low는 너무 느림)

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

		// OC2PE=1이라 CCR2 쓰기는 preload로 들어가고, UEV 때 shadow로 넘어간다.
		// 그래서 시작 전에 2개를 채워둬야 첫 비트가 중복 출력되지 않는다.
		lookup_table_idx = 0;
		TIM3->CCR2 = lookup_table[lookup_table_idx++];	// table[0] → preload

		// 적용: UG로 preload(table[0])를 shadow에 강제 로드
		Macro_Set_Bit(TIM3->EGR, 0);

		TIM3->CCR2 = lookup_table[lookup_table_idx++];	// table[1] → preload (첫 UEV 때 shadow로)

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
	printf("\nWS2812B Start\n");

	init_button();
	make_lookup_table();
	TIM3_PWM_Generator(1, 0);

	// [진단용] 1초마다 완료된 프레임 수를 출력한다.
	// 정상이면 약 2374 (= 96MHz / (337주기 x 120틱)).
	//   0         → TIM3 인터럽트가 아예 안 걸림 (CCR2가 얼어붙어 데이터가 안 나감)
	//   2374 근처 → 파형은 완벽. 문제는 MCU 바깥(레벨/배선/LED).
	for(;;)
	{
		unsigned int f;

		LED_On();	TIM2_Delay(500);
		LED_Off();	TIM2_Delay(500);

		f = (unsigned int)check_flag;
		check_flag = 0;
		printf("frames/sec = %u\n", f);
	}
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