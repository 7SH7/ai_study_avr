///*
 //* uart1.c
 //*
 //* Created: 2026-06-22 오전 10:38:31
 //*  Author: kccistc
 //*/ 
//
//#include "uart1.h"
//
//extern void UART0_transmit(uint8_t data);
//
//volatile uint8_t bt_data;  // bluetooth data
//
//void init_uart1(void);
//void UART1_transmit(uint8_t data);
//
//// p278 표 12-3: PC로부터 1byte가 들어오면 자동적으로 이곳으로 진입한다.
//ISR(USART1_RX_vect)
//{
	//bt_data = UDR1;		// UDR1의 내용이 data에 복사된 후, UDR1의 내용은 빈 상태로 된다.
	//UART0_transmit(bt_data);	// BT로부터 들어온 byte를 확인하기 위해서 comport로 출력한다.
//}
//
///*
//1. 전송 속도: 9600bps
//2. start / stop 비트
//3. RX(수신): interrupt로 설정
//*/
//void init_uart1(void)
//{
	//UBRR1H = 0x00;
	//UBRR1L = 207;  // 9600bps (표8-9)
	//UCSR1A |= 1 << U2X1;  // 2배속 설정 (sampling 8)
	//// UART1 를 송신, 수신이 다 가능하고 RX INT 가 가능하도록 설정한다.
	//UCSR1B |= 1 << RXEN1 | 1 << TXEN1 | 1 << RXCIE1;
//}
//
//// UART1로 1byte 전송하는 함수
//void UART1_transmit(uint8_t data)
//{
	//while(!(UCSR1A & (1 << UDRE1)))	// data가 송신 중이면, 송신이 끝날때까지 기다림.
	//{
		//;	// no operation
	//}
	//
	//UDR1 = data;  // HW 전송 register에 data 송신한다.
//}