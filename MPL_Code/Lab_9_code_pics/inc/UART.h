#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include <string.h>
#include "lcd_function.h"
#include "gpio.h"
#define USART_InUse USART3
extern char buffer[];
unsigned int buffer_size;
typedef enum data_word_length
{
	USART_DATAWORD_8_BITS = 0U,
	USART_DATAWORD_9_BITS = 1U,
	USART_DATAWORD_7_BITS = 2U
} EN_USART_DATAWORD_LENGTH;
typedef enum oversampling_mode_selection
{
	USART_OVERSAMPLING_16 = 0U,
	USART_OVERSAMPLING_8 = 1U
} EN_USART_OVERSAMPLING_MODE_SELECTION;
typedef enum parity_selection
{
	USART_EVEN_PARITY = 0U,
	USART_ODD_PARITY = 1U
} EN_USART_PARITY_SELECTION;
typedef enum parity_control
{
	USART_PARITY_CONTROL_DISABLE = 0U,
	USART_PARITY_CONTROL_ENABLE = 1U
} EN_USART_PARITY_CONTROL;
typedef enum transmit_interrupt_control
{
	USART_TX_INTERRUPT_DISABLE = 0U,
	USART_TX_INTERRUPT_ENABLE = 1U
} EN_USART_TX_INTERRUPT_CONTROL;
typedef enum receive_interrupt_control
{
	USART_RX_INTERRUPT_DISABLE = 0U,
	USART_RX_INTERRUPT_ENABLE = 1U
} EN_USART_RX_INTERRUPT_CONTROL;
typedef enum tx_control
{
	USART_TX_CONTROL_DISABLE = 0U,
	USART_TX_CONTROL_ENABLE = 1U
} EN_USART_TX_CONTROL;
typedef enum rx_control
{
	USART_RX_CONTROL_DISABLE = 0U,
	USART_RX_CONTROL_ENABLE = 1U
} EN_USART_RX_CONTROL;
typedef enum usart_stop_bits_selection
{
	USART_STOP_1_BIT = 0U,
	USART_STOP_0_5_BIT = 1U,
	USART_STOP_2_BIT = 2U,
	USART_STOP_1_5_BIT = 3U
} EN_USART_STOP_BITS_SELECTION;
typedef enum usart_sample_bits_selection
{
	USART_THREE_SAMPLE_BIT = 0U,
	USART_ONE_SAMPLE_BIT = 1U
} EN_USART_SAMPLE_BITS_SELECTION;
typedef enum usart_cts_control
{
	USART_CTS_DISABLE = 0U,
	USART_CTS_ENABLE = 1U
} EN_USART_CTS_CONTROL;
typedef enum usart_rts_control
{
	USART_RTS_DISABLE = 0U,
	USART_RTS_ENABLE = 1U
} EN_USART_RTS_CONTROL;
typedef enum usart_control
{
	USART_DISABLE = 0U,
	USART_ENABLE = 1U
} EN_USART_CONTROL;
/*
----------------------------------------
|	UART GPIO Pin Explanation			|
-----------------------------------------
|	GPIO Module	|	Pin	|	Function	|
|	GPIOA		|	2	|	UART3_RX	|
|	GPIOA		|	3	|	UART3_TX	|
-----------------------------------------
*/
#define UART GPIO GPIOA
#define UART_BOARD_TX 4U
#define UART_BOARD_RX 5U

void USART_Module_Init(void);
void USART_GPIO_Init(void);
void USART_Init(USART_TypeDef* USARTx, EN_USART_DATAWORD_LENGTH USART_DATAWORD_LENGTH, EN_USART_PARITY_SELECTION USART_PARITY_SELECTION, EN_USART_PARITY_CONTROL USART_PARITY_CONTROL, EN_USART_OVERSAMPLING_MODE_SELECTION USART_Oversampling_selection);
void USART_Tx_Interrupt_Control(USART_TypeDef* USARTx, EN_USART_TX_INTERRUPT_CONTROL USART_Tx_interrupt_control);
void USART_Rx_Interrupt_Control(USART_TypeDef* USARTx, EN_USART_RX_INTERRUPT_CONTROL USART_Rx_interrupt_control);
void USART_Tx_Control(USART_TypeDef* USARTx, EN_USART_TX_CONTROL USART_Tx_control);
void USART_Rx_Control(USART_TypeDef* USARTx, EN_USART_RX_CONTROL USART_Rx_control);
void USART_Control(USART_TypeDef* USARTx, EN_USART_CONTROL USART_Control_Option);
void USART_Stop_Bits_Selection(USART_TypeDef* USARTx, EN_USART_STOP_BITS_SELECTION USART_Stop_bits_selection);
void USART_Baud_Rate_Setting(USART_TypeDef* USARTx, uint32_t expected_baud_rate, EN_USART_OVERSAMPLING_MODE_SELECTION USART_Oversampling_selection);
void USART_Sample_Bits_Selection(USART_TypeDef* USARTx, EN_USART_SAMPLE_BITS_SELECTION USART_Sample_bits_selection);
void USART_Hardware_Flow_Control(USART_TypeDef* USARTx, EN_USART_CTS_CONTROL USART_CTS_Control, EN_USART_RTS_CONTROL USART_RTS_Control);
void USART_Asy_Mode_Setting(USART_TypeDef* USARTx);
void USART_Transmit(USART_TypeDef* USARTx, const char* data);
void USART_Receive(USART_TypeDef* USARTx);
void USART3_IRQHandler(void);
#endif
