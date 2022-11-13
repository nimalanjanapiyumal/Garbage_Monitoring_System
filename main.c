/*
 * EP_Final.c
 *
 * Created: 11/6/2022 10:46:35 AM
 * Author : User
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/wdt.h>

#include "LCD_Display.h"
#include "Weigh_sensor.h"
#include "Ultrasonic.h"
#include "Methene_sensor.h"
#include "timersf.h"
#include "hx711.h"


void initPorts(void);
void Turn_Power_Indicator_LED_ON(void);
void Turn_limit_Indicator_LED_ON(void);

double density;
double methene_v;
int counter =0;

//double distance;


int main(void)
{
	double fillin_p;
	//INITIALIZING THE HARDWARE COMPONENTS
    initPorts(); //Initializing Ports
	Lcd_init(); //Initializing LCD Display
	Turn_Power_Indicator_LED_ON(); //Power Indicator ON
	Lcd_CmdWrite(0X80);
	LCD_String_xy(0,0,"Waste Managment");
	
	
    while (1) 
    {
		char fillingbuff[100];
		char fillweight[100];
		//weigh_measure();
		methene_calc();
		ultrasonic();
		//FILLED LEVEL - VIA ULTRASONIC SENSOR
		distance = 18;
		fillin_p = (distance/18.5)*100;
		dtostrf(fillin_p,2,1,fillingbuff);
		Lcd_CmdWrite(0x01);
		LCD_String_xy(0,0,"BIN");
		LCD_String_xy(0,4,fillingbuff);
		LCD_String_xy(0,8,"% Filled");
		
		double wht = hx711_getweight();
		density = hx711_getweight()/distance;
		
		adcinit();
		Lcd_init();
		adcread(0);
		char Res[16], lpg[16], smoke[16];
		
		//Ro = SensorCalibration();
		
		_delay_ms(10);

		//get weight
		Lcd_CmdWrite(0x01);
		LCD_String_xy(0,0,"BIN WEIGH");
		weigh_measure();
		//get methene
		double lpgas = ReadSensor();
		lpgas =25;
		dtostrf(lpgas,2,2,lpg);
		LCD_String_xy(1,0,"Methene %");
		LCD_String_xy(1,10,lpg);
		density = 2;
		fillin_p = 91;
		
		
		
		
		if (fillin_p>90)
		{
			Turn_limit_Indicator_LED_ON();	
		}
		
		if ((lpgas > 20 )&(density >0.9))
		{
			Lcd_CmdWrite(0x01);
			LCD_String_xy(1,0,"Organic Waste");
		}
		//Plastic - weight<10, methene <1
		if ((lpgas < 10 )&(density < 0.9))
		{
			LCD_String_xy(1,0,"Plastic or Polythene");
		}
		
		if ((lpgas < 10 )&(density > 2))
		{
			LCD_String_xy(1,0,"Metal Or Glass");
		}
		
		//Bin Filling Time	
		
    }
}

void initPorts(void)
{
	LcdDataBusDirnReg = 0xFF; //LCD Display Attached Port as output
	DDRC &= 0B10001111; //PORTC pin 5,6 as inputs
	DDRB |= 0B11000000; //POrtB
}

void Turn_Power_Indicator_LED_ON(void)
{
	PORTB |= 0B10000000; //Set portB pin7 to high
}

void Turn_limit_Indicator_LED_ON(void)
{
	PORTB |= 0B01000000; //Set portB pin6 to high
}

ISR(INT0_vect)
{
	counter=counter+1;
}




