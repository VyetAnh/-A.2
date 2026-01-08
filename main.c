#include "thu_vien_rieng.h"

int main(void)
{
	/* DEVICE (LED mô ph?ng) */
	DDRD |= (1<<PD2);

	/* BUTTON */
	DDRB &= ~((1<<PB0)|(1<<PB1));
	PORTB |= (1<<PB0)|(1<<PB1);

	LCD_Init();
	UART_Init();

	LCD_String("VA BLUETOOTH");
	LCD_GotoXY(1,0);
	LCD_String("DEVICE: ");

	char rx;

	while (1)
	{
		/* Bluetooth */
		rx = UART_Read();
		if (rx == '1')
		{
			LED_On();
			LCD_GotoXY(1,0);
			LCD_String("DEVICE: ON ");
		}
		else if (rx == '0')
		{
			LED_Off();
			LCD_GotoXY(1,0);
			LCD_String("DEVICE: OFF");
		}

		/* Button */
		if (button_press(PB0))
		{
			LED_On();
			LCD_GotoXY(1,0);
			LCD_String("DEVICE: ON ");
		}

		if (button_press(PB1))
		{
			LED_Off();
			LCD_GotoXY(1,0);
			LCD_String("DEVICE: OFF");
		}
	}
}
