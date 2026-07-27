#define TIM2_TICK         	(20) 				// usec
#define TIM2_FREQ 	  		(1000000/TIM2_TICK)	// Hz
#define TIME2_PLS_OF_1ms  	(1000/TIM2_TICK)
#define TIM2_MAX	  		(0xffffffffu)

#define TIM3_FREQ 	  			(8000000) 	      	// Hz
#define TIM3_TICK	  			(1000000/TIM3_FREQ)	// usec
#define TIME3_PLS_OF_1ms  		(1000/TIM3_TICK)

#define TIM4_TICK (9600)	// 달걀 1판
#define TIM4_FRAG (TIMXCLK / TIM4_TICK)	// 초당 몇 개?
#define TIM4_PLS_OF_1ms (TIM4_FRAG / 1000)
#define TIM4_MAX (0xffff)

#define F_PWM			(20000)		// 초당 몇 개 분주비 만들 수 있나 => 20KHz
#define TIM5_ARR		(unsigned int) ((TIMXCLK / F_PWM + 0.5) - 1)	// 분주비
#define TIM5_MAX		(0xffffffffu)

extern void TIM5_Out_Init(void);
extern int TIM2_Interrupt_Enable(int en, int time);
extern int TIM4_Interrupt_Enable(int en, int time);
