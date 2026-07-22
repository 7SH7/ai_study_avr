/*
 * i2c_m_loopback.h
 *
 * Created: 2026-07-01 오후 6:37:41
 *  Author: kccistc
 */ 


#ifndef I2C_M_LOOPBACK_H_
#define I2C_M_LOOPBACK_H_


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>    // sei 등 함수
#include <stdio.h>
#include <string.h>

// I2C 설정
#define SLAVE_ADDR 0x68    // 7bit salve 주소
#define I2C_FREQUENCY   100000UL   // 100KHz
// TWBR : I2C 통신 bit bate 설정
// TWBR = (F_CPU /  I2C_FREQUENCY - 16) / 2 (분주비=1)
#define TWBR_VALUE  ( (F_CPU /  I2C_FREQUENCY - 16) / 2)  // TWBR(TWI Bit Rate Register)

//--------- TWI 상태 코드 -------------
// TWSR(TWI Status Register) : 7번~3번 bit(5bit를 참조) : I2c통신의 전송 상태나 오류를 나타 낸다
#define TWSR_START  0x08  // START 조건 전송 완료
#define TWSR_REP_START 0x10   // TWSR_REP_START (0x10) - Repeated START
#define TWSR_MT_SLA_ACK  0x18  // MASTER가 SLAVE ADDR + W 전송후 ACK 수신
#define TWSR_MT_DATA_ACK  0x28  // MASTER가 SLAVE DATA 전송후 ACK 수신
#define TWSR_MR_SLA_ACK  0x40   // MASTER가 SLAVE ADDR + R 전송후 ACK 수신
#define TWSR_MR_DATA_ACK  0x50   // MASTER가 DATA 수신뒤 + ACK 전송
#define TWSR_MR_DATA_NACK  0x58   // MASTER가 DATA 수신뒤 + NACK 전송  (마지막)

int i2c_main(void);
void init_i2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_slave_addr_send(uint8_t addr_rw);
void i2c_data_write(uint8_t data);
uint8_t i2c_data_read_acksend(void);
uint8_t i2c_data_read_nacksend(void);

#endif /* I2C_M_LOOPBACK_H_ */