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

volatile char *p = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
volatile int Uart_Tx_End = 0;

void Uart2_TX_Interrupt_Enable(void)
{
	// todo: usart2의 tx interrupt를 허용하도록 코드를 작성합니다.
    Macro_Set_Bit(USART2->CR1, 7);
	NVIC_ClearPendingIRQ(38);
	NVIC_EnableIRQ(38);
}

void Main(void)
{
	Sys_Init(115200);
	printf("\nUART2 RX Interrupt Test\n");

	Key_ISR_Enable(1);
	// Uart2_RX_Interrupt_Enable(1);
	Uart2_TX_Interrupt_Enable();

	for(;;)
	{
		if(Uart_Tx_End)
		{
			printf("USART END!!\n");
			Uart_Tx_End = 0;
		}

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

		LED_On();
		TIM2_Delay(500);
		LED_Off();
		TIM2_Delay(500);
	}
}
