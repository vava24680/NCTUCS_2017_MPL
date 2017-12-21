#ifndef LCD_FUNCTION_H_
#define LCD_FUNCTION_H_

#ifndef STDINT_H_
#define STDINT_H_
#include <stdint.h>
#endif

#ifndef GPIO_H_
#include "gpio.h"
#endif
#include "ref.h"

void lcd_gpio_init(void);
void WriteCommand(uint16_t command);
void WriteData(uint16_t data);
uint8_t BusyCheck(void);
void LCD_ClearScreen(void);
void LCD_Show_CursorShow_Blink(uint16_t show, uint16_t cursor_show, uint16_t blink);
#endif
