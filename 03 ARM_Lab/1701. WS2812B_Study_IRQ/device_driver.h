#include "stm32f4xx.h"
#include "option.h"
#include "macro.h"
#include "malloc.h"

// Uart.c

extern void Uart2_Init(int baud);
extern void Uart2_Send_Byte(char data);
extern void Uart2_RX_Interrupt_Enable(int en);

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
extern void Key_Wait_Key_Released(void);
extern void Key_Wait_Key_Pressed(void);
extern void Key_ISR_Enable(int en);

// Timer.c

extern void TIM2_Delay(int time);
extern void TIM2_Stopwatch_Start(void);
extern unsigned int TIM2_Stopwatch_Stop(void);
extern void TIM4_Repeat(int time);
extern int TIM4_Check_Timeout(void);
extern void TIM4_Stop(void);
extern void TIM4_Change_Value(int time);
extern void TIM4_Repeat_Interrupt_Enable(int en, int time);
extern void TIM3_Out_Init(void);
extern void TIM3_Out_Freq_Generation(unsigned short freq);
extern void TIM3_Out_Stop(void);

// WS2812B (TIM3_CH2 PWM + DMA1 Stream2/Channel5)
// WS2812B 전송 시작/정지 함수와 DMA 결과 확인용 플래그
extern void WS2812_DMA_Start(void);
extern void WS2812_DMA_Stop(void);
extern volatile int WS2812_DMA_Done;
extern volatile int WS2812_DMA_Error;

// ---------
#define LED_COUNT (4)
#define BIT_COUNT (24 * LED_COUNT)
#define RES_PERIOD (242)                // 240 complete LOW slots (300us) + 2 DMA pipeline guard slots
                                        // 실제 LOW 240주기와 CCR preload/DMA 완료 시점 보정용 2주기
#define LOOKUP_TABLE_SIZE (BIT_COUNT + RES_PERIOD)
