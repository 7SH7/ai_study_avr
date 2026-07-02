/*
 * lcd.c
 *
 * Created: 2026-07-01 오전 9:41:32
 *  Author: kccistc
 */ 

#include "lcd.h"

void LCD_pulse_enable(void)
{
	LCD_CONTROL_PORT |= (1 << E_PIN);	// E를 HIGH
	_delay_ms(1);
	LCD_CONTROL_PORT &= ~(1 << E_PIN);	// E를 LOW	 >> 하강 에지에서 동작
	_delay_ms(1);
}

// WRITE
void LCD_write_data(uint8_t data)
{
	LCD_CONTROL_PORT |= (1 << RS_PIN);	// RS_PIN을 1로 set: data 담는 register로 select

	if(MODE == 8){
		LCD_DATA_PORT = data;
		LCD_pulse_enable();
	} else{
		LCD_DATA_PORT = data & 0xf0;	// 상위
		LCD_pulse_enable();
		
		LCD_DATA_PORT = (data << 4) & 0xf0;	// 하위
		LCD_pulse_enable();
	}
	_delay_ms(2);
}

void LCD_write_command(uint8_t command)
{
	LCD_CONTROL_PORT &= ~(1 << RS_PIN);	// RS_PIN을 0로 set: command 담는 register로 select

	if(MODE == 8){
		LCD_DATA_PORT = command;
		LCD_pulse_enable();
	} else{
		LCD_DATA_PORT = command & 0xf0;	// 상위
		LCD_pulse_enable();
		
		LCD_DATA_PORT = (command << 4) & 0xf0;	// 하위
		LCD_pulse_enable();
	}
	_delay_ms(2);
}

void LCD_clear(void)
{
	LCD_write_command(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}

void LCD_init(void)
{
	_delay_ms(50);
	
	// 연결 핀을 출력으로
	if(MODE == 8) LCD_DATA_DDR = 0xff;
	else LCD_DATA_DDR = 0xf0;
	LCD_DATA_PORT = 0x00;	
	
	LCD_CONTROL_DDR |= (1 << RS_PIN) | (1 << RW_PIN) | (1 << E_PIN);
	
	// RW를 쓰기 모드로 (0)
	LCD_CONTROL_PORT &= ~(1 << RW_PIN);
	
	if(MODE == 8) LCD_write_command(COMMAND_8_BIT_DISPLAY);
	else{
		LCD_write_command(0x02);
		LCD_write_command(COMMAND_4_BIT_DISPLAY);
	}
	
	// display on/off control > 화면 on/커서off/커서 깜빡이 off
	uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
	LCD_write_command(command);
	
	LCD_clear();
	
	// entry mode set : 출력 후 커서 이동 > 화면 이동은 없음. (띄워준거 뒤로 그냥 이동)
	LCD_write_command(0x06);
}

// READ
void LCD_write_string(char* str)
{
	for(uint8_t idx = 0 ; str[idx] ; idx++)
		LCD_write_data(str[idx]);
}

void LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;	// [0 15]
	row %= 2;	// [0 1]
	
	// 첫째 라인 시작 주소 0x00, 둘째 라인 시작 0x40
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	LCD_write_command(command);	// 커서 이동
}

