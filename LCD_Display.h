/*
 * LCD_Display.h
 *
 * Created: 10/31/2022 12:46:52 AM
 *  Author: User
 */ 


#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_

/*
 * EP_LCD.c
 *
 * Created: 10/30/2022 6:53:08 PM
 * Author : User
 */ 
#define LcdDataBus PORTA
#define LcdControlBus PORTA

#define LcdDataBusDirnReg DDRA

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

void Lcd_init(void);
void Lcd_CmdWrite(char cmd);
void Lcd_DataWrite(char dat);
void LCD_String(char *str);
void LCD_String_xy (char row, char pos, char *str);



void Lcd_init(void)
{
	Lcd_CmdWrite(0x02); //Initialize Lcd in 4bit mode
	Lcd_CmdWrite(0x28); //Enable 5x7 mode for chars
	Lcd_CmdWrite(0x0E); //Display OFF,Cursor ON
	Lcd_CmdWrite(0x01); //Clear Display
	Lcd_CmdWrite(0x80); //Move the cursor to begining of the first line
	
}


void Lcd_CmdWrite(char cmd)
{
	LcdDataBus =(cmd & 0xF0); //Set Upper 4 bits of the cmd
	LcdControlBus &= ~(1<<LCD_RS); //Set RS pin to LOW
	LcdControlBus &= ~(1<<LCD_RW);// Set RW pin to LOW
	LcdControlBus |= (1<<LCD_EN); //Generate High-to-Low Pulse
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	
	_delay_ms(10);
	
	LcdDataBus = ((cmd<<4) & 0xF0);  //Set Lower 4 bits of the cmd
	LcdControlBus &= ~(1<<LCD_RS); //Sete RS pin to LOW
	LcdControlBus &= ~(1<<LCD_RW);// Set RW pin to LOW
	LcdControlBus |= (1<<LCD_EN); //Generate High-to-Low Pulse
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(10);
	
}

void Lcd_DataWrite(char dat)
{
	LcdDataBus =(dat & 0xF0); //Set Upper 4 bits of the cmd
	LcdControlBus |= (1<<LCD_RS); //Set RS pin to LOW
	LcdControlBus &= ~(1<<LCD_RW);// Set RW pin to LOW
	LcdControlBus |= (1<<LCD_EN); //Generate High-to-Low Pulse
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	
	_delay_ms(10);
	
	LcdDataBus = ((dat<<4) & 0xF0);  //Set Lower 4 bits of the cmd
	LcdControlBus |= (1<<LCD_RS); //Sete RS pin to LOW
	LcdControlBus &= ~(1<<LCD_RW);// Set RW pin to LOW
	LcdControlBus |= (1<<LCD_EN); //Generate High-to-Low Pulse
	_delay_ms(10);
	LcdControlBus &= ~(1<<LCD_EN);
	_delay_ms(10);
}


void LCD_String(char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		Lcd_DataWrite (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	Lcd_CmdWrite((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	Lcd_CmdWrite((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}




#endif /* LCD_DISPLAY_H_ */