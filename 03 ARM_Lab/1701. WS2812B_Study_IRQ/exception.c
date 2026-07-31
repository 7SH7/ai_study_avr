#include "device_driver.h"
#include <stdio.h>

void _Invalid_ISR(void)
{
	unsigned int r = Macro_Extract_Area(SCB->ICSR, 0x1ff, 0);
	printf("\nInvalid_Exception: %d!\n", r);
	printf("Invalid_ISR: %d!\n", r - 16);
	for (;;);
}

extern volatile int Key_Pressed;

void EXTI15_10_IRQHandler(void)
{
	Key_Pressed = 1;

	EXTI->PR = 0x1 << 13;
	NVIC_ClearPendingIRQ(40);
}

extern volatile int Uart_Data_In;
extern volatile unsigned char Uart_Data;

void USART2_IRQHandler(void)
{
	Uart_Data = (unsigned char)USART2->DR;
	Uart_Data_In = 1;
	NVIC_ClearPendingIRQ(38);
}

extern volatile int TIM4_Expired;

void TIM4_IRQHandler(void)
{
	Macro_Clear_Bit(TIM4->SR, 0);
	NVIC_ClearPendingIRQ(30);
	TIM4_Expired = 1;
}

void DMA1_Stream2_IRQHandler(void)
{
	// 인터럽트 플래그를 지우기 전에 원인을 먼저 저장한다.
	// LISR은 DMA1 Stream 0~3의 완료/오류 상태가 들어 있는 읽기용 레지스터다.
	unsigned int status = DMA1->LISR;
	unsigned int error_flags =
		DMA_LISR_TEIF2 | DMA_LISR_DMEIF2 | DMA_LISR_FEIF2;

	// Writing 1 to LIFCR clears the pending Stream 2 flags.
	// DMA 플래그는 0을 쓰는 것이 아니라, 지우려는 비트에 1을 써서 지운다(W1C).
	// 완료, 절반 완료, 전송 오류, Direct mode 오류, FIFO 오류를 모두 정리한다.
	DMA1->LIFCR = DMA_LIFCR_CTCIF2 |
				 DMA_LIFCR_CHTIF2 |
				 DMA_LIFCR_CTEIF2 |
				 DMA_LIFCR_CDMEIF2 |
				 DMA_LIFCR_CFEIF2;

	if (status & error_flags)
	{
		// 오류가 있으면 타이머와 DMA를 즉시 정지하고 오류 상태를 남긴다.
		WS2812_DMA_Stop();
		WS2812_DMA_Error = 1;
	}
	else if (status & DMA_LISR_TCIF2)
	{
		// NDTR이 0이 되어 전체 전송이 끝난 경우다.
		// 출력 핀을 LOW로 고정한 뒤 완료 플래그를 1로 만든다.
		WS2812_DMA_Stop();
		WS2812_DMA_Done = 1;
	}
}
