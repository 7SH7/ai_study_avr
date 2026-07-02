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
	//_delay_ms(1);
	_delay_us(1);
	LCD_CONTROL_PORT &= ~(1 << E_PIN);	// E를 LOW	 >> 하강 에지에서 동작
	//_delay_ms(1);
	_delay_us(1);
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
	_delay_us(50); 
	//_delay_ms(2);
}

void LCD_write_high_nibble(uint8_t data)
{
	LCD_CONTROL_PORT |= (1 << RS_PIN);	// RS_PIN을 1로 set: data 담는 register로 select

	LCD_DATA_PORT = data & 0xf0;	// 상위
	LCD_pulse_enable();
		
	_delay_us(50); 
//	_delay_ms(2);
	
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
	_delay_us(50); 
//	_delay_ms(2);
}

void LCD_clear(void)
{
	LCD_write_command(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}

void LCD_init(void)
{
	// 연결 핀을 출력으로
	LCD_DATA_DDR = 0xf0;
	LCD_DATA_PORT = 0x00;	
	
	LCD_CONTROL_DDR |= (1 << RS_PIN) | (1 << RW_PIN) | (1 << E_PIN);
	
	// RW를 쓰기 모드로 (0)
	LCD_CONTROL_PORT &= ~(1 << RW_PIN);
	
	_delay_ms(20);	// doc 기준 15ms 기다리라고 함
	
	// high nibble을 3번 보내주는 작업을 해야함. > 이유는? doc에서 그렇게 하래.
	LCD_write_high_nibble(0x30);	// RS : RW : DB7 : DB6 : DB5 : DB4 = 0 : 0 : 0 : 0 : 1 : 1
	_delay_ms(5);	// 4.1ms 초과 기다림
	
	LCD_write_high_nibble(0x30);	// RS : RW : DB7 : DB6 : DB5 : DB4 = 0 : 0 : 0 : 0 : 1 : 1
	_delay_us(150);	// 100us 초과 기다림
	
	LCD_write_high_nibble(0x30);	// RS : RW : DB7 : DB6 : DB5 : DB4 = 0 : 0 : 0 : 0 : 1 : 1
	_delay_us(150);	// 100us 초과 기다림
	
	LCD_write_high_nibble(0x20);	// RS : RW : DB7 : DB6 : DB5 : DB4 = 0 : 0 : 0 : 0 : 1 : 1
	_delay_ms(5);	// 4.1ms 초과 기다림
	

	LCD_write_command(0x02);
	LCD_write_command(COMMAND_4_BIT_DISPLAY);
	
	
	// display on/off control > 화면 on/커서off/커서 깜빡이 off
	uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);	// 0x0c
	LCD_write_command(command);
	
	LCD_clear();
	
	// entry mode set : 출력 후 커서 이동 > 화면 이동은 없음. (띄워준거 뒤로 그냥 이동)
	LCD_write_command(0x06);
	LCD_write_command(0x0c);
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

void LCD_main(void)
{
	LCD_init();
	
	LCD_write_string("HELLO LCD!");
	
	_delay_ms(1000);
	
	LCD_clear();

	LCD_goto_XY(0, 0);
	LCD_write_data('1');	// 이렇게 해주면 내부에서 알아서 변환해서 띄워주는 것
	LCD_goto_XY(0, 5);
	LCD_write_data('2');
	LCD_goto_XY(1, 0);
	LCD_write_data('3');
	LCD_goto_XY(1, 5);
	LCD_write_data('4');
	
}