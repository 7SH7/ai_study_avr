/*
 * 10. DS1302.c
 *
 * Created: 2026-06-26 오후 2:39:39
 * Author : kccistc
 */

 #define F_CPU 16000000UL
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>	// sei, cli 등등 함수 내장.
 #include <stdio.h>

 extern void init_uart0(void);
 extern void UART0_transmit(uint8_t data);
 extern void dht11_main(void);
 extern void ds1302_main(void);

 FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);	// printf 사용..


 int main(void)
 {
	 init_uart0();
	 stdout = &OUTPUT;	// 송수신이 하나에서 이뤄지니까..
	
     sei();
		
 	 ds1302_main();
 
 }
 