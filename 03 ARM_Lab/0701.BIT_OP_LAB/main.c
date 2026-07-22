#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
    SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
}

#if 0

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
	// todo: 0을 만들 때는 &= ~ 이거를 해줘야함. 
	// todo: 1을 만들 때는 |= 이거를 사용해야함.
	// todo: 하나의 기능은 하나만 하기 때문에, 이를 주의할 것
	GPIOA->MODER = (GPIOA->MODER & ~(0x1 << 11)) | (0x1 << 10);	// 이렇게 한번에 다 처리하는게 좋음.
	GPIOA->OTYPER &= ~(0x1 << 5);	// ~: tilled
	GPIOA->ODR |= (0x1 << 5);

}

#endif


#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("LED ON : Bit Operation - 1\n");

	/* 비트 연산을 이용하여 LED를 ON하는 코드를 설계하시오 */
	// todo: 0을 만들 때는 &= ~ 이거를 해줘야함. 
	// todo: 1을 만들 때는 |= 이거를 사용해야함.
	// todo: 하나의 기능은 하나만 하기 때문에, 이를 주의할 것
	GPIOA->MODER = (GPIOA->MODER & ~(0x3 << 10)) | (0x1 << 10);	// 이렇게 한번에 다 처리하는게 좋음.
	GPIOA->OTYPER &= ~(0x1 << 5);	// ~: tilled
	GPIOA->ODR |= (0x1 << 5);

}

#endif

#if 0
// LED Toggle
void Main(void)
{
	Sys_Init(115200);
	printf("LED Toggling : Macro\n");

	volatile int i;

	/* 매크로를 이용하여 초기에 LED를 출력으로 설정하고 OFF */
	// GPIOA->MODER = (GPIOA->MODER & ~(0x3 << 10)) | (0x01 << 10); // 01을.. MODER5
	// GPIOA->OTYPER &= ~(0x1 << 5);
	// GPIOA->ODR |= (0x1 << 5);

	// MODER 11번 0, 10번 1
	Macro_Write_Block(GPIOA->MODER, 0x3, 0x1 ,10);	// 순서를 dest, pos, bits, data 순으로 채우기 (어디에 어디부터 몇번째까지 어떤 값을)
	// OTYPER 5번째 0
	Macro_Clear_Bit(GPIOA->OTYPER, 5);
	// ODR 5번째 1
	// Macro_Set_Bit(GPIOA->ODR, 5);

	


	for(;;)
	{
		/* LED 반전 및 Delay, Delay는 0x80000으로 설정 */
		Macro_Invert_Bit(GPIOA->ODR, 5);

		for(i=0; i<0x40000; i++);

	}
}

#endif

#if 1

// todo: study misra rule (https://blog.naver.com/techref/222448591325)
// LED Toggle
void Main(void)
{
	Sys_Init(115200);
	printf("LED Toggling : Macro\n");

	volatile int i;

	/* 매크로를 이용하여 초기에 LED를 출력으로 설정하고 OFF */
	// GPIOA->MODER = (GPIOA->MODER & ~(0x3 << 10)) | (0x01 << 10); // 01을.. MODER5
	// GPIOA->OTYPER &= ~(0x1 << 5);
	// GPIOA->ODR |= (0x1 << 5);

	// GPIOA->MODER = (GPIOA->MODER & ~(0x3 << 10)) | (0x01 << 10); // 01을.. MODER5
	// GPIOA->OTYPER &= ~(0x1 << 5);
	// GPIOA->ODR &= ~(0x1 << 5);

	Macro_Write_Block(GPIOA->MODER, 0x3 , 0x1, 10);	// 2개의 연달아 있는 것(0x3)을 0x01로 넣겠다.
	Macro_Clear_Bit(GPIOA->OTYPER, 5);
	Macro_Clear_Bit(GPIOA->ODR, 5);

	for(;;)
	{
		/* LED 반전 및 Delay, Delay는 0x80000으로 설정 */
		Macro_Invert_Bit(GPIOA->ODR, 5);
		for(i=0; i<0x40000; i++);

	}
}

#endif
