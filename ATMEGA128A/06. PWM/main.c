/*
 * 06. PWM.c
 *
 * Created: 2026-06-18 오전 10:23:49
 * Author : kccistc
 */ 

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