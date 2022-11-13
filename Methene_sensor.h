/*
 * Methene_sensor.h
 *
 * Created: 11/7/2022 9:17:10 PM
 *  Author: User
 */ 


#ifndef METHENE_SENSOR_H_
#define METHENE_SENSOR_H_


#include <avr/io.h>
#define F_CPU 16000000UL

#include <util/delay.h>
#include <stdlib.h>
#include "LCD_Display.h"
#include "adc.h"
#include "mq9.h"

float Ro=10;                 //Ro is initialized to 10 kilo ohms

void methene_calc()
{
	adcinit();
	Lcd_init();
	adcread(0);
	char Res[16], lpg[16], smoke[16];
	
	//Ro = SensorCalibration();
	
	_delay_ms(10);

	//get weight
	double lpgas = ReadSensor();
	dtostrf(lpgas, 3, 3, lpg);
	//Lcd_CmdWrite(0x01);
	//Lcd_CmdWrite(0xC0);
	//LCD_String(lpg);
	_delay_ms(500);
	
	//itoa(GetGasPercentage(ReadSensor()/Ro,LPG), lpg, 10);
	//dtostrf(GetGasPercentage(ReadSensor()/Ro,LPG),3,3,lpg);
	//Lcd_CmdWrite(0x01);
	//LCD_String_xy(0,8,"lpg");
}

#endif /* METHENE_SENSOR_H_ */