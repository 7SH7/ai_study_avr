/*
 * uart0.c
 *
 * Created: 2026-06-16 오전 9:57:57
 *  Author: kccistc
 */ 
#include "uart0.h"
#include "ds1307.h"

extern int func_state;
extern void (*fp[])(void);

void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing(t_ds1307* ds1307);

volatile int rtc_update_flag = 0;

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

void pc_command_processing(t_ds1307* ds1307)
{
	if (front != rear)    // data가 rx_buff에 존재 하는지 check
	{
		printf("%s", rx_buff[front]);  // printf("%s", &rx_buff[front][0])
		if (strncmp((char *) rx_buff[front], "setrst", 6) == 0)
		{
			sscanf(rx_buff[front], "setrst%2hhu%2hhu%2hhu%2hhu%2hhu%2hhu",
			&ds1307->year,
			&ds1307->month,
			&ds1307->date,
			&ds1307->hours,
			&ds1307->minutes,
			&ds1307->seconds);

			rtc_update_flag = 1;
		}

		memset(rx_buff[front], 0, sizeof(rx_buff[front]));
        
		front = (front + 1) % QUEUE_SIZE;  
	}
}
