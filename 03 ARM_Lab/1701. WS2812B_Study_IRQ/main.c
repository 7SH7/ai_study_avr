#include "device_driver.h"
#include <stdio.h>
#include "timer.h"

static void Sys_Init(int baud)
{
	SCB->CPACR |= (0x3 << 10*2) | (0x3 << 11*2);
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

// PA7, AF2 = TIM3_CH2
// 전체 데이터 이동 경로:
// lookup_table(RAM) -> DMA1 Stream2 -> TIM3_CCR2 -> TIM3_CH2(PA7)
// TIM3가 1.25us마다 Update event를 만들고, 그 이벤트가 DMA 전송 1회를 요청한다.
#define WS2812_FREQ             (800000.0)
#define TIM3_TICK               ((unsigned int)((TIMXCLK / WS2812_FREQ) + 0.5))
#define DMA1_STREAM2_CLEAR_MASK (DMA_LIFCR_CTCIF2 | DMA_LIFCR_CHTIF2 | \
								DMA_LIFCR_CTEIF2 | DMA_LIFCR_CDMEIF2 | \
								DMA_LIFCR_CFEIF2)

// DMA가 읽어 갈 원본 메모리다. STM32F411에는 D-Cache가 없으므로
// 이 Cortex-M4에서는 별도의 cache clean 작업 없이 DMA가 최신 값을 읽을 수 있다.
static unsigned int lookup_table[LOOKUP_TABLE_SIZE];
// volatile: ISR에서 변경되는 값을 Main 코드나 디버거가 항상 실제 메모리에서 읽게 한다.
volatile int WS2812_DMA_Done = 0;
volatile int WS2812_DMA_Error = 0;

static void make_lookup_table(void)
{
	// Down-counting PWM mode 1 + inverted output:
	// physical HIGH time = ARR - CCR.
	unsigned int T0H = (unsigned int)(TIM3_TICK * (1.0 - 0.32));
	unsigned int T1H = (unsigned int)(TIM3_TICK * (1.0 - 0.68));
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
		// CCR == ARR keeps PA7 LOW for the reset/latch interval.
		lookup_table[idx++] = TIM3_TICK - 1;
	}
}

static void WS2812_Pin_Low(void)
{
	// PA7의 출력 데이터 비트를 먼저 LOW로 만든 뒤 GPIO 출력 모드로 바꾼다.
	// 순서를 이렇게 잡으면 AF에서 GPIO로 전환할 때 순간적인 HIGH glitch를 피할 수 있다.
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->BSRR = (1u << (7 + 16));
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1, 14);
}

void WS2812_DMA_Stop(void)
{
	// Keep this public stop routine safe even before the first Start call.
	// Stop 함수가 단독으로 호출되어도 레지스터 접근이 가능하도록 관련 clock을 먼저 켠다.
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_DMA1EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	// clock enable 직후 read-back을 수행하여 다음 주변장치 접근 전에 clock이 반영되게 한다.
	(void)RCC->AHB1ENR;
	(void)RCC->APB1ENR;

	// Stop new requests before disabling the DMA stream.
	// 1) TIM3가 새 DMA 요청을 만들지 못하게 UDE를 먼저 끈다.
	// 2) TIM3 counter를 멈춘다.
	// 3) 진행 중인 DMA Stream을 끄고 EN이 실제로 0이 될 때까지 기다린다.
	TIM3->DIER &= ~TIM_DIER_UDE;
	TIM3->CR1 &= ~TIM_CR1_CEN;

	DMA1_Stream2->CR &= ~DMA_SxCR_EN;
	while (DMA1_Stream2->CR & DMA_SxCR_EN);

	// CPU 쪽 DMA 인터럽트도 끄고, NVIC 및 DMA 내부 pending flag를 정리한다.
	NVIC_DisableIRQ(DMA1_Stream2_IRQn);
	NVIC_ClearPendingIRQ(DMA1_Stream2_IRQn);
	DMA1->LIFCR = DMA1_STREAM2_CLEAR_MASK;

	// Return PA7 to an ordinary LOW output so reset remains asserted.
	// WS2812B는 전송 뒤 DATA를 충분히 오래 LOW로 유지해야 색을 latch한다.
	WS2812_Pin_Low();
}

