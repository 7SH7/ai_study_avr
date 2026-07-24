#include "device_driver.h"

void init_motor(void)
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
}

void stop_motor(void)
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
}

void turn_motor_ccw()
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
}

void turn_motor_cw()
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
}

void change_motor_state()
{
	Macro_Invert_Area(GPIOA->ODR, 0x3, 0);
}