#include "../inc/onewire.h"

/* Init OneWire Struct with GPIO information
 * param:
 *   OneWire: struct to be initialized
 *   GPIOx: Base of the GPIO DQ used, e.g. GPIOA
 *   GPIO_Pin: The pin GPIO DQ used, e.g. 5
 */
void OneWire_Init(OneWire_t* OneWireStruct, GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin)
{
	// TODO
	OneWireStruct->GPIOx = GPIOx;
	OneWireStruct->GPIO_Pin = GPIO_Pin;
}

/* Send reset through OneWireStruct
 * Please implement the reset protocol
 * param:
 *   OneWireStruct: wire to send
 * retval:
 *    0 -> Reset OK
 *    1 -> Reset Failed
 */
uint8_t OneWire_Reset(OneWire_t* OneWireStruct) {
	// TODO
	GPIOB->MODER |= 0x00001000U;//GPIOB, Pin 6 as output
	GPIOB->ODR &= 0xFFFFFFBF;//GPIOB, Pin 6 output "ZERO"
	delay_us(480);
	GPIOB->MODER &= 0xFFFFEFFFU;//GPIOB, Pin 6 as input
	delay_us(80);
	uint8_t result = (GPIOB->IDR >> 6U) & 1U;
	delay_us(410);
	return result;
}

/* Write 1 bit through OneWireStruct
 * Please implement the send 1-bit protocol
 * param:
 *   OneWireStruct: wire to send
 *   bit: bit to send
 */
void OneWire_WriteBit(OneWire_t* OneWireStruct, uint8_t bit) {
	// TODO
	GPIOB->MODER &= 0xFFFFEFFFU;//GPIOB, Pin 6 as input
	if(bit)
	{
		GPIOB->MODER |= 0x00001000U;//GPIOB, Pin 6 as output
		GPIOB->ODR &= 0xFFFFFFBF;//GPIOB, Pin 6 output "ZERO"
		delay_us(1);
		GPIOB->MODER &= 0xFFFFEFFFU;//GPIOB, Pin 6 as input
		delay_us(58);
	}
	else
	{
		GPIOB->MODER |= 0x00001000U;//GPIOB, Pin 6 as output
		GPIOB->ODR &= 0xFFFFFFBF;//GPIOB, Pin 6 output "ZERO"
		delay_us(60);
	}
	GPIOB->MODER &= 0xFFFFEFFFU;//GPIOB, Pin 6 as input
}

/* Read 1 bit through OneWireStruct
 * Please implement the read 1-bit protocol
 * param:
 *   OneWireStruct: wire to read from
 */
uint8_t OneWire_ReadBit(OneWire_t* OneWireStruct) {
	// TODO
	uint8_t flag = 1;
	GPIOB->MODER &= 0xFFFFEFFFU;//GPIOB, Pin 6 as input

	GPIOB->MODER |= 0x00001000U;//GPIOB, Pin 6 as output
	GPIOB->ODR &= 0xFFFFFFBF;//GPIOB, Pin 6 output "ZERO"
	delay_us(2);
	GPIOB->MODER &= 0xFFFFEFFFU;//GPIOB, Pin 6 as input
	flag = (GPIOB->IDR >> 6) & 1U;
	flag = (GPIOB->IDR >> 6) & 1U;
	delay_us(60);
	return flag;
}

/* A convenient API to write 1 byte through OneWireStruct
 * Please use OneWire_WriteBit to implement
 * param:
 *   OneWireStruct: wire to send
 *   byte: byte to send
 */
void OneWire_WriteByte(OneWire_t* OneWireStruct, uint8_t byte)
{
	// TODO
	int i = 0;
	while(i < 8)
	{
		OneWire_WriteBit(OneWireStruct, (byte >> i) & 0x01U);
		delay_us(1);
		i++;
	}
}

/* A convenient API to read 1 byte through OneWireStruct
 * Please use OneWire_ReadBit to implement
 * param:
 *   OneWireStruct: wire to read from
 */
uint8_t OneWire_ReadByte(OneWire_t* OneWireStruct) {
	// TODO
	int i = 0;
	uint8_t temp;
	uint8_t data = 0;
	while(i < 8)
	{
		temp = OneWire_ReadBit(OneWireStruct);
		delay_us(1);
		data = (temp << 7) | (data >> 1);
		i++;
	}
	return data;
}

/* Send ROM Command, Skip ROM, through OneWireStruct
 * You can use OneWire_WriteByte to implement
 */
void OneWire_SkipROM(OneWire_t* OneWireStruct) {
	// TODO
	OneWire_WriteByte(OneWireStruct, 0xCCU);
}
