#ifndef INCLUDE_BUTTON_H_
#define INCLUDE_BUTTON_H_
#include "../inc/button.h"
#endif
void Button_Init(void)
{
	TM_GPIO_Init(GPIOC, 13U, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low);
	return;
}