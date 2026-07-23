#include "device_driver.h"
#include <stdio.h>

void _Invalid_ISR(void)		// 밑에 구현되지 않은 ISR이 있다면, 이게 실행됨.
{
	unsigned int r = Macro_Extract_Area(SCB->ICSR, 0x1ff, 0);
	printf("\nInvalid_Exception: %d!\n", r);
	printf("Invalid_ISR: %d!\n", r - 16);
	for(;;);
}

// ☆ 내가 서비스한 interrupt pending clear >> sub한 다음, main을 해주어야함. (main을 먼저하면, 바로 다시 set 됨)
void EXTI15_10_IRQHandler(void)
{
	// KEY Pressed 메시지 인쇄
	// int key_val = Key_Get_Pressed();
	printf("key pressed\n");
	// KEY(EXTI) Pending Clear
	EXTI->PR = 0x1 << 13;
	// NVIC Pending Clear
	NVIC_ClearPendingIRQ(40);
}
