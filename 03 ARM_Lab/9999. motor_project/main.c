#include "device_driver.h"
#include <stdio.h>

// #define MOTOR_STOP_TIME	3000
// #define MOTOR_STOP_TIME_REF	1000

typedef enum{
	MOTOR_STOP = -1,
	MOTOR_CW,
	MOTOR_CCW
} motor_state_t;

motor_state_t motor_state;

int key_state = 0;

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
	Key_Poll_Init();
	// MOTOR_Init();
	TIM5_Out_Init();
}



// Mini Project

#pragma region 필요없는 코드
#if 0

void Main(void)
{
	int lock = 0;
	int re_cnt = 0;
	int rst = 0;

	Sys_Init(115200);
	printf("Motor Control Project\n");
	
	for(;;)
	{
		
		if(lock == 0 && Macro_Check_Bit_Clear(GPIOC -> IDR, 13))
		{
			lock = 1;
			TIM4_Repeat(MOTOR_STOP_TIME_REF);
			
		}

		else if(lock == 1 && Macro_Check_Bit_Set(GPIOC -> IDR, 13))
		{
			if(rst)
			{
				lock = 0;
				rst = 0;
			}
			else
			{
				if(!Macro_Extract_Area(GPIOA -> ODR, 0x3, IN_1A))
					motor_cw();
				else
					motor_inverse();

				lock = 0;
				TIM4_Stop();
				re_cnt = 0;
			}
			
		}
		if(TIM4_Check_Timeout())
		{
			re_cnt ++;
			if(re_cnt == (MOTOR_STOP_TIME / MOTOR_STOP_TIME_REF))
			{
				motor_stop();
				re_cnt = 0;
				rst = 1;
			}
		}

	}
}

#endif

#pragma endregion 필요없는 코드

#if 1

void Main(void)
{
	int lock = 0;
	motor_state = MOTOR_STOP;

    Sys_Init(115200);
    printf("start\n");

	for(;;)
	{
		if(!key_state)
		{
			//printf("key_state = 0");
			switch(motor_state)
			{
				case -1:
					motor_stop();
					break;
				case 0:
					printf("cw   ");
					motor_cw();
					break;
				case 1:
					printf("ccw   ");
					motor_ccw();
					break;
			}

			if(lock ==1 && Key_Get_Released())
				lock = 0;

			else if (lock == 0 && Key_Get_Pressed()) // 1pulse
			{
				lock = 1;
				key_state = 1;
				TIM2_1Pls(3000);
			}
		}

		else // !key_state == 1
		{
			if(TIM2_Check_Timeout())
			{
				motor_state = MOTOR_STOP;
				key_state = 0;
			}

			else if(lock == 1 && Key_Get_Released())
			{
				TIM2_Stop();
				
				if(motor_state == MOTOR_STOP)
				{
					motor_state = MOTOR_CW;
					key_state = 0;
					continue;
				}

				else
				{
					printf("motor toggle");
					motor_stop();

					if(TIM4_Check_Timeout())
					{
						printf("TIM4 check");
						motor_state ^= 1;
						key_state = 0;
					}

					else if(Macro_Check_Bit_Clear(TIM4 -> CR1, 0))
					{
						printf("TIM4 START");
						TIM4_1Pls(1000);
					}	
				}

			}
		}
	}
}
#else


void Main(void)
{
	Sys_Init(115200);
	printf("\nTest\n");

	int state = 0;   

	Macro_Write_Block(GPIOA->MODER, 0xf, 0x5, 0);
	Macro_Write_Block(GPIOA->OTYPER, 0x3, 0x0, 0);
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);  

	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);   
	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 26);   


	for(;;)
	{
		if(!Macro_Check_Bit_Set(GPIOC->IDR, 13))
		{
			state = (state + 1) % 4; 

			switch(state)
			{
				case 0:   
					Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
					break;
				case 1:   
					Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
					break;
				case 2:
					Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
					break;
				case 3:
					Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
					break;
				default: 
					state = 0;
					Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
					break;
			}

			while(!Macro_Check_Bit_Set(GPIOC->IDR, 13));
			
		}
	}
}


#endif