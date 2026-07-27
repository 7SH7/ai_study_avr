#include "device_driver.h"
#include "uart.h"
#include "key.h"
#include "timer.h"
#include "motor.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();		// timer 사용을 위해서
	Uart2_Init(baud);	// usart 사용을 위해서
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();			// led 사용을 위해서
}

volatile int Key_Pressed = 0;
volatile int Uart_Data_In = 0;
volatile unsigned char Uart_Data = 0;
volatile int TIM4_Expired = 0;
volatile int TIM2_Expired = 0;
volatile int long_press = 0;
motor_state_t motor_state = STOP;

// 스위치: PC13									>> INPUT
// PA0, PA1 :: PA0: 1A / PA1: 2A			   >> OUTPUT >> 모터 움직이는거..  

void init_in_gpio(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 2);
	GPIOC->MODER = (0x0 << 27) | (0x0 << 26);
	GPIOC->PUPDR = (0x0 << 27) | (0x1 << 26);	// pull up
}


void Main(void)
{
	Sys_Init(115200);
	printf("start\n");

	// init_out_gpio();	// key init (PA0, PA1): 버튼 클릭으로 처리 >> 차후 pwm으로 변경 필요
	init_in_gpio();		// PC13: 내부 버튼 사용을 위함.
	TIM5_Out_Init();	//  pwm으로 변경
	Key_ISR_Enable(1);
	
	// TODO
	// 1. TIM3으로 방향 바뀔때 500ms 멈추도록 하기
	// 2. USART 적용하기

	for(;;)
	{
		if(uart2_flag)
		{
			// uart2에서 값이 들어온 경우
			// do_usart_work();
		} 

		if(TIM2_Expired)
		{
			motor_state = STOP;
			stop_motor();
			TIM2_Expired = 0;
			long_press = 1;
		}

		if(Key_Pressed)
		{
			Key_Pressed = 0;
			if(long_press) long_press = 0;
			else {
				stop_motor();
				// 여기선 time4 걸어두고, 이후 방향 타도록 하자
				TIM4_Interrupt_Enable(1, 500);
			}
		}

		if(TIM4_Expired)
		{
			TIM4_Expired = 0;
			TIM4_Interrupt_Enable(0, 500);
			do_key_work();
		}		
	}
}
