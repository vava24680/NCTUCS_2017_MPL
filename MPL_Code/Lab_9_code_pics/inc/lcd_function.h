#ifndef LCD_FUNCTION_H_
#define LCD_FUNCTION_H_

#ifndef STDINT_H_
#define STDINT_H_
#include <stdint.h>
#endif

#ifndef GPIO_H_
#include "gpio.h"
#endif
#include "delay.h"
#define LCD_GPIO GPIOB
#define LCD_RS_PIN 3
#define LCD_RW_PIN 4
#define LCD_ENABLE_PIN 5
#define LCD_DATA0 8
#define LCD_DATA1 9
#define LCD_DATA2 10
#define LCD_DATA3 11
#define LCD_DATA4 12
#define LCD_DATA5 13
#define LCD_DATA6 14
#define LCD_DATA7 15
#define LCD_OutPut_DR(GPIOx, DATA) ((GPIOx)->ODR = (((GPIOx)->ODR & 0xFFFF00FFU) | DATA))
void lcd_gpio_init(void);
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
void LCD_Serial_Output(const char* data);
#endif
