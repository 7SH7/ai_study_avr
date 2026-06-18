/*
 * 06. PWM.c
 *
 * Created: 2026-06-18 오전 10:23:49
 * Author : kccistc
 */ 

#if 1

#define F_CPU 16000000UL  // 16MHz
#include <avr/io.h>
#include <util/delay.h>

#define LED_TIME 20

extern void init_led();

void turn_on_LED_inPWM_manner(int dim)
{
	int i;
	
	PORTA = 0xFF;	// LED 켜기
	
	for(int i = 0 ; i < 256; i++)
	{
		if(i>dim) PORTA = 0x00;
		_delay_us(LED_TIME);
	}
}

int main(void)
{
	
	init_led();
	
	DDRB = 0x01;	// DDR 방향 출력
	
	int dim = 0;
	int direction = 1;
	
	while(1)
	{
		turn_on_LED_inPWM_manner(dim);
		
		dim += direction;
		
		if(dim == 0) direction = 1;
		if(dim == 255) direction = -1;
	}

	return 0;
	
}

#endif

#if 0

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int dim = 0;
	int direction = 1;

	init_led();
	
	// 파형 출력 핀인 PB4(OC0 핀)을 출력으로 설정
	DDRB |= (1 << PB4);
	
	// 타이머/카운터 0번을 고속 PWM 모드로 설정
	TCCR0 |= (1 << WGM01) | (1 << WGM00);
	// 비반전모드
	TCCR0 |= (1 << COM01);
	// 분주비를 1024로 설정
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	
	while(1)
	{
		OCR0 = dim;	// 듀티 사이클 설정
		_delay_ms(10);
		
		dim += direction;
		
		if(dim==0) direction = 1;
		if(dim==255) direction = -1;
	}
	
}

#endif
#if 0

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// 파형 출력핀인 PB5(0C1A핀), PB6핀(OC1B핀)을 출력으로 설정
	DDRB |= (1 << PB5) | (1 << PB6);
	
	// 타이머/카운터 1번을 8비트 위상 교정 PWM으로 설정
	TCCR1A |= (1 << WGM10);
	
	
	
	int dim = 0;
	int direction = 1;

	init_led();
	
	// 파형 출력 핀인 PB4(OC0 핀)을 출력으로 설정
	DDRB |= (1 << PB4);
	
	// 타이머/카운터 0번을 고속 PWM 모드로 설정
	TCCR0 |= (1 << WGM01) | (1 << WGM00);
	// 비반전모드
	TCCR0 |= (1 << COM01);
	// 분주비를 1024로 설정
	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	
	while(1)
	{
		OCR0 = dim;	// 듀티 사이클 설정
		_delay_ms(10);
		
		dim += direction;
		
		if(dim==0) direction = 1;
		if(dim==255) direction = -1;
	}
	
}


#endif