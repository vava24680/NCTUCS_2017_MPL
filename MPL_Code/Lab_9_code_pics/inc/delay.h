#ifndef DELAY_H_
#define DELAY_H_
#define US_FREQUENCY 1000000
#define MS_FREQUENCY 1000
#include "./stm32l476xx.h"
/*
* Here our system clokc is assumed as 4Mhz
*/
void us_timer_init(void);
void delay_ms(uint32_t value);
void delay_us(uint32_t value);
#endif
