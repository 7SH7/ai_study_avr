#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
}

#if 0
void Main(void)
{
	Sys_Init(115200);
	printf("\nUART Echo-Back Test\n");

	Uart1_Init(115200);

	char x, y;


	while(!Macro_Check_Bit_Set(USART1->SR, 7)); 
	USART1->DR = 'A'; 
	
	while(!Macro_Check_Bit_Set(USART1->SR, 7)); 
	USART1->DR = 'B'; 
	
	while(!Macro_Check_Bit_Set(USART1->SR, 7)); 
	USART1->DR = 'C';

}
#endif

#if 0
void Main(void)
{
	Sys_Init(115200);
	printf("\nUART Echo-Back Test\n");

	Uart1_Init(115200);

	char x, y;

	for(x = 'A'; x <= 'Z'; x++)
	{
		// 송신 버퍼가 비면 x의 글자를 출력

		
		// 수신 버퍼에 글자가 입력되면 y에 글자를 수신


		printf("%c ", y);
	}
}
#endif

#if 0
void Main(void)
{
	Sys_Init(115200);
	printf("\nUART Echo-Back Test\n");

	Uart1_Init(115200);

	for(;;)
	{
		char x;

		//수신?
		while(!Macro_Check_Bit_Set(USART1->SR, 5)); 
		// x = dr
		x = USART1->DR;
		
		// 송신?
		while(!Macro_Check_Bit_Set(USART1->SR, 7)); 
		// dr = x;
		USART1->DR = x;

		
	}

}

#endif

#if 0

#include "device_driver.h"
#include <stdio.h>

// 밑의 코드는 계쏙 돌아간단 말이지..? 누르는것과 무관하게.. >> state가 계쏙 더해져서 처리됨.
// 버튼 누르면 방향만 바꿔줘
// 계속 돌아가게 해. >> volatile 쓰면 될 거 같음
// void Main(void)
// {
// 	Sys_Init(115200);
// 	printf("\nUser Button (PC7) State Control Test\n");

// 	int state = 0;   

// 	// 초기화 시키는 것은 bitwise operator 사용하는 게 좋은 듯..
// 	Macro_Write_Block(GPIOA->MODER, 0xf, 0x5, 0);
// 	Macro_Write_Block(GPIOA->OTYPER, 0x3, 0x0, 0);
// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);  

// 	Macro_Set_Bit(RCC->AHB1ENR, 2); 
// 	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 14);  
// 	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 14);  

// 	for(;;)
// 	{
// 		if(!Macro_Check_Bit_Set(GPIOC->IDR, 7))   
// 		{
// 			state = (state + 1) % 4; 

// 			switch(state)
// 			{
// 				case 0:   
// 					Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
// 					break;
// 				case 1:   
// 					Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
// 					break;
// 				case 2:
// 					Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
// 					break;
// 				case 3:
// 					Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
// 					break;
// 			}

// 			while(!Macro_Check_Bit_Set(GPIOC->IDR, 7));
// 		}
// 	}
// }

#pragma region 내부버튼
// 처음은 stop
// 버튼 누르면, cw > ccw  :: 방향 전환때마다 delay(1)정도
// 추가 문제) switch를 stop에서 누르면 방향이 바뀌어.
// switch를 3sec 이상 누르면 off가 되도록.  >> timer2 사용.

// void stop()
// {
// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);  
// }

// void rotate_direction(int flag)
// {
// 	if(flag == 0)
// 	{
// 		Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);  
// 	} else if(flag == 1)
// 	{
// 		Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);  
// 	}
// }

// void init_GPIO()
// {
// 	Macro_Write_Block(GPIOA->MODER, 0x15, 0x5 ,0);
// 	Macro_Write_Block(GPIOA->OTYPER, 0x3, 0x0 ,0);
// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
// }

// void init_extern_button()
// {
// 	Macro_Set_Bit(RCC->AHB1ENR, 2);
// 	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0 ,14);
// 	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 14);   
// }


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
}
#pragma endregion 내부버튼


#pragma region 외부버튼


// void stop()
// {
// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);  
// }

// void rotate_direction(int flag)
// {
// 	if(flag == 0)
// 	{
// 		Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);  
// 	} else if(flag == 1)
// 	{
// 		Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);  
// 	}
// }

// void init_GPIO()
// {
// 	Macro_Write_Block(GPIOA->MODER, 0x15, 0x5 ,0);
// 	Macro_Write_Block(GPIOA->OTYPER, 0x3, 0x0 ,0);
// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
// }

// void init_extern_button()
// {
// 	Macro_Set_Bit(RCC->AHB1ENR, 2);
// 	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0 ,14);
// 	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 14);   
// }

// void Main(void)
// {
// 	Sys_Init(115200);
// 	printf("\nTest\n");

// 	int flag = 0;

// 	init_GPIO();
// 	init_extern_button();
    
