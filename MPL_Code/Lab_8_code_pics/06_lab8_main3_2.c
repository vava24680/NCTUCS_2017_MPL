char key_value = 0;
void EXIT_Setup()
{
	//TODO: Setup EXTI interrupt
}
void SystemClock_Config()
{
	//TODO: Setup system clock and SysTick timer interrupt
}
void SysTick_Handler(void) {
	//TODO: Scan the keypad column
}
void EXTIx_IRQHandler(void)
{
	//TODO: Read the keypad row value
}

int main()
{
	SystemClock_Config();
	GPIO_init();
	EXTI_Setup();
	while(1){
	display(key_value,2);
}