#include "stm32f4xx.h"
#include "option.h"
#include "macro.h"
#include "malloc.h"
#include "motor.h"

// Uart.c

extern void Uart2_Init(int baud);
extern void Uart2_Send_Byte(char data);

extern void Uart1_Init(int baud);
extern void Uart1_Send_Byte(char data);
extern void Uart1_Send_String(char *pt);
extern void Uart1_Printf(char *fmt,...);
extern char Uart1_Get_Char(void);
extern char Uart1_Get_Pressed(void);

// SysTick.c

extern void SysTick_Run(unsigned int msec);
extern int SysTick_Check_Timeout(void);
extern unsigned int SysTick_Get_Time(void);
extern unsigned int SysTick_Get_Load_Time(void);
extern void SysTick_Stop(void);

// Led.c

extern void LED_Init(void);
extern void LED_On(void);
extern void LED_Off(void);

// Clock.c

extern void Clock_Init(void);

// Key.c

extern void Key_Poll_Init(void);
extern int Key_Get_Pressed(void);
extern int Key_Get_Released(void);
extern void Key_Wait_Key_Released(void);
extern void Key_Wait_Key_Pressed(void);

// Timer.c

extern void TIM2_Delay(int time);
extern void TIM2_Stopwatch_Start(void);
extern unsigned int TIM2_Stopwatch_Stop(void);
extern void TIM4_Repeat(int time);
extern void TIM4_1Pls(int time);
extern int TIM4_Check_Timeout(void);
extern void TIM4_Stop(void);
//extern void TIM2_Oneshot(int time);
extern void TIM2_1Pls(int time);
extern int TIM2_Check_Timeout(void);
extern void TIM2_Stop(void);
extern void TIM5_Out_PWM_Generation(unsigned short freq, int duty, int a0, int a1);
extern void TIM5_Out_Init(void);
extern void TIM5_Out_Init(void);
extern void TIM5_Out_Stop(void);

// motor.c

extern void MOTOR_Init(void);
extern void motor_cw(void);
extern void motor_ccw(void);
extern void motor_stop(void);
// extern void motor_inverse(void);