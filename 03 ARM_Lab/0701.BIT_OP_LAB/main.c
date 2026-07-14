#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
    SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
}

#if 1

void Main(void)
{
	Sys_Init(115200);
	printf("LED ON\n");

	GPIOA->MODER = 0x1 << 10;
	GPIOA->OTYPER = 0x0 << 5;
	GPIOA->ODR = 0x1 << 5; 
}

#endif

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("LED ON : Bit Operation - 1\n");

	/* 비트 연산을 이용하여 LED를 ON하는 코드를 설계하시오 */


}

#endif

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("LED Toggling : Macro\n");

	volatile int i;

	/* 매크로를 이용하여 초기에 LED를 출력으로 설정하고 OFF */



	for(;;)
	{
		/* LED 반전 및 Delay, Delay는 0x80000으로 설정 */


	}
}

#endif
