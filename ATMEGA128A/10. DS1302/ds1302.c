/*
 * ds1302.c
 *
 * Created: 2026-06-26 오후 2:42:33
 *  Author: kccistc
 */ 

#include "ds1302.h"

void init_date_time(void);
void init_gpio_ds1302(void);
void init_ddr_ds1302(void);
void init_ds1302(void);
uint8_t dec2bcd(uint8_t data);
void tx_ds1302(uint8_t data);
void clock_ds1302(void);
void write_ds1302(uint8_t addr, uint8_t data);

void ds1302_main(void) {
	init_date_time();
	init_ddr_ds1302();
	init_gpio_ds1302(); // all LOW로 설정
	init_ds1302();

	while(1) {
		// 1. read time
		read_time_ds1302();	// ds1302: real time 시계
		// 2. read date
		// 3. printf date & time
		// 4. delay_ms(1000);
	}
}

<<<<<<< HEAD
void rx_ds1302(uint8_t *pdata8bits) {
=======
void read_time_ds1302(void)
{
	ds1302.seconds = read_ds1302(ADDR_SECONDS);
	ds1302.minutes = read_ds1302(ADDR_MINUTES);
	ds1302.hours = read_ds1302(ADDR_HOUR);
}

void read_ds1302(uint8_t addr)
{
	uint8_t data8bits;	// 1bit씩 읽어
	// 1. CE high
	// 2. addr 전송
	// 3. data 읽어들ㅇ미
	// 4. CE low
	// 5. reurn (bcd to dec)
	
	// 1. CE low --> high
	// CE: Chip Enable = RST(RESET) = CS(Chip Select) : 지금부터 너랑 소통하겠다.
	DS1302_RST_PORT |= (1 << DS1302_RST);	// 포트 = 1 >> high니까, 소통하겠음을 표기!
	
	// 2. ADDR 전송
	tx_ds1302(addr + 1);	// data addr 보내고
	
	// 3. DATA 읽어들이기
	rx_ds1302(&data8bits);	// data 받아들이고
	
	// 4. CE high --> low
	DS1302_RST_PORT &= ~(1 << DS1302_RST);	// 다 받아들였으니, 소통 종료 (포트 = 0 > low)
	
	return (bcd2dec(data8bits));	// 읽어들인 data addr 반환
}

void rx_ds1302(uint8_t* pdata8bits);

void rx_ds1302(uint8_t* pdata8bits){
	
>>>>>>> 33768e08ce3e9bdd214ed1c318d4469ef1749562
	uint8_t temp = 0;
	
	// 1. 입력 mode로 설정
<<<<<<< HEAD
	DS1302_DAT_DDR &= ~(1 << DS1302_DAT); // read mode
	
	// LSB로부터 차례로 입력
	for (int i=0; i<8;i++) {
		if (DS1302_DAT_PIN & (1 <<DS1302_DAT)){
			temp |= 1 << i;
		}
		// 3. CLK를 HIGH --> LOW
		if (i != 7) // 마지막 bit를 읽을 때는 clk을 보내주지 않는다.
			clock_ds1302();
=======
	DS1302_DAT_DDR &= ~(1 << DS1302_DAT);	// read mode >> data 송신 > 입력모드. DDR = 0
	// 예) 0x80
	//	MSB			LSB
	//	1000		0000

	// LSB부터 차례로 입력 > 1bit씩 들어옴..
	for(int i = 0 ; i < 8 ; i++)
	{
		// DS1302_DAT_PIN 이 1이다. > 상대가 하는 말 들었는데, HIGH다. > 현재 상태가 1(high)
		// PIN의 역할은 항상 현재 상태가 1(HIGH)인지, 0(LOW)인지 읽어들이는!
		if(DS1302_DAT_PIN & (1 << DS1302_DAT) )	
		{
			temp |= (1 << i);	// 1의 조건만 set
		}
		// 3. CLK를 high -> low	>> 이거는 어딨지..
		// 마지막 bit를 읽을 때는 clk를 보내지 않음.
		if(i != 7)	clock_ds1302();
>>>>>>> 33768e08ce3e9bdd214ed1c318d4469ef1749562
	}
	
	*pdata8bits = temp;
}

<<<<<<< HEAD
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
	
=======

void init_ds1302(void)
{
		write_ds1302(ADDR_SECONDS, ds1302.seconds);
		write_ds1302(ADDR_MINUTES, ds1302.minutes);
		write_ds1302(ADDR_HOUR, ds1302.hours);
		write_ds1302(ADDR_DATE, ds1302.date);
		write_ds1302(ADDR_MONTH, ds1302.month);
		write_ds1302(ADDR_DAYOFWEEK, ds1302.dayofweek);
		write_ds1302(ADDR_YEAR, ds1302.year);
}

void clock_ds1302(void)
{
	// LOW -> HIGH -> LOW	>> LOW 코드 어디갔지?
	DS1302_CLK_PORT &= ~(1 << DS1302_CLK);
	DS1302_CLK_PORT |= (1 << DS1302_CLK);

}


void write_ds1302(uint8_t addr, uint8_t data)
{
	// 1. CE low -> high
	DS1302_RST_PORT	|= (1 << DS1302_RST);
	// 2. ADDR 전송
	tx_ds1302(addr);
>>>>>>> 33768e08ce3e9bdd214ed1c318d4469ef1749562
	// 3. DATA 전송
	tx_ds1302(dec2bcd(data));
	
}

void read_time_ds1302(void) {
	ds1302.seconds = read_ds1302(ADDR_SECONDS);
	ds1302.minutes = read_ds1302(ADDR_MINUTES);
	ds1302.hours = read_ds1302(ADDR_HOUR);
}

void init_ds1302(void) {
	write_ds1302(ADDR_SECONDS, ds1302.seconds);
	write_ds1302(ADDR_MINUTES, ds1302.minutes);
	write_ds1302(ADDR_HOUR, ds1302.hours);
	write_ds1302(ADDR_DATE, ds1302.date);
	write_ds1302(ADDR_MONTH, ds1302.month);
	write_ds1302(ADDR_DAYOFWEEK, ds1302.dayofweek);
	write_ds1302(ADDR_YEAR, ds1302.year);
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
	high = (data & 0xf0) * 10;
	
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

<<<<<<< HEAD
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

void init_date_time(void) {
=======
// 시계니까, 출력모드로 전부 설정
void init_ddr_ds1302(void)
{
	DDRF &= ~( (1 << DS1302_CLK) | (1 << DS1302_DAT) | (1 << DS1302_RST));
	DDRF |=( (1 << DS1302_CLK) | (1 << DS1302_DAT) | (1 << DS1302_RST));	// 출력 mode로 설정
}

// 문서에서 GPIO를 LOW로 하래. > PORT(내부 전압 설정 > 0이면 LOW!)
void init_gpio_ds1302(void)
{
	DS1302_CLK_PORT &= ~( (1 << DS1302_CLK) | (1 << DS1302_DAT) | (1 << DS1302_RST));
}

// 작업 날짜로 초기화
void init_date_time(void)
{
>>>>>>> 33768e08ce3e9bdd214ed1c318d4469ef1749562
	ds1302.year = 26;
	ds1302.month = 06;
	ds1302.date = 26;
	ds1302.dayofweek = 06; // Fri
	ds1302.hours = 15;
	ds1302.minutes = 20;
	ds1302.seconds = 00;
	
}