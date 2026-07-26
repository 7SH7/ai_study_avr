#define F_PWM			(20000)		// 초당 몇 개 분주비 만들 수 있나 => 20KHz
#define TIM5_ARR		(unsigned int) ((TIMXCLK / F_PWM + 0.5) - 1)	// 분주비
#define TIM5_MAX		(0xffffffffu)

extern void TIM5_Out_Init(void);
