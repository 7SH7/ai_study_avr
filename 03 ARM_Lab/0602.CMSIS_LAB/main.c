#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
  SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
}

void Main(void)
{
	volatile int i;

	Sys_Init(115200);
	printf("CMSIS Based Register Define\n");

	// LED Pin을 출력으로 설정


	for(;;)
	{
		// LED ON


		for(i=0; i<0x40000; i++);

		// LED OFF


		for(i=0; i<0x40000; i++);
	}
}
