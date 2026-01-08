#ifndef THU_VIEN_RIENG_H
#define THU_VIEN_RIENG_H

#include <avr/io.h>
#include <util/delay.h>

/* ========= LCD ========= */
#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR  DDRC

#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_DDR  DDRD
#define LCD_RS PD6
#define LCD_RW PD5
#define LCD_EN PD7

void LCD_Init(void);
void LCD_Command(unsigned char cmd);
void LCD_Data(unsigned char data);
void LCD_String(char *str);
void LCD_Clear(void);
void LCD_GotoXY(unsigned char row, unsigned char col);

/* ========= UART – HC05 ========= */
void UART_Init(void);
char UART_Read(void);
void UART_Write(char data);

/* ========= BUTTON ========= */
uint8_t button_press(uint8_t pin);

/* ========= LED ========= */
void LED_On(void);
void LED_Off(void);

#endif
