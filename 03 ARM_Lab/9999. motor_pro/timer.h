#define TIM2_TICK         	(20) 				// usec
#define TIM2_FREQ 	  		(1000000/TIM2_TICK)	// Hz
#define TIME2_PLS_OF_1ms  	(1000/TIM2_TICK)
#define TIM2_MAX	  		(0xffffffffu)

#define TIM4_TICK	  		(20) 				// usec
#define TIM4_FREQ 	  		(1000000/TIM4_TICK) // Hz
#define TIME4_PLS_OF_1ms  	(1000/TIM4_TICK)
#define TIM4_MAX	  		(0xffffu)

#define F_PWM			(20000)		// 초당 몇 개 분주비 만들 수 있나 => 20KHz
#define TIM5_ARR		(unsigned int) ((TIMXCLK / F_PWM + 0.5) - 1)	// 분주비
#define TIM5_MAX		(0xffffffffu)

extern void TIM5_Out_Init(void);
extern void TIM2_Stopwatch_Start(void);
extern unsigned int TIM2_Stopwatch_Stop(void);
extern void TIM2_Delay(int time);
extern int TIM2_Interrupt_Enable(int en, int time);