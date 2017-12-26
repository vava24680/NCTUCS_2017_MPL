#ifndef DELAY_H_
#define DELAY_H_
#define US_FREQUENCY 1000000
#define MS_FREQUENCY 1000
#ifndef INCLUDE_STM32L476XX_H_
#define INCLUDE_STM32L476XX_H_
#include "./stm32l476xx.h"
#endif
/*
* Here our system clokc is assumed as 4Mhz
*/
void us_timer_init(void);
void delay_ms(uint32_t value);
void delay_us(uint32_t value);
#endif
