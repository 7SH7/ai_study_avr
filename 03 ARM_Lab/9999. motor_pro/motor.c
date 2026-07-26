#include "device_driver.h"
#include "timer.h"
#include <stdio.h>

void init_motor(void)
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
}

void stop_motor(void)
{
	// Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
	TIM5->CCR1 = 0;
	TIM5->CCR2 = 0;
}

// PWM을 하는 이유.. MOTOR..
// 기본 set은 duty가 50..
void TIM5_Set_Duty_Key(int duty, int motor_state)
{
	if(motor_state == CW)
	{
		TIM5->CCR1 = 0;
		TIM5->CCR2 = TIM5_ARR * (duty / 100.); 
	} else if(motor_state == CCW)
	{
		TIM5->CCR1 = TIM5_ARR * (duty / 100.); 
		TIM5->CCR2 = 0;
	}
}

void TIM5_Set_Duty_USART(int duty, int direction, int speed)
{
	// PSC, ARR, CCR 설정 해주기

	// TIM 변경값 적용
	Macro_Set_Bit(TIM5->EGR, 0);
}

void change_motor_state()
{
	Macro_Invert_Area(GPIOA->ODR, 0x3, 0);
}
