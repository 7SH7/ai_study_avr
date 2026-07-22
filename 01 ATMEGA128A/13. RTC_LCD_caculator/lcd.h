/*
 * lcd.h
 *
 * Created: 2026-07-01 오전 9:41:52
 *  Author: kccistc
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// 제어용
#define LCD_CONTROL_DDR	 DDRB
#define LCD_CONTROL_PORT PORTB

// 데이터용
#define LCD_DATA_DDR	 DDRC
#define LCD_DATA_PORT    PORTC

#define RS_PIN 5	// PB5 > HIGH면 데이터를 담고있는 register / LOW면 명령어를 담고 있는 register
#define RW_PIN 6	// PB6
#define E_PIN  7	// PB7

#define COMMAND_CLEAR_DISPLAY	0x01
#define COMMAND_8_BIT_DISPLAY	0x38	// 8bit, 2라인 > 5 * 8 >> 이건 command doc 참고
#define COMMAND_4_BIT_DISPLAY	0x28	// 4bit, 2라인 > 5 * 8

#define COMMAND_DISPLAY_ON_OFF_BIT 2
#define COMMAND_CURSOR_ON_OFF_BIT 1
#define COMMAND_BLANK_ON_OFF_BIT 0

extern uint8_t MODE;

void LCD_pulse_enable(void);
void LCD_write_data(uint8_t data);
void LCD_write_command(uint8_t command);
void LCD_clear(void);
void LCD_init(void);
void LCD_write_string(char* str);
void LCD_goto_XY(uint8_t row, uint8_t col);
void LCD_main(void);
void LCD_write_high_nibble(uint8_t data);


#endif /* LCD_H_ */