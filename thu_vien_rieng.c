#include "thu_vien_rieng.h"

/* ================= LCD ================= */
void LCD_Command(unsigned char cmd)
{
	LCD_DATA_PORT = cmd;
	LCD_CTRL_PORT &= ~(1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |=  (1<<LCD_EN);
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	_delay_ms(2);
}

void LCD_Data(unsigned char data)
{
	LCD_DATA_PORT = data;
	LCD_CTRL_PORT |=  (1<<LCD_RS);
	LCD_CTRL_PORT &= ~(1<<LCD_RW);
	LCD_CTRL_PORT |=  (1<<LCD_EN);
	_delay_ms(1);
	LCD_CTRL_PORT &= ~(1<<LCD_EN);
	_delay_ms(2);
}

void LCD_String(char *str)
{
	while(*str)
	LCD_Data(*str++);
}

void LCD_Clear(void)
{
	LCD_Command(0x01);
	_delay_ms(2);
}

void LCD_GotoXY(unsigned char row, unsigned char col)
{
	if (row == 0)
	LCD_Command(0x80 + col);
	else
	LCD_Command(0xC0 + col);
}

void LCD_Init(void)
{
	LCD_DATA_DDR = 0xFF;
	LCD_CTRL_DDR |= (1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN);

	_delay_ms(20);
	LCD_Command(0x38);   // 8-bit, 2 line
	LCD_Command(0x0C);   // Display ON
	LCD_Command(0x06);   // Auto increment
	LCD_Clear();
}

/* ================= UART – HC05 ================= */
void UART_Init(void)
{
	UBRRL = 51; // 9600 baud @ 8MHz
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

char UART_Read(void)
{
	if (UCSRA & (1<<RXC))
	return UDR;
	return 0;
}

void UART_Write(char data)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;
}

/* ================= BUTTON ================= */
uint8_t button_press(uint8_t pin)
{
	if (!(PINB & (1<<pin)))
	{
		_delay_ms(20);
		if (!(PINB & (1<<pin)))
		{
			while (!(PINB & (1<<pin)));
			return 1;
		}
	}
	return 0;
}

/* ================= LED ================= */
void LED_On(void)
{
	PORTD |= (1<<PD2);
}

void LED_Off(void)
{
	PORTD &= ~(1<<PD2);
}
