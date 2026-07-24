#include "device_driver.h"
#include "motor.h"
#include <stdio.h>

void do_key_work(void)
{
	// pwm 기반으로 돌아야해.
	// 멈춰진 상태야.. 그럼 
	if(motor_state == STOP)
	{
		// cw 돌려.
		printf("here1: %d\n", motor_state);
		turn_motor_cw();
		motor_state = CW;
	} else {
		// cw <-> ccw  :: bit만 바꿔줘..
		change_motor_state();
		motor_state = motor_state == CW ? CCW : CW;	// 한번씩 바뀌어야하는데, 계속 바뀌는게 문제임.
		printf("here2: %d\n", motor_state);
	}
}


// 밑은 base set

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);
}

int Key_Get_Pressed(void)
{
	return Macro_Check_Bit_Clear(GPIOC->IDR, 13);	
}

void Key_Wait_Key_Pressed(void)
{
	while(!Macro_Check_Bit_Clear(GPIOC->IDR, 13));
}

void Key_Wait_Key_Released(void)
{
	while(!Macro_Check_Bit_Set(GPIOC->IDR, 13));
}

void Key_ISR_Enable(int en)
{
	if(en)
	{
		Macro_Set_Bit(RCC->AHB1ENR, 2); 
		Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);

		Macro_Set_Bit(RCC->APB2ENR, 14); 
		Macro_Write_Block(SYSCFG->EXTICR[3], 0xf, 0x2, 4);

		Macro_Set_Bit(EXTI->FTSR, 13);
		EXTI->PR = 0x1 << 13;
		
		NVIC_ClearPendingIRQ((IRQn_Type)40);
		Macro_Set_Bit(EXTI->IMR, 13);
		NVIC_EnableIRQ((IRQn_Type)40);
	}

	else
	{
		NVIC_DisableIRQ((IRQn_Type)40);
	}
}
