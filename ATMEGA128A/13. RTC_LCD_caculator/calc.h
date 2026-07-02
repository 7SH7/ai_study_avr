/*
 * calc.h
 *
 * Created: 2026-07-02 오후 2:19:45
 *  Author: kccistc
 */ 
#include <avr/io.h>

void cal_main(uint32_t *cnt, uint32_t timeout, int program_stat);
void calculator_processing(uint8_t key);