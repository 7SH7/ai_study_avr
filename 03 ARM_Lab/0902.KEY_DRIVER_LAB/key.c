#include "device_driver.h"

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);
}

int Key_Get_Pressed(void)
{
	// Key가 눌렸으면 1, 안 눌렸으면 0 리턴
}

void Key_Wait_Key_Pressed(void)
{
	// 키가 눌릴때까지 대기하고 눌리면 리턴
}

void Key_Wait_Key_Released(void)
{
	// 키가 안 눌릴때까지 대기하고 안 눌리면 리턴
}