// 	for(;;)
//     {
// 		if(!Macro_Check_Bit_Set(GPIOC->IDR, 7)) 	// 1이 아님. > 눌린 시점
// 		{
// 			flag++;
// 			rotate_direction(flag);
// 			// if(flag == 0)
// 			// {
// 			// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);  
// 			// 	flag = 1;
// 			// }
			
// 			// if(flag == 1)
// 			// {
// 			// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);  
// 			// 	flag = 0;
// 			// }
// 		}
// 		while(!Macro_Check_Bit_Set(GPIOC->IDR, 7));
//     }
// }

#pragma endregion 외부버튼

#endif

// todo: 3초 이상 버튼 눌려있으면 stop
// 그 외엔 돌리기
// delay 사용하기
// todo: uart 사용해서 scanf 구현하기

#if 1
// 스위치: PC13									>> INPUT
// PA0, PA1 :: PA0: 1A / PA1: 2A			   >> OUTPUT >> 모터 움직이는거..  

#define TIM2_MAX    (0xffffffff)	// TIM2
#define TIM2_TICK	(20)   // 주기 us
#define TIM2_FRAG	(1000000. / TIM2_TICK)   // 진동수(pulse) Hz
#define TIM2_1ms_FRAG  (TIM2_FRAG / 1000.)	// 1ms의 pulse

void init_out_gpio(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 0);
	GPIOA->MODER = (0x0 << 3) | (0x1 << 2) | (0x0 << 1) | (0x1 << 0);
	GPIOA->OTYPER = (0x1 << 1) | (0x1 << 0);
}

void init_in_gpio(void)
{
	Macro_Set_Bit(RCC->AHB1ENR, 2);
	GPIOC->MODER = (0x0 << 27) | (0x0 << 26);
	GPIOC->PUPDR = (0x0 << 27) | (0x1 << 26);	// pull up
}

void strat_stopwatch(void)
{
	// timer2 사용 set
	Macro_Set_Bit(RCC->APB1ENR, 0);			// tim2 en

	TIM2->CR1 = (0x1 << 4) | (0x1 << 3);	// down count + 1회만 돌리는

	// TIMXCLK / (희망하는 진동수) = 분주기
	TIM2->PSC = (unsigned int)(TIMXCLK / TIM2_FRAG + 0.5) - 1; 	// PSC_buf에서 +1로 분주기 해주니까..
	TIM2->ARR = TIM2_MAX;
	
	// 메뉴얼 모드 > 값 수정 시, 바로 작동
	Macro_Set_Bit(TIM2->EGR, 0);

	// timer 사용 set
	Macro_Set_Bit(TIM2->CR1, 0);	// CEN = 1 >> T2시작
}

unsigned int stop_stopwatch(void)
{
	unsigned int time = 0;

	Macro_Clear_Bit(TIM2->CR1, 0);	// clear 해주면, 멈춤.
	time = (TIM2_MAX - TIM2->CNT) * TIM2_TICK;

	return time;
}

void delay_stopwatch(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);
	TIM2->CR1 = (0x1 << 4) | (0x0 << 3); 	// delay니까 repeat이지 않나..
	
	TIM2->PSC = (unsigned int)(TIMXCLK / TIM2_FRAG + 0.5) - 1;
	unsigned int pls = time * TIM2_1ms_FRAG;
	int n = pls / TIM2_MAX;
	int m = pls % TIM2_MAX;
	int i;

	for(i = 0; i < n; i++)
	{
		// 여기서 한 일
		TIM2->ARR = TIM2_MAX;
		Macro_Set_Bit(TIM2->EGR, 0);
		Macro_Clear_Bit(TIM2->SR, 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(!Macro_Check_Bit_Set(TIM2->SR, 0));
	}

	// 동일하게 여기서도
	TIM2->PSC = m;	// m분주
	Macro_Set_Bit(TIM2->EGR, 0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);
	while(!Macro_Check_Bit_Set(TIM2->SR, 0));

	Macro_Set_Bit(TIM2->EGR, 0)	// 작동 될 때, PSC랑 같이 SET 되어야 함.

	Macro_Set_Bit(TIM2->CR1, 0);	// enable > TIM2 작동 시작
	
}

void init_motor(void)
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
}

void stop_motor(void)
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
}

void turn_motor(int flag)
{
	if(flag == 0)
	{
		Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
	} else if(flag == 1)
	{
		Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
	}
}

void turn_left_motor()
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
}

void turn_right_motor()
{
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
}

void Main(void)
{
	int state = -1;
	int flag = 0;

	init_out_gpio();
	init_in_gpio();
	init_motor();

	for(;;)
	{
		if(flag == 0 && !Macro_Check_Bit_Set(GPIOC->IDR, 13))	
		{
			flag = 1;
			turn_left_motor();
		}else if(flag == 1 && !Macro_Check_Bit_Set(GPIOC->IDR, 13))	
		{
			flag = 0;
			turn_right_motor();
		}

	}
}


#endif