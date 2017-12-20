#include "../inc/ds18b20.h"

/* Send ConvT through OneWire with resolution
 * param:
 *   OneWire: send through this
 *   resolution: temperature resolution
 * retval:
 *    0 -> OK
 *    1 -> Error
 */
int DS18B20_ConvT(OneWire_t* OneWire, DS18B20_Resolution_t resolution) {
	// TODO
	while(OneWire_Reset(OneWire));
	OneWire_SkipROM(OneWire);
	OneWire_WriteByte(OneWire, 0x44U);//Give it the Write Scratchpad instruction
	switch (resolution) {
		case TM_DS18B20_Resolution_9bits:
			delay_ms(98);
			break;
		case TM_DS18B20_Resolution_10bits:
			delay_ms(195);
			break;
		case TM_DS18B20_Resolution_11bits:
			delay_ms(385);
			break;
		case TM_DS18B20_Resolution_12bits:
			delay_ms(765);
			break;
	}
	while(!DS18B20_Done(OneWire));
	return 0;
}

/* Read temperature from OneWire
 * param:
 *   OneWire: send through this
 *   destination: output temperature
 * retval:
 *    0 -> OK
 *    1 -> Error
 */
uint8_t DS18B20_Read(OneWire_t* OneWire, float* destination)
{
	(*destination) = 0;
	//int base = 64;
	float base = 64;
	int flag;
	uint8_t lsb;
	uint8_t msb;
	uint16_t total;
	while(OneWire_Reset(OneWire));
	OneWire_SkipROM(OneWire);
	OneWire_WriteByte(OneWire, 0xBE);
	lsb = OneWire_ReadByte(OneWire);
	msb = OneWire_ReadByte(OneWire);
	total = (msb << 8) + lsb;
	if((msb >> 7))
	{//Negative
		flag = -1;
		total = ~total + 1;
	}
	else
	{//Positive
		flag = 1;
	}
	OneWire_Reset(OneWire);
	for(int i = 10; i >= 0;i--)
	{
		(*destination) += ((total >> i) & 1U) * base;
		base /= 2.0;
	}
	/*for(int i = 10; i >= 4;i--)
	{
		(*destination) += ((total >> i) & 1U) * base;
		base /= 2;
	}*/
	(*destination) *= flag;
	return 0;
}

/* Set resolution of the DS18B20
 * param:
 *   OneWire: send through this
 *   resolution: set to this resolution
 * retval:
 *    0 -> OK
 *    1 -> Error
 */
uint8_t DS18B20_SetResolution(OneWire_t* OneWire, DS18B20_Resolution_t resolution)
{
	// TODO
	while(OneWire_Reset(OneWire));
	OneWire_SkipROM(OneWire);
	OneWire_WriteByte(OneWire, 0x4E);//Give it the Write Scratchpad instruction
	OneWire_WriteByte(OneWire, 0x32);
	OneWire_WriteByte(OneWire, 0xC4);
	switch (resolution)
	{
		case TM_DS18B20_Resolution_9bits:
			OneWire_WriteByte(OneWire, 0x1F);
			break;
		case TM_DS18B20_Resolution_10bits:
			OneWire_WriteByte(OneWire, 0x3F);
			break;
		case TM_DS18B20_Resolution_11bits:
			OneWire_WriteByte(OneWire, 0x5F);
			break;
		case TM_DS18B20_Resolution_12bits:
			OneWire_WriteByte(OneWire, 0x7F);
			break;
	}
	return 0;
}

/* Check if the temperature conversion is done or not
 * param:
 *   OneWire: send through this
 * retval:
 *    0 -> OK
 *    1 -> Not yet
 */
uint8_t DS18B20_Done(OneWire_t* OneWire)
{
	return OneWire_ReadBit(OneWire);
	return 0;
}
