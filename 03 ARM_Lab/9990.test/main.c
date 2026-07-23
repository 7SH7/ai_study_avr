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

void Main(void)
{
	Sys_Init(115200);
	printf("test\n");

	int i;

	TIM4_Repeat();
	
	for(;;)
    {
		if(TIM4_Check_Timeout(TIM4->SR, 0))
	        Macro_Invert_Bit(GPIOA->ODR, 5); 
    }

}