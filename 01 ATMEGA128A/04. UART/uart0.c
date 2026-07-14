/*
 * uart0.c
 *
 * Created: 2026-06-16 오전 9:57:57
 *  Author: kccistc
 */ 
#include "uart0.h"

extern int func_state;
extern void (*fp[])(void);

void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing(void);

// p278 표 12-3
// PC로부터 1byte가 들어오면 자동적으로 이곳으로 진입한다.
// led_all_on\n 이면, 11번 이곳으로 진입한다.
ISR(USART0_RX_vect)
{
	volatile uint8_t data;
	volatile static int i=0;
	
	data = UDR0;		// UDR0의 내용이 data에 복사된 후, UDR0의 내용은 빈 상태로 된다.
	
	if(data == '\n' || data == '\r')
	{
		if( (rear + 1) % QUEUE_SIZE == front % QUEUE_SIZE)
			return;	//	queue full 상태
			
		rx_buff[rear][i] = '\0';	// 문장의 끝인 null을 넣는다.
		i=0;	// 다음 string을 저장하기 위해 i=0으로 할당한다.
		rear = (rear + 1) % QUEUE_SIZE;	// 0 ~ 9
	}
	else
	{
		if( (rear + 1) % QUEUE_SIZE == front % QUEUE_SIZE)
			return;	//	queue full 상태
		
		rx_buff[rear][i++] = data;
	}
}

/*
1. 전송 속도: 9600bps 
2. start / stop 비트 
3. RX(수신): interrupt로 설정
*/
void init_uart0(void)
{
	UBRR0H = 0x00;
	UBRR0L = 207;  // 9600bps (표8-9)
	UCSR0A |= 1 << U2X0;  // 2배속 설정 (sampling 8)
	// UART0 를 송신, 수신이 다 가능하고 RX INT 가 가능하도록 설정한다.
	UCSR0B |= 1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0;
}

// UART0로 1byte 전송하는 함수
void UART0_transmit(uint8_t data)
{
	while(!(UCSR0A & (1 << UDRE0)))	// data가 송신 중이면, 송신이 끝날때까지 기다림.	
	{
		;	// no operation
	}
	
	UDR0 = data;  // HW 전송 register에 data 송신한다.
}

void pc_command_processing(void)
{
	if(front != rear) // data가 들어있는거지
	{
		printf("%s", rx_buff[front]);	
		if(strncmp((char*) rx_buff[front], "led_shift_left_on", strlen("led_shift_left_on")) == 0)
		{
			func_state = 0;
		}
		else if(strncmp((char*) rx_buff[front], "led_shift_right_on", strlen("led_shift_right_on")) == 0)
		{
			func_state = 1;
		}
		else if(strncmp((char*) rx_buff[front], "led_shift_left_keep_on", strlen("led_shift_left_keep_on")) == 0)
		{
			func_state = 2;
		}
		else if(strncmp((char*) rx_buff[front], "led_shift_right_keep_on", strlen("led_shift_right_keep_on")) == 0)
		{
			func_state = 3;
		}
		else if(strncmp((char*) rx_buff[front], "led_flower_on", strlen("led_flower_on")) == 0)
		{
			func_state = 4;
		}
		else if(strncmp((char*) rx_buff[front], "led_flower_off", strlen("led_flower_off")) == 0)
		{
			func_state = 5;
		}
	}
	fp[func_state]();
}		
		
		
		