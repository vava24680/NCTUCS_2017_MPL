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
void LCD_WriteCommand_4bit(uint16_t command);
uint8_t BusyCheck(void);
void LCD_WriteCommand(uint16_t command);
void LCD_WriteData(uint16_t data);
void LCD_ClearScreen(void);
void LCD_Cursor_Reset(void);
void LCD_Enter_Mode(uint16_t Incre_Decre, uint16_t Shift_screen);
void LCD_Panel_Switcher(uint16_t screen_switch, uint16_t cursor_show, uint16_t cursor_blink);
void LCD_Cursor_Shift_Set(uint16_t object, uint16_t direction);
void LCD_Function_Set(uint16_t DL, uint16_t N, uint16_t F);
void LCD_Set_CRGRAM_Address(uint16_t five_bit_address);
void LCD_Set_DDRAM_Address(uint16_t six_bit_address);
void LCD_Function_Set_4bit(uint16_t DL, uint16_t N, uint16_t F);
#endif
