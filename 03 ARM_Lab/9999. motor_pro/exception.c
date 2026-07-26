#include "device_driver.h"
#include "motor.h"
#include "timer.h"
#include <stdio.h>

void _Invalid_ISR(void)
{
	unsigned int r = Macro_Extract_Area(SCB->ICSR, 0x1ff, 0);
	printf("\nInvalid_Exception: %d!\n", r);
	printf("Invalid_ISR: %d!\n", r - 16);
	for(;;);
}

extern volatile int Key_Pressed;

void EXTI15_10_IRQHandler(void)
{
	if(Key_Get_Pressed()){
		TIM2_Interrupt_Enable(1, 3000);
	} else {
		TIM2_Interrupt_Enable(0, 3000);
		Key_Pressed = 1;
	}
	
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
	// TIM4 Interrupt Pending Clear
	Macro_Clear_Bit(TIM4->SR, 0);
	// NVIC Pending Clear
	NVIC_ClearPendingIRQ(30);
	TIM4_Expired = 1;
}

extern volatile int TIM2_Expired;

// 3sec 다 세고, time out 되면 여기로 와.
void TIM2_IRQHandler(void)
{
	if(Macro_Check_Bit_Set(TIM2->SR, 0))
		TIM2_Expired = 1;
	
	// TIM4 Interrupt Pending Clear
	Macro_Clear_Bit(TIM2->SR, 0);
	// NVIC Pending Clear
	NVIC_ClearPendingIRQ(28);
}