/*
 * ds1302.c
 *
 * Created: 2026-06-26 오후 2:42:33
 *  Author: kccistc
 */ 

#include "ds1302.h"
#include "uart0.h"

void init_date_time(t_ds1302* ds1302);
void init_gpio_ds1302(void);
void init_ddr_ds1302(void);
void init_ds1302(t_ds1302* ds1302);
uint8_t dec2bcd(uint8_t data);
void tx_ds1302(uint8_t data);
void clock_ds1302(void);
void write_ds1302(uint8_t addr, uint8_t data);
void read_time_ds1302(t_ds1302* ds1302);
uint8_t read_ds1302(uint8_t addr);
uint8_t bcd2dec(uint8_t data);
void read_date_ds1302(t_ds1302* ds1302);
void parse_ds1302_from_uart(t_ds1302* ds1302, char* str);

extern void pc_command_processing(void);

void ds1302_main(void) {

	// 쓰레기값이 있으니까, 초기화하는 걸로 작업 시작
	t_ds1302 data;
	t_ds1302 *ds1302 = &data;
	
	// 각 parameter에는 주소값이 전달되어야 고쳐지지
	init_date_time(ds1302);
	init_ddr_ds1302();
	init_gpio_ds1302(); // all LOW로 설정
//	init_ds1302(ds1302);

	while(1) {
		//if (front != rear)
		//{
			//parse_ds1302_from_uart(ds1302, rx_buff[front]);
			//init_ds1302(ds1302);
			//front = (front + 1) % QUEUE_SIZE;
		//}
	
		//pc_command_processing();
		parse_ds1302_from_uart(ds1302, rx_buff);

		// 1. read time
		read_time_ds1302(ds1302);
		// 2. read date
		read_date_ds1302(ds1302);
		// 3. printf date & time
		printf("DATE: %d-%d-%d\n", ds1302->year, ds1302->month, ds1302->date);
		printf("TIME: %d-%d-%d\n", ds1302->hours, ds1302->minutes, ds1302->seconds);
		// 4. delay_ms(1000);
		_delay_ms(1000);
	}
}

void read_date_ds1302(t_ds1302* ds1302)
{
	ds1302->date = read_ds1302(ADDR_DATE);
	ds1302->month = read_ds1302(ADDR_MONTH);
	ds1302->dayofweek = read_ds1302(ADDR_DAYOFWEEK);
	ds1302->year = read_ds1302(ADDR_YEAR);
}

void rx_ds1302(uint8_t *pdata8bits) {
	uint8_t temp = 0;
	
	// 1. 입력 mode로 설정
	DS1302_DAT_DDR &= ~(1 << DS1302_DAT); // read mode
	
	// LSB로부터 차례로 입력
	for (int i=0; i<8;i++) {
		if (DS1302_DAT_PIN & (1 << DS1302_DAT)){
			temp |= 1 << i;
		}
		// 3. CLK를 HIGH --> LOW
		if (i != 7) // 마지막 bit를 읽을 때는 clk을 보내주지 않는다.
			clock_ds1302();
	}
	
	*pdata8bits = temp;
}

uint8_t read_ds1302(uint8_t addr) {
	uint8_t data8bits = 0; // 1bit씩 읽어서 담을 변수
	
	// 1. CE high
	DS1302_RST_PORT |= 1 << DS1302_RST;
	// 2. addr 전송
	tx_ds1302(addr+1); // read addr
	// 3. data를 읽어들임.
	rx_ds1302(&data8bits);
	// 4. CE HIGH --> LOW
	DS1302_RST_PORT &= ~(1 << DS1302_RST);
	// 5. return (bcd to dec)
    return bcd2dec(data8bits);	
}

void read_time_ds1302(t_ds1302* ds1302) {
	ds1302->seconds = read_ds1302(ADDR_SECONDS);
	ds1302->minutes = read_ds1302(ADDR_MINUTES);
	ds1302->hours = read_ds1302(ADDR_HOUR);
}

void init_ds1302(t_ds1302* ds1302) {
	write_ds1302(ADDR_SECONDS, ds1302->seconds);
	write_ds1302(ADDR_MINUTES, ds1302->minutes);
	write_ds1302(ADDR_HOUR, ds1302->hours);
	write_ds1302(ADDR_DATE, ds1302->date);
	write_ds1302(ADDR_MONTH, ds1302->month);
	write_ds1302(ADDR_DAYOFWEEK, ds1302->dayofweek);
	write_ds1302(ADDR_YEAR, ds1302->year);
}

// dec --> bcd
// 예) 25
// dec 00011001
// bcd 00100101
uint8_t dec2bcd(uint8_t data) {
	uint8_t high, low;
	
	high = (data / 10) << 4; // high nibble에 위치
	low = data % 10;
	
	return (high + low);
}

// 1. 입력 bcd
// 예) 26년의 bcd
// 7654 3210
// 0010 0110
// * 10
// 26
uint8_t bcd2dec(uint8_t data) {
	uint8_t high, low;
	
	low = data & 0x0f;
	high = (data >> 4) * 10;	
	
	return (high+low);
}

void write_ds1302(uint8_t addr, uint8_t data) {
	// 1. CE low --> HIGH
	DS1302_RST_PORT |= 1 << DS1302_RST;
	// 2. ADDR 전송
	tx_ds1302(addr);
	// 3. DATA 전송
	tx_ds1302(dec2bcd(data));
	// 4. CE HIGH --> LOW
	DS1302_RST_PORT &= ~(1 << DS1302_RST);
}

void init_ddr_ds1302(void) {
	DDRF &= ~(1 << DS1302_CLK | 1 << DS1302_DAT | 1 << DS1302_RST);
	DDRF |= 1 << DS1302_CLK | 1 << DS1302_DAT | 1 << DS1302_RST; // 출력 mode로 설정
}

void tx_ds1302(uint8_t data) {
	// 1. 출력 mode로 설정
	DS1302_DAT_DDR |= 1 << DS1302_DAT; // write mode
	// 예) 0x80
	// M		L
	// 1000 0000
	for (int i=0;i<8;i++) {
		if (data & (1 << i))
			DS1302_DAT_PORT |= 1 << DS1302_DAT;
		else DS1302_DAT_PORT &= ~(1 << DS1302_DAT);
		
		clock_ds1302();
	}
}

void clock_ds1302(void) {
	// LOW --> HIGH --> LOW
	DS1302_CLK_PORT &= ~(1 << DS1302_CLK);
	DS1302_CLK_PORT |= 1 << DS1302_CLK;
	DS1302_CLK_PORT &= ~(1 << DS1302_CLK);
}

void init_gpio_ds1302(void){
	DS1302_CLK_PORT &= ~(1 << DS1302_CLK | 1 << DS1302_DAT | 1 << DS1302_RST);
	_delay_ms(2);
}

// 이 init을 comport master로 처리하라.
void init_date_time(t_ds1302* ds1302) {
	ds1302->year = 26;
	ds1302->month = 06;
	ds1302->date = 26;
	ds1302->dayofweek = 06; // Fri
	ds1302->hours = 15;
	ds1302->minutes = 20;
	ds1302->seconds = 00;
}

void parse_ds1302_from_uart(t_ds1302* ds1302, char* rx_buff)
{	
	// %2hhu: 2글자로 hhu = unsigned char (uint8_t)
	sscanf(rx_buff, "setrtc%2hhu%2hhu%2hhu%2hhu%2hhu%2hhu",
	&ds1302->year,
	&ds1302->month,
	&ds1302->date,
	&ds1302->hours,
	&ds1302->minutes,
	&ds1302->seconds);
}

