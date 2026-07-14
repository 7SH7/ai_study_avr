/*
 * i2c_ds1307.c
 *
 * Created: 2026-07-01 오후 4:36:46
 *  Author: kccistc
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart0.h"