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

/* Key 인식 */

#if 1

void Main(void)
{
	int k;

	Sys_Init(115200);
	printf("KEY Input Test #1\n");

	/* 아래 코드 수정 금지 : Port-C Clock Enable */
	Macro_Set_Bit(RCC->AHB1ENR, 2); 

	// KEY(PC13)을 GPIO 입력으로 선언
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);	// INPUT으로 설정
	
	for(;;)
	{
		#if 0
		// KEY가 눌렸으면 LED(PA5) ON, 안 눌렸으면 OFF
		// 여기서 버튼은 pull up으로 간다고 했으니까..
		// >> if / else / 삼향연산자 사용 안 하는 게 좋다.
		if(Macro_Check_Bit_Set(GPIOC->IDR, 13)){
			LED_Off();
		} else {
			LED_On();
		}
		#else
		k = Macro_Extract_Area(~GPIOC->ODR, 0x1, 13);	// c99문법: 변수를 아무곳에서 선언하는 것
		// int k = Macro_Extract_Area(~GPIOC->ODR, 0x1, 13);	// c99문법: 변수를 아무곳에서 선언하는 것
		Macro_Write_Block(GPIOA->ODR, 0x1, k, 5)

		#endif
	}
}

#endif

/* Key에 의한 LED Toggling */

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("KEY Input Toggling #1\n");

	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);

	for(;;)
	{
		// KEY(PC13)이 눌릴때마다 LED(PA5)가 Toggling하도록 코드 작성		
		
	}
}

#endif
