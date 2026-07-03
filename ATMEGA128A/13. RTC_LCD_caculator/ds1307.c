/*
 * DS1307.c
 *
 * Created: 2026-06-26 오후 2:42:33
 *  Author: kccistc
 */ 

#include "DS1307.h"
#include "lcd.h"
#include "uart0.h"
#include "i2c_m_loopback.h"

extern void init_uart0(void);
extern void pc_command_processing(t_ds1307* ds1307);
extern volatile int rtc_update_flag;

typedef enum {
	RTC_CLOCK,
	CALCULATOR,
	RTC_CHG_MODE
} program_stat_t;
extern program_stat_t program_stat;

typedef enum {
	NOTHING,
	CHG_YY,
	CHG_MM,
	CHG_DD,
	CHG_HOUR,
	CHG_MIN,
	CHG_SEC
} chg_clock_stat_t ;
extern chg_clock_stat_t chg_clock_stat;

const char* CHG_STATE_STR[] = {
	"CHG_S",    // NOTHING
	"YY",    // CHG_YY
	"MM",    // CHG_MM
	"DD",    // CHG_DD
	"HH",    // CHG_HOUR
	"MIN",   // CHG_MIN
	"SEC"    // CHG_SEC
};

// 이 init을 comport master로 처리하라.
void init_date_time(t_ds1307* ds1307) {
	ds1307->year = 26;
	ds1307->month = 6;
	ds1307->date = 26;
	ds1307->dayofweek = 6; // Fri
	ds1307->hours = 15;
	ds1307->minutes = 20;
	ds1307->seconds = 0;
}

// 1. 입력 bcd
uint8_t bcd2dec(uint8_t data) {
	uint8_t high, low;
	
	low = data & 0x0f;
	high = (data >> 4) * 10;
	
	return (high+low);
}

// dec --> bcd
uint8_t dec2bcd(uint8_t data) {
	uint8_t high, low;
	
	high = (data / 10) << 4; // high nibble에 위치
	low = data % 10;
	
	return (high + low);
}

void write_DS1307(t_ds1307* ds1307)
{
	uint8_t tx_data[7] = {
		dec2bcd(ds1307->seconds) & 0x7F,  // bit7 = CH(clock halt) 반드시 0
		dec2bcd(ds1307->minutes),
		dec2bcd(ds1307->hours) & 0x3F,    // bit6=0 : 24시간 모드 고정
		dec2bcd(ds1307->dayofweek),
		dec2bcd(ds1307->date),
		dec2bcd(ds1307->month),
		dec2bcd(ds1307->year)
	};

	i2c_start();
	i2c_slave_addr_send((SLAVE_ADDR << 1) | 0);   // SLA+W
	i2c_data_write(0x00);                         // 8bit에 전부 채울 거니까
	for (int i = 0; i < 7; i++)
		i2c_data_write(tx_data[i]);
	i2c_stop();
}

void read_DS1307(t_ds1307* ds1307)
{
	i2c_start();
	i2c_slave_addr_send((SLAVE_ADDR << 1) | 0);   // SLA+W (포인터 세팅용)
	i2c_data_write(0x00);                         // 읽을 시작 주소 지정
	i2c_start();                                  // Repeated START
	i2c_slave_addr_send((SLAVE_ADDR << 1) | 1);   // SLA+R

	ds1307->seconds   = bcd2dec(i2c_data_read_acksend()  & 0x7F);	// CH bit(오실레이터 정지 설정)
	ds1307->minutes   = bcd2dec(i2c_data_read_acksend());
	ds1307->hours     = bcd2dec(i2c_data_read_acksend()  & 0x3F);	// 시간에 관련된 것만 얻기 위함
	ds1307->dayofweek = bcd2dec(i2c_data_read_acksend());
	ds1307->date      = bcd2dec(i2c_data_read_acksend());
	ds1307->month     = bcd2dec(i2c_data_read_acksend());
	ds1307->year      = bcd2dec(i2c_data_read_nacksend());

	i2c_stop();
}

void ds1307_init(t_ds1307* ds1307)
{
	init_i2c();
	init_uart0();

	init_date_time(ds1307);
	write_DS1307(ds1307);
}

void ds1307_main(t_ds1307* ds1307)
{
	pc_command_processing(ds1307);

	if (rtc_update_flag) {
		write_DS1307(ds1307);   
		rtc_update_flag = 0;
	}

	read_DS1307(ds1307);        
}

void print_calendar(t_ds1307* ds1307)
{
	char lcd_buf[19];   // 16x2 LCD 기준 한 줄 16자 + null

	LCD_clear();

	LCD_goto_XY(0, 0);
	sprintf(lcd_buf, "20%02d-%02d-%02d D%d",
	ds1307->year, ds1307->month, ds1307->date, ds1307->dayofweek);
	LCD_write_string(lcd_buf);

	LCD_goto_XY(1, 0);
	if (program_stat == RTC_CHG_MODE/* && chg_clock_stat != NOTHING*/) {
		sprintf(lcd_buf, "%02d:%02d:%02d [%s]",
			ds1307->hours, ds1307->minutes, ds1307->seconds,
			CHG_STATE_STR[chg_clock_stat]);
		} else {
		sprintf(lcd_buf, "%02d:%02d:%02d", ds1307->hours, ds1307->minutes, ds1307->seconds);
	}
	LCD_write_string(lcd_buf);
}