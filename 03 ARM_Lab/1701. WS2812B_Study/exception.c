#include "device_driver.h"
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
	// TIM4 Interrupt Pending Clear
	Macro_Clear_Bit(TIM4->SR, 0);
	// NVIC Pending Clear
	NVIC_ClearPendingIRQ(30);
	TIM4_Expired = 1;
}

// extern unsigned int lookup_table[LOOKUP_TABLE_SIZE];			// 크기 지정은 이후에
// extern volatile unsigned int lookup_table_idx;	// 이걸로 exception에서 직접 값을 바꿔줄 것
// extern volatile int check_flag;	// check.. > 차후 사용..

// extern void TIM3_PWM_Generator(int en, double duty);	

// void TIM3_IRQHandler(void)
// {
// 	Macro_Clear_Bit(TIM3->SR, 0);
// 	NVIC_ClearPendingIRQ(29);

// 	if(lookup_table_idx < LOOKUP_TABLE_SIZE)
// 	{
// 		// 넣고
// 		TIM3->CCR2 = lookup_table[lookup_table_idx++];
// 	} else {
// 		// 끝  
// 		lookup_table_idx = 0;
// 		check_flag = 1;
// 	}
// }


extern unsigned int lookup_table[LOOKUP_TABLE_SIZE];
extern volatile unsigned int lookup_table_idx;
extern volatile int check_flag;

extern void TIM3_PWM_Generator(int en, double duty);	

void TIM3_IRQHandler(void)
{
	Macro_Clear_Bit(TIM3->SR, 0);
	NVIC_ClearPendingIRQ(29);

	if(lookup_table_idx < LOOKUP_TABLE_SIZE)
	{
		TIM3->CCR3 = lookup_table[lookup_table_idx++];  // CCR2 → CCR3
	} else {
		lookup_table_idx = 0;
		check_flag = 1;
	}
}