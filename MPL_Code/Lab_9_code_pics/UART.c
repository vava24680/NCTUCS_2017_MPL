#include "../inc/UART.h"
/*
----------------------------------------
|	UART GPIO Pin Explanation			|
-----------------------------------------
|	GPIO Module	|	Pin	|	Function	|
|	GPIOC		|	4	|	UART2_TX	|
|	GPIOC		|	5	|	UART2_RX	|
-----------------------------------------
*/
void USART_Module_Init(void)
{
	RCC->APB1ENR1 = RCC->APB1ENR1 & (~RCC_APB1ENR1_USART3EN_Msk);
	RCC->APB1ENR1 = RCC->APB1ENR1 | RCC_APB1ENR1_USART3EN;
}
void USART_GPIO_Init(void)
{
	/*TX Part*/
	TM_GPIO_Init(GPIOC, UART_BOARD_TX, TM_GPIO_Mode_AF, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Medium);
	/*TX AF Function Selection, AF7*/
	GPIOC->AFR[0] = GPIOC->AFR[0] & (~GPIO_AFRL_AFSEL4_Msk);
	GPIOC->AFR[0] = GPIOC->AFR[0] | GPIO_AFRL_AFSEL4_0 | GPIO_AFRL_AFSEL4_1 | GPIO_AFRL_AFSEL4_2;

	/*RX part*/
	TM_GPIO_Init(GPIOC, UART_BOARD_RX, TM_GPIO_Mode_AF, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Medium);
	GPIOC->AFR[0] = GPIOC->AFR[0] & (~GPIO_AFRL_AFSEL5_Msk);
	GPIOC->AFR[0] = GPIOC->AFR[0] | GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL5_1 | GPIO_AFRL_AFSEL5_2;
}
void USART_Init(USART_TypeDef* USARTx, EN_USART_DATAWORD_LENGTH USART_Dataword_length, EN_USART_PARITY_SELECTION USART_PARITY_SELECTION, EN_USART_PARITY_CONTROL USART_Parity_control, EN_USART_OVERSAMPLING_MODE_SELECTION USART_Oversampling_selection)
{
	USARTx->CR1 = USARTx->CR1 & (~USART_CR1_M0_Msk) & (~USART_CR1_M1_Msk) & (~USART_CR1_PS_Msk) & (~USART_CR1_PCE_Msk);
	USARTx->CR1 = USARTx->CR1 | ((USART_Dataword_length & 1U) << USART_CR1_M0_Pos) | (((USART_Dataword_length >> 1U) & 1U) << USART_CR1_M1_Pos);
	USARTx->CR1 = USARTx->CR1 | (USART_Parity_control << USART_CR1_PCE_Pos);
	if(USART_Parity_control == USART_PARITY_CONTROL_ENABLE)
		USARTx->CR1 = USARTx->CR1 | (USART_PARITY_SELECTION << USART_CR1_PS_Pos);
	USARTx->CR1 = USARTx->CR1 & (~USART_CR1_OVER8_Msk);
	USARTx->CR1 = USARTx->CR1 | (USART_Oversampling_selection << USART_CR1_OVER8_Pos);
	USART_Control(USARTx, USART_ENABLE);
	USART_Rx_Control(USARTx, USART_RX_CONTROL_ENABLE);
}
void USART_Tx_Interrupt_Control(USART_TypeDef* USARTx, EN_USART_TX_INTERRUPT_CONTROL USART_Tx_interrupt_control)
{
	USARTx->CR1 &= (~USART_CR1_TCIE_Msk);
	USARTx->CR1 |= (USART_Tx_interrupt_control << USART_CR1_TCIE_Pos);
}
void USART_Rx_Interrupt_Control(USART_TypeDef* USARTx, EN_USART_RX_INTERRUPT_CONTROL USART_Rx_interrupt_control)
{
	USARTx->CR1 &= (~USART_CR1_RXNEIE_Msk);
	USARTx->CR1 |= (USART_Rx_interrupt_control << USART_CR1_RXNEIE_Pos);
}
void USART_Tx_Control(USART_TypeDef* USARTx, EN_USART_TX_CONTROL USART_Tx_control)
{
	USARTx->CR1 &= (~USART_CR1_TE_Msk);
	USARTx->CR1 |= (USART_Tx_control << USART_CR1_TE_Pos);
}
void USART_Rx_Control(USART_TypeDef* USARTx, EN_USART_RX_CONTROL USART_Rx_control)
{
	USARTx->CR1 = USARTx->CR1 & (~USART_CR1_RE_Msk);
	USARTx->CR1 = USARTx->CR1 | (USART_Rx_control << USART_CR1_RE_Pos);
}
void USART_Control(USART_TypeDef* USARTx, EN_USART_CONTROL USART_Control_Option)
{
	USARTx->CR1 = USARTx->CR1 & (~USART_CR1_UE_Msk);
	USARTx->CR1 = USARTx->CR1 | (USART_Control_Option << USART_CR1_UE_Pos );
}
void USART_Stop_Bits_Selection(USART_TypeDef* USARTx, EN_USART_STOP_BITS_SELECTION USART_Stop_bits_selection)
{
	USARTx->CR2 = USARTx->CR2 & (~USART_CR2_STOP_Msk);
	USARTx->CR2 = USARTx->CR2 | (USART_Stop_bits_selection << USART_CR2_STOP_Pos);
}
void USART_Baud_Rate_Setting(USART_TypeDef* USARTx, uint32_t expected_baud_rate, EN_USART_OVERSAMPLING_MODE_SELECTION USART_Oversampling_selection)
{
	if(USART_Oversampling_selection == USART_OVERSAMPLING_16)
	{
		USARTx->BRR = USARTx->BRR & (~0xFFFFU);
		USARTx->BRR = (USARTx->BRR | (4000000U/expected_baud_rate)) & 0xFFFFU;
	}
	else
	{
		uint32_t USARTDIV = 2 * 4000000U / expected_baud_rate;
		USARTx->BRR = USARTx->BRR & (~0xFFFFU);
		USARTx->BRR = USARTx->BRR | (USARTDIV & 0xFFF0U);
		USARTDIV &= 0xFU;
		USARTx->BRR = USARTx->BRR | (USARTDIV >> 1U);
	}
}
void USART_Sample_Bits_Selection(USART_TypeDef* USARTx, EN_USART_SAMPLE_BITS_SELECTION USART_Sample_bits_selection)
{
	USARTx->CR3 = USARTx->CR3 & (~USART_CR3_ONEBIT_Msk);
	USARTx->CR3 = USARTx->CR3 | (USART_Sample_bits_selection << USART_CR3_ONEBIT_Pos);
}
void USART_Hardware_Flow_Control(USART_TypeDef* USARTx, EN_USART_CTS_CONTROL USART_CTS_Control, EN_USART_RTS_CONTROL USART_RTS_Control)
{
	USARTx->CR3 = USARTx->CR3 & (~USART_CR3_CTSE_Msk);
	USARTx->CR3 = USARTx->CR3 & (~USART_CR3_RTSE_Msk);
	USARTx->CR3 = USARTx->CR3 | (USART_CTS_Control << USART_CR3_CTSE_Pos);
	USARTx->CR3 = USARTx->CR3 | (USART_RTS_Control << USART_CR3_RTSE_Pos);
}
void USART_Asy_Mode_Setting(USART_TypeDef* USARTx)
{//From ppt, may not be generally used
	USARTx->CR2 = USARTx->CR2 & (~USART_CR2_LINEN_Msk) & (~USART_CR2_CLKEN_Msk);
	USARTx->CR3 = USARTx->CR3 & (~USART_CR3_SCEN_Msk) & (~USART_CR3_HDSEL_Msk) & (~USART_CR3_IREN_Msk);
}
void USART_Transmit(USART_TypeDef* USARTx, const char* data)
{
	int length = strlen(data);
	/*USART_BAUD_RATE_SETTING(USARTx, 9600U, USART_OVERSAMPLING_16);
	USART_STOP_BITS_SELECTION(USARTx, USART_STOP_1_BIT);*/
	//USART_Control should not be here
	USART_Tx_Control(USARTx, USART_TX_CONTROL_ENABLE);
	for(uint32_t i = 0; i < length; i++)
	{
		while( !( (USARTx->ISR >> USART_ISR_TXE_Pos) & 1U) );
		USARTx->TDR = (*data & 0xFFU);
		data++;
	}
	while( !( (USARTx->ISR >> USART_ISR_TC_Pos) & 1U) ) ;
	USART_Tx_Control(USARTx, USART_TX_CONTROL_DISABLE);
}
