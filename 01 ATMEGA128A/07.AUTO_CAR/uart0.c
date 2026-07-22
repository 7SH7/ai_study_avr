/*
 * uart0.c
 *
 * Created: 2026-06-16 오전 9:57:57
 *  Author: kccistc
 */ 
#include "uart0.h"

void init_uart0(void);
void UART0_transmit(uint8_t data);
void pc_command_processing(void);

volatile uint8_t data;

ISR(USART0_RX_vect)
{
	data = UDR0;		
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
	UBRR0L = 207;  // 9600bps 
	UCSR0A |= 1 << U2X0;  // 2배속 설정 
	UCSR0B |= 1 << RXEN0 | 1 << TXEN0 | 1 << RXCIE0;
}

// UART0로 1byte 전송
void UART0_transmit(uint8_t data)
{
	// data가 송신 중이면, 송신이 끝날때까지 기다림.
	while(!(UCSR0A & (1 << UDRE0)))	
	{
		;	
	}
	
	UDR0 = data;  
}

		
		
		