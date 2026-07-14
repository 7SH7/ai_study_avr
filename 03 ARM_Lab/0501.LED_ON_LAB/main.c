// 여기에 사용자 임의의 define을 작성하시오

#if 0
// todo: 앞으로 int는 보다 short / long 이거 처리를 해주자.
// todo: 앞으로 unsigned는 무조건 붙이자.
#define GPIOA_MODER  (*(unsigned int*)0x40020000)
#define GPIOA_OTYPER (*(unsigned int*)0x40020004)
#define GPIOA_ODR    (*(unsigned int*)0x40020014)

void Main(void)
{
	// LED GPA[5]를 출력(General Push Pull) 모드로 설정하시오

    GPIOA_MODER = 0x00000400;
    GPIOA_OTYPER = 0x00000000;

    // GPA[5] LED를 ON 시키도록 설정하시오

    GPIOA_ODR = 0x00000020;	
}
#endif

#if 1

#define GPIOA_MODER  (*(unsigned long*)0x40020000)
#define GPIOA_OTYPER (*(unsigned long*)0x40020004)
#define GPIOA_ODR    (*(unsigned long*)0x40020014)

// active low
void Main(void)
{
	// LED GPA[7]를 출력(General Open Drain) 모드로 설정하시오

    GPIOA_MODER = 0x00004000;
    GPIOA_OTYPER = 0x00000080;	/		/ change general open drain

    // GPA[7] LED를 ON 시키도록 설정하시오

    GPIOA_ODR = 0x00000000;	
    // GPIOA_ODR = 0x00000080;	
}
#endif