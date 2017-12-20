#include "../inc/ds18b20.h"
//#include "../inc/stm32l476xx.h"
#include "../inc/system_stm32l4xx.h"
extern void MAX7219Send(unsigned char address, unsigned char data);
extern int user_press_button(void);
extern void FPU_ENABLE(void);
OneWire_t OneWire_instance;
void Essential_GPIO_init()
{
	/**/
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOBEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR & (~RCC_AHB2ENR_GPIOCEN_Msk);
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR = RCC->AHB2ENR | RCC_AHB2ENR_GPIOCEN;
	/**/
}
void seven_segment_blank(int num_digts)
{
	for(unsigned int i=0 ; i<num_digts; i++)
	{
		MAX7219Send(i+1,0x0FU);
	}
}
void GPIO_init()
{
	TM_GPIO_Init(GPIOB, 3U, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, 4U, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, 5U, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, 6U, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOC, 13U, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low);
	MAX7219Send(0x0CU,0x01U);//Shutdown register, 1=>Normal operation
	MAX7219Send(0x0FU,0x00U);//Display Test, 1=>Normal Operation
	MAX7219Send(0x09U,0xFFU);//Decode Mode, FF=>All bits use CodeB Format
	MAX7219Send(0x0BU,0x07U);//Scan-Limit Register, 1=>For bit0 and bit1
	MAX7219Send(0x0AU,0x05U);//Intensity Register
	seven_segment_blank(8);
	MAX7219Send(1, 8);//MAX7219 test
}
void SystemClock_Config()
{
	//TODO: Setup system clock and SysTick timer interrupt
	RCC->APB2ENR = RCC->APB2ENR & 0xFFFFFFFE;
	RCC->APB2ENR = RCC->APB2ENR | 0x00000001U;
	/*SysTick config*/
	SysTick->CTRL = SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk);
	SysTick->CTRL = SysTick->CTRL & (~SysTick_CTRL_TICKINT_Msk);
	SysTick->CTRL = SysTick->CTRL & (~SysTick_CTRL_CLKSOURCE_Msk);
	SysTick->CTRL = SysTick->CTRL | (0x01U << SysTick_CTRL_ENABLE_Pos);		//Enable SysTick timer
	SysTick->CTRL = SysTick->CTRL | (0x01U << SysTick_CTRL_TICKINT_Pos);		//Count to 0, assert SysTick exception request
	SysTick->CTRL = SysTick->CTRL | (0x00U << SysTick_CTRL_CLKSOURCE_Msk);	//Choose processor clock as clock source
	SysTick->LOAD = SysTick->LOAD & (~SysTick_VAL_CURRENT_Msk);
	SysTick->LOAD = SysTick->LOAD | (999999U << SysTick_VAL_CURRENT_Pos);
	SysTick->VAL = SysTick->VAL & (~SysTick_LOAD_RELOAD_Msk);
}
void SysTick_Handler(void)
{
	//TODO: Show temperature on 7-seg display
	unsigned int address = 1;
	float temperature_float;
	int temperature;
	DS18B20_ConvT(&OneWire_instance, TM_DS18B20_Resolution_10bits);
	DS18B20_Read(&OneWire_instance, &temperature_float);
	seven_segment_blank(8);
	temperature_float*=100;
	temperature = (int)temperature_float;
	do
	{
		if(address == 3)
			MAX7219Send(address, temperature%10 + 0x80);
		else
			MAX7219Send(address, temperature%10);
		address++;
		temperature /= 10;
	}
	while(temperature);
}
int main()
{
	int SysTick_state = 1;
	SystemClock_Config();
	Essential_GPIO_init();
	GPIO_init();
	FPU_ENABLE();
	OneWire_Init(&OneWire_instance, GPIOB, 6);
	DS18B20_SetResolution(&OneWire_instance, TM_DS18B20_Resolution_10bits);
	while(1)
	{
		if(user_press_button())
		{
			//TODO: Enable or disable Systick timer
			if(SysTick_state)
			{
				SysTick->CTRL = SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk);
				SysTick_state = 0;
			}
			else
			{
				SysTick->CTRL = SysTick->CTRL | SysTick_CTRL_ENABLE_Msk;
			}
		}
	}
}
