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

#if 1

#include "device_driver.h"
#include <stdio.h>

// 밑의 코드는 계쏙 돌아간단 말이지..? 누르는것과 무관하게.. >> state가 계쏙 더해져서 처리됨.
// 버튼 누르면 방향만 바꿔줘
// 계속 돌아가게 해. >> volatile 쓰면 될 거 같음
void Main(void)
{
	Sys_Init(115200);
	printf("\nUser Button (PC7) State Control Test\n");

	int state = 0;   

	// 초기화 시키는 것은 bitwise operator 사용하는 게 좋은 듯..
	Macro_Write_Block(GPIOA->MODER, 0xf, 0x5, 0);
	Macro_Write_Block(GPIOA->OTYPER, 0x3, 0x0, 0);
	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);  

	Macro_Set_Bit(RCC->AHB1ENR, 2); 
	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 14);  
	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 14);  

	for(;;)
	{
		if(!Macro_Check_Bit_Set(GPIOC->IDR, 7))   
		{
			state = (state + 1) % 4; 

			switch(stat)
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
			}

			while(!Macro_Check_Bit_Set(GPIOC->IDR, 7));
		}
	}
}


// void Main(void)
// {
// 	Sys_Init(115200);
// 	printf("\nTest\n");

// 	int state = 0;   

// 	Macro_Write_Block(GPIOA->MODER, 0xf, 0x5, 0);
// 	Macro_Write_Block(GPIOA->OTYPER, 0x3, 0x0, 0);
// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);  

// 	Macro_Set_Bit(RCC->AHB1ENR, 2); 
// 	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0, 26);   
// 	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 26);   

// 	for(;;)
// 	{
// 		if(!Macro_Check_Bit_Set(GPIOC->IDR, 13))   
// 		{
// 			if(!Macro_Check_Bit_Set(GPIOC->IDR, 13))
// 			{
// 				state = (state + 1) % 4; 

// 				switch(state)
// 				{
// 					case 0:   
// 						Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
// 						break;
// 					case 1:   
// 						Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
// 						break;
// 					case 2:
// 						Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
// 						break;
// 					case 3:
// 						Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
// 						break;
// 					default: 
// 						state = 0;
// 						Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
// 						break;
// 				}

// 				while(!Macro_Check_Bit_Set(GPIOC->IDR, 13));
				
// 			}
// 		}
// 	}
// }


// void Main(void)
// {
// 	Sys_Init(115200);
// 	printf("\nTest\n");

// 	int state = 0;   

// 	Macro_Write_Block(GPIOA->MODER, 0xf, 0x5 ,0);
// 	Macro_Write_Block(GPIOA->OTYPER, 0x3, 0x0 ,0);
// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);  

// 	// PC7 >> logical input
// 	Macro_Set_Bit(RCC->AHB1ENR, 2);
// 	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0 ,14);
// 	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 14);   

// 	for(;;)
//     {
// 		if(!Macro_Check_Bit_Set(GPIOC->IDR, 7))   // 눌림 감지
// 		{
// 			state = (state + 1) % 4; 

// 			switch(state)
// 			{
// 				case 0:   // 시계
// 					Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
// 					break;
// 				case 1:   
// 					Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
// 					break;
// 				case 2:   // 반시계
// 					Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
// 					break;
// 				case 3:   
// 					Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
// 					break;
// 			}

// 			while(!Macro_Check_Bit_Set(GPIOC->IDR, 7));
// 		}
//     }
// }

// void Main(void)
// {
// 	Sys_Init(115200);
// 	printf("\nTest\n");

// 	Uart1_Init(115200);

// 	int flag = 0;

// 	Macro_Write_Block(GPIOA->MODER, 0x15, 0x5 ,0);
// 	Macro_Write_Block(GPIOA->OTYPER, 0x3, 0x0 ,0);
// 	Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);

// 	// PC7 >> logical input
// 	Macro_Set_Bit(RCC->AHB1ENR, 2);
// 	Macro_Write_Block(GPIOC->MODER, 0x3, 0x0 ,14);
// 	Macro_Write_Block(GPIOC->PUPDR, 0x3, 0x1, 14);   
    
// 	for(;;)
//     {
// 		if(!Macro_Check_Bit_Set(GPIOC->IDR, 7)) 	// 1이면 떼고 있을때
// 		{
// 			if(flag == 0)
// 			{
// 				Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);  
// 				flag = 1;
// 			}
// 			while(!Macro_Check_Bit_Set(GPIOC->IDR, 7));

// 			if(flag == 1)
// 			{
// 				Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);  
// 				flag = 0;
// 			}
// 		}
//     }
// }



	// for(;;)
	// {
	// 	char x;

	// 	//수신?
	// 	while(!Macro_Check_Bit_Set(USART1->SR, 5)); 
	// 	// x = dr
	// 	x = USART1->DR;
		
	// 	// 송신?
	// 	while(!Macro_Check_Bit_Set(USART1->SR, 7)); 
	// 	// dr = x;
	// 	USART1->DR = x;

	// 	if(x == 'S')
	// 	{
	// 		// PA0, 1  > 1a, 2a >> 10
	// 		Macro_Write_Block(GPIOA->ODR, 0x3, 0x0, 0);
	// 	} else if(x == 'F')
	// 	{
	// 		Macro_Write_Block(GPIOA->ODR, 0x3, 0x2, 0);
	// 	} else if(x == 'R')
	// 	{
	// 		Macro_Write_Block(GPIOA->ODR, 0x3, 0x1, 0);
	// 	}
	// }
// }

#endif