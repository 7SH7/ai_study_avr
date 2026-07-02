/*
 * DS1307.h
 *
 * Created: 2026-06-26 오후 2:42:04
 *  Author: kccistc
 */ 
#ifndef DS1307_H_
#define DS1307_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

// DS1307 레지스터는 flat 주소 0x00 ~ 0x06 (I2C 방식, DS1302와 다름)
// write_DS1307/read_DS1307에서 0x00부터 순차 write/read 하므로
// 개별 ADDR_* 매크로는 사용하지 않음

typedef struct _ds1307
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t date;
	uint8_t month;
	uint8_t dayofweek;	// 1: sun ...
	uint8_t year;
	uint8_t ampm;		// 1: pm, 0: am
	uint8_t hourmode;	// 0: 24, 1: 12
} t_ds1307;

void ds1307_init(t_ds1307* ds1307);
void ds1307_main(t_ds1307* ds1307);
void init_date_time(t_ds1307* ds1307);
void write_DS1307(t_ds1307* ds1307);
void read_DS1307(t_ds1307* ds1307);
uint8_t dec2bcd(uint8_t data);
uint8_t bcd2dec(uint8_t data);
void print_calendar(t_ds1307* ds1307);

#endif /* DS1307_H_ */