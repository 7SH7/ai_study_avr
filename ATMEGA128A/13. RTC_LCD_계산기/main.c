/*
 * 13. RTC_LCD_계산기.c
 *
 * Created: 2026-07-01 오전 9:38:26
 * Author : kccistc
 */ 

#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

uint8_t MODE = 4;

int main(void)
{
	LCD_init();
	
	LCD_write_string("HELLO LCD!");
	
	_delay_ms(1000);
	
//	LCD_clear();
	
    /* Replace with your application code */
    while (1) 
    {
		return 0;
    }
}

