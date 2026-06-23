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
volatile uint8_t data;


ISR(USART0_RX_vect)
{
	data = UDR0;		// UDR0의 내용이 data에 복사된 후, UDR0의 내용은 빈 상태로 된다.
    PORTA ^= (1 << 0);
	UART0_transmit(data);	
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
	//UBRR0L = 51;  // 9600bps (표8-9)
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

		
		
		