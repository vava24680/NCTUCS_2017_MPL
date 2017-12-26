/**
 * @author  Tilen Majerle
 * @email   tilen@majerle.eu
 * @website http://stm32f4-discovery.com
 * @link    http://stm32f4-discovery.com/2015/07/hal-library-1-5-gpio-library-for-stm32fxxx/
 * @version v1.0
 * @ide     Keil uVision
 * @license MIT
 * @brief   GPIO Library for STM32F4xx and STM32F7xx devices
 *
\verbatim
   ----------------------------------------------------------------------
    Copyright (c) 2016 Tilen Majerle

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge,
    publish, distribute, sublicense, and/or sell copies of the Software,
    and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
    AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
   ----------------------------------------------------------------------
\endverbatim
 */

#ifndef GPIO_H_
#define GPIO_H_
#ifndef INCLUDE_STM32L476XX_H_
#define INCLUDE_STM32L476XX_H_
#include "./stm32l476xx.h"
#endif
#ifndef INCLUDE_SYSTEM_STM32L4XX_H_
#define INCLUDE_SYSTEM_STM32L4XX_H_
#include "./system_stm32l4xx.h"
#endif

#define TM_GPIO_SetPinLow(GPIOx, GPIO_Pin)			((GPIOx)->BRR = (1<<(uint32_t)(GPIO_Pin)))
#define TM_GPIO_SetPinHigh(GPIOx, GPIO_Pin)			((GPIOx)->BSRR = (1<<(uint32_t)(GPIO_Pin)))
#define TM_GPIO_GetInputPinValue(GPIOx, GPIO_Pin)	(((GPIOx)->IDR & (1<<(uint32_t)(GPIO_Pin))) == 0 ? 0 : 1)
#define TM_GPIO_SetPinLow_ODR(GPIOx, GPIO_Pin) ((GPIOx)->ODR = ((GPIOx)->ODR) & (~(1<<(uint32_t)(GPIO_Pin))))
#define TM_GPIO_SetPinHigh_ODR(GPIOx, GPIO_Pin) ((GPIOx)->ODR = ((GPIOx)->ODR) | (1<<(uint32_t)(GPIO_Pin)))
#define TM_GPIO_SetSerialOutput(GPIOx, DATA) ((GPIOx)->ODR = ((GPIOx)->ODR & (0xFFFF00FFU)) | )
/*********************GPIO Define*********************/


/*********************GPIO Enum*********************/

typedef enum {
	TM_GPIO_Mode_IN = 0x00,  /*!< GPIO Pin as General Purpose Input */
	TM_GPIO_Mode_OUT = 0x01, /*!< GPIO Pin as General Purpose Output */
	TM_GPIO_Mode_AF = 0x02,  /*!< GPIO Pin as Alternate Function */
	TM_GPIO_Mode_AN = 0x03,  /*!< GPIO Pin as Analog input/output */
} TM_GPIO_Mode_t;

typedef enum {
	TM_GPIO_OType_PP = 0x00, /*!< GPIO Output Type Push-Pull */
	TM_GPIO_OType_OD = 0x01  /*!< GPIO Output Type Open-Drain */
} TM_GPIO_OType_t;

typedef enum {
	TM_GPIO_Speed_Low = 0x00,    /*!< GPIO Speed Low */
	TM_GPIO_Speed_Medium = 0x01, /*!< GPIO Speed Medium */
	TM_GPIO_Speed_Fast = 0x02,   /*!< GPIO Speed Fast, not available on STM32F0xx devices */
	TM_GPIO_Speed_High = 0x03    /*!< GPIO Speed High */
} TM_GPIO_Speed_t;

typedef enum {
	TM_GPIO_PuPd_NOPULL = 0x00, /*!< No pull resistor */
	TM_GPIO_PuPd_UP = 0x01,     /*!< Pull up resistor enabled */
	TM_GPIO_PuPd_DOWN = 0x02    /*!< Pull down resistor enabled */
} TM_GPIO_PuPd_t;

void TM_GPIO_SetPullResistor(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, TM_GPIO_PuPd_t GPIO_PuPd);
void TM_GPIO_SetPinAsInput(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void TM_GPIO_SetPinAsOutput(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);
void TM_GPIO_Init(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, TM_GPIO_Mode_t GPIO_Mode, TM_GPIO_OType_t GPIO_OType, TM_GPIO_PuPd_t GPIO_PuPd, TM_GPIO_Speed_t GPIO_Speed);


#endif /* GPIO_H_ */
