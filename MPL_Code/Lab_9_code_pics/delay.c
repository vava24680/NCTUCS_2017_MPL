#include "../inc/delay.h"
/*
* Here our system clokc is assumed as 4Mhz
*/
void us_timer_init(void)
{
	RCC->APB1ENR1 = RCC->APB1ENR1 & (~RCC_APB1ENR1_TIM2EN_Msk);
	RCC->APB1ENR1 = RCC->APB1ENR1 | RCC_APB1ENR1_TIM2EN;
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_DIR_Msk);/*Counting Down*/
	TIM2->PSC = TIM2->PSC & (~TIM_PSC_PSC_Msk);
	TIM2->PSC = TIM2->PSC | (4000000/US_FREQUENCY - 1);
	TIM2->ARR = TIM2->ARR & (~TIM_ARR_ARR_Msk);
	TIM2->ARR = TIM2->ARR | (US_FREQUENCY - 1);
	TIM2->EGR = TIM2->EGR & (~TIM_EGR_UG_Msk);
	TIM2->EGR = TIM2->EGR | (1U << TIM_EGR_UG_Pos);
	TIM2->CNT = TIM2->CNT & (~TIM_CNT_CNT_Msk);
}
void delay_ms(uint32_t value)
{
	delay_us(value * 1000);
	return;
}

void delay_us(uint32_t value)
{
	us_timer_init();
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_CEN_Msk);
	TIM2->CR1 = TIM2->CR1 | TIM_CR1_CEN;
	while(TIM2->CNT < value);
	TIM2->CR1 = TIM2->CR1 & (~TIM_CR1_CEN_Msk);
	return;
}