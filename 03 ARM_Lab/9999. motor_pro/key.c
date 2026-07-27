#include "device_driver.h"
#include "motor.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>

extern volatile int TIM4_Expired;
extern volatile int Uart_Data_In;
extern volatile unsigned char Uart_Data;
extern volatile int speed;

void do_usart_work(void)
{
	// pwm으로 돌아야하지..
	if(Uart_Data == 'F' || Uart_Data == 'f')
	{
		motor_state = CW;
	} else if(Uart_Data == 'R' || Uart_Data == 'r')
	{
		motor_state = CCW;
	} else if('0' <= Uart_Data && Uart_Data <= '9')
	{
		speed = 50 + 5 * (Uart_Data - '0');
	}

	TIM5_Set_Duty_Key(speed, motor_state);
}

void do_key_work(void)
{
	// pwm 기반으로 돌아야해.
	printf("here: %d\n", motor_state);

	if(motor_state == STOP)
		motor_state = CW;
	else 
		motor_state = motor_state == CW ? CCW : CW;

	TIM5_Set_Duty_Key(speed, motor_state);
}

int Key_Get_Pressed(void)
{
	return Macro_Check_Bit_Clear(GPIOC->IDR, 13);	
}

// 외부 interrupt도 다른 것과 동일하게 enable func 1개, handler 1개
void Key_ISR_Enable(int en)
{
	if(en)
	{
		Macro_Set_Bit(RCC->AHB1ENR, 2);
		Macro_Write_Block(GPIOC->MODER, 0x3 , 0x0, 26);

		// 외부 소스 set 
		Macro_Set_Bit(RCC->APB2ENR, 14);	// 얘는 왜 필요하지?
		Macro_Write_Block(SYSCFG->EXTICR[3], 0xf, 0x2, 4);	// 13번 포트 사용

		Macro_Set_Bit(EXTI->FTSR, 13);	// falling edge (버튼 눌렸을 때)
		Macro_Set_Bit(EXTI->RTSR, 13);	// rising edge (버튼 떼었을 때)
		EXTI->PR = (0x1 << 13);			// pending clear

		// 내부 소스 set
		NVIC_ClearPendingIRQ(40);
		Macro_Set_Bit(EXTI->IMR, 13);
		NVIC_EnableIRQ(40);

	} else {
		NVIC_DisableIRQ(40);
	}
}