#include "device_driver.h"

void LED_Init(void)
{
	/* 아래 코드 수정 금지 : Port-A Clock Enable */
	Macro_Set_Bit(RCC->AHB1ENR, 0); 

	// LED를 출력으로 설정하고 초기 OFF
    GPIOA->MODER = (GPIOA->MODER & ~(0x3 << 10)) | (0x01 << 10); // 01을.. MODER5
	GPIOA->OTYPER &= ~(0x1 << 5);
	GPIOA->ODR |= (0x1 << 5);

    LED_Off();

}

void LED_On(void)
{
	// LED On
	GPIOA->ODR = 0x1 << 5; 
}

void LED_Off(void)
{
	// LED Off
	GPIOA->ODR = 0x0 << 5; 
}
