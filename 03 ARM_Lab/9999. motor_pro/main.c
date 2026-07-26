#include "device_driver.h"
#include "uart.h"
#include "key.h"
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
motor_state_t motor_state = STOP;

// 스위치: PC13									>> INPUT
// PA0, PA1 :: PA0: 1A / PA1: 2A			   >> OUTPUT >> 모터 움직이는거..  

void init_out_gpio(void)
{
	// Macro_Set_Bit(RCC->AHB1ENR, 0);  // led_init()에서 이미 함.
	GPIOA->MODER |= (0x0 << 3) | (0x1 << 2) | (0x0 << 1) | (0x1 << 0);
	GPIOA->OTYPER |= (0x0 << 1) | (0x0 << 0);
}

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

	init_out_gpio();	// key init (PA0, PA1): 버튼 클릭으로 처리 >> 차후 pwm으로 변경 필요
	init_in_gpio();		// PC13: 내부 버튼 사용을 위함.
	TIM2_Stopwatch_Start();

	for(;;)
	{
		if(uart2_flag)
		{
			// uart2에서 값이 들어온 경우
			// do_usart_work();
		} else if(!uart2_flag && Key_Get_Pressed()) {
			// 버튼으로 처리하는 경우
			do_key_work();
			Key_Wait_Key_Released();
		}
	}
}

#if 0	
	int flag = 0;

	init_out_gpio();
	init_in_gpio();
	init_motor();

	int check_time;
	for(;;)
	{
		if(!Macro_Check_Bit_Set(GPIOC->IDR, 13))
		{
			TIM2_Stopwatch_Start();
			check_time = 0;

			while(!Macro_Check_Bit_Set(GPIOC->IDR, 13))
			{
				int pls = TIM2_TICK * (TIM2_MAX - TIM2->CNT);
				if(pls >= 3000000)
				{
					check_time = 1;
					break;
				}
			}
			TIM2_Stopwatch_Stop();
			if(check_time)
			{
				stop_motor();
			}
			else{
				if(flag == 0)
				{
					turn_left_motor();
					flag = 1;
				} else if(flag == 1)
				{
					turn_right_motor();
					flag = 0;
				}

			}
			while(!Macro_Check_Bit_Set(GPIOC->IDR, 13));
		}
	}
}
#endif
