#pragma once

#include "Defines.h"
#include "ADC_10B.h"
#include "DigitalPin.h"
#include "DigitalPinPWM.h"
#include "Saturator.h"

class ArduinoIO
{
	// Variables
public:
	ADC_10B ADC_A0 = ADC_10B(0);
	ADC_10B ADC_A1 = ADC_10B(1);
	ADC_10B ADC_A2 = ADC_10B(2);
	ADC_10B ADC_A3 = ADC_10B(3);
	ADC_10B ADC_A4 = ADC_10B(4);
	ADC_10B ADC_A5 = ADC_10B(5);
	DigitalPin P1 = DigitalPin(1);
	DigitalPin P2 = DigitalPin(2);
	DigitalPinPWM P3 = DigitalPinPWM(3);
	DigitalPin P4 = DigitalPin(4);
	DigitalPinPWM P5 = DigitalPinPWM(5);
	DigitalPinPWM P6 = DigitalPinPWM(6);
	DigitalPin P7 = DigitalPin(7);
	DigitalPin P8 = DigitalPin(8);
	DigitalPin P9 = DigitalPin(9);
	DigitalPinPWM P10 = DigitalPinPWM(10);
	DigitalPinPWM P11 = DigitalPinPWM(11);
	DigitalPin P12 = DigitalPin(12);
	DigitalPin P13 = DigitalPin(13);

protected:
private:
	// Funktions
public:
	ArduinoIO();
	~ArduinoIO();
	void MeasureA0();
	void MeasureA1();
	void MeasureA2();
	void MeasureA3();
	void MeasureA4();
	void MeasureA5();
	void MeasureAllAnalog();
	void PrintInstanceState();

protected:
private:
};