void WS2812_DMA_Start(void)
{
	// RM0383: TIM3_UP is DMA1 Stream 2, Channel 5 on STM32F411.
	// STM32 DMA는 주변장치마다 연결 가능한 Stream/Channel 조합이 정해져 있다.
	// 여기서는 TIM3 Update 요청이 연결된 DMA1 Stream2, Channel5를 사용한다.
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_DMA1EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	(void)RCC->AHB1ENR;
	(void)RCC->APB1ENR;

	// Make repeated calls safe and force a clean LOW level first.
	// 이전 전송 도중 다시 호출되어도 깨끗한 초기 상태에서 시작한다.
	WS2812_DMA_Stop();

	// 이번 전송의 결과 플래그와 이전 DMA pending flag를 초기화한다.
	WS2812_DMA_Done = 0;
	WS2812_DMA_Error = 0;
	DMA1->LIFCR = DMA1_STREAM2_CLEAR_MASK;

	// Select AF2 now, but keep PA7 as a GPIO LOW until the timer is running.
	// AFR에는 TIM3_CH2 기능을 미리 선택하지만, MODER는 아직 GPIO 출력 상태다.
	// 타이머 준비 중 PA7이 예상보다 일찍 HIGH가 되는 것을 막기 위한 순서다.
	GPIOA->BSRR = (1u << (7 + 16));
	Macro_Write_Block(GPIOA->AFR[0], 0xf, 0x2, 28);

	// 96MHz / (PSC+1) / (ARR+1) = 800kHz = 1.25us/bit.
	// PSC=0이면 분주하지 않고 96MHz로 센다. ARR=119이면 0~119, 총 120 tick이다.
	// 120 / 96MHz = 1.25us이므로 WS2812B 데이터 한 비트의 전체 주기가 된다.
	TIM3->CR1 = TIM_CR1_DIR;
	TIM3->CR2 = 0;
	TIM3->SMCR = 0;
	TIM3->DIER = 0;
	TIM3->CCER = 0;
	TIM3->PSC = 0;
	TIM3->ARR = TIM3_TICK - 1;

	// PWM mode 1, channel 2, with CCR2 preload enabled. DMA writes the
	// preload register during one period; update applies it next period.
	// OC2PE=1이면 DMA가 CCR2에 쓴 값이 즉시 출력에 반영되지 않는다.
	// 먼저 preload에 저장되고, 다음 Update event에서 active(shadow) 값으로 옮겨진다.
	// 따라서 현재 PWM 펄스가 중간에 잘리지 않고 다음 1.25us 경계에서만 duty가 바뀐다.
	TIM3->CCMR1 =
		(0x6u << TIM_CCMR1_OC2M_Pos) |
		TIM_CCMR1_OC2PE;

	// Start with one LOW guard period. UG moves it into the active shadow
	// register, then lookup_table[0] is staged in the preload register.
	// 최초 active CCR2에는 완전한 LOW 값을 넣는다.
	// EGR.UG로 CCR2=ARR를 active에 반영한 다음, 첫 데이터는 preload에 넣어 둔다.
	// 첫 Update가 발생하면 lookup_table[0]이 active로 넘어가며 실제 데이터가 시작된다.
	TIM3->CCR2 = TIM3->ARR;
	TIM3->EGR = TIM_EGR_UG;
	TIM3->CNT = TIM3->ARR;
	TIM3->SR = 0;
	TIM3->CCR2 = lookup_table[0];
	TIM3->CCER = TIM_CCER_CC2P | TIM_CCER_CC2E;

	// lookup_table[0] is already preloaded. Each update copies the following
	// 32-bit value to CCR2 for use in the next PWM period.
	// PAR : DMA 목적지 주소. 고정된 TIM3_CCR2 주소이므로 PINC는 사용하지 않는다.
	// M0AR: DMA 원본 주소. table[0]은 이미 넣었으므로 table[1]부터 시작한다.
	// NDTR: 남은 전송 개수. DMA 요청 1회마다 자동으로 1씩 감소하고 0이면 TC가 발생한다.
	DMA1_Stream2->PAR = (unsigned int)&TIM3->CCR2;
	DMA1_Stream2->M0AR = (unsigned int)&lookup_table[1];
	DMA1_Stream2->NDTR = LOOKUP_TABLE_SIZE - 1;
	// FCR=0: FIFO를 사용하지 않는 Direct mode로 한 항목씩 바로 전송한다.
	DMA1_Stream2->FCR = 0;

	// CR 설정 내용:
	// CHSEL=5       : TIM3_UP 요청을 선택
	// PL=11         : Stream 우선순위 Very High
	// MSIZE/PSIZE=10: 메모리와 주변장치 모두 32bit 단위
	// MINC=1        : 전송 후 lookup_table 주소를 다음 원소로 증가
	// DIR=01        : Memory-to-Peripheral 방향
	// TCIE/TEIE/DMEIE: 완료/전송 오류/Direct mode 오류 인터럽트 허용
	DMA1_Stream2->CR =
		(0x5u << DMA_SxCR_CHSEL_Pos) |
		DMA_SxCR_PL |
		DMA_SxCR_MSIZE_1 |
		DMA_SxCR_PSIZE_1 |
		DMA_SxCR_MINC |
		DMA_SxCR_DIR_0 |
		DMA_SxCR_TCIE |
		DMA_SxCR_TEIE |
		DMA_SxCR_DMEIE;

	// DMA Stream2에서 완료/오류가 발생했을 때 Cortex-M4가 ISR로 들어가도록 NVIC를 켠다.
	// 이것은 비트마다 발생하는 인터럽트가 아니라 전체 DMA 전송 끝에 한 번 발생한다.
	NVIC_ClearPendingIRQ(DMA1_Stream2_IRQn);
	NVIC_EnableIRQ(DMA1_Stream2_IRQn);

	// Producer order: DMA ready -> timer DMA request -> timer counter.
	// PA7 is changed to AF only after the LOW guard period has started.
	// 활성화 순서가 중요하다:
	// DMA를 먼저 준비하고 -> TIM3의 DMA 요청을 허용하고 -> 마지막에 counter를 시작한다.
	// 반대 순서라면 첫 Update 요청을 DMA가 받을 준비가 되기 전에 놓칠 수 있다.
	DMA1_Stream2->CR |= DMA_SxCR_EN;
	TIM3->DIER = TIM_DIER_UDE;
	TIM3->CR1 |= TIM_CR1_CEN;
	// LOW guard 주기가 시작된 뒤에만 PA7을 TIM3_CH2 Alternate Function으로 연결한다.
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x2, 14);
}

void Main(void)
{
	Sys_Init(115200);

	WS2812_Pin_Low();
	make_lookup_table();
	WS2812_DMA_Start();

	while (1);
}
