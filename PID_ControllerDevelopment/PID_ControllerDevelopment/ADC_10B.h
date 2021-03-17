#pragma once

#include "Defines.h"
#include <stdint.h>

class ADC_10B
{
	// Variables
public:
	const float Max_mV = 5000.0f;  // 5V
	const float Max_Bit = 1023.0f; // 10 Bit Resolution
protected:
	uint8_t PinNr;
	int16_t AnalogSignal_Bit; // Digital Value from ADC
	float AnalogSignal_mVolt; // [0V..5V]

private:
	// Funktions
public:
	ADC_10B(const uint8_t pinNr);
	~ADC_10B();
	void UpdateSignal(const int16_t signal_Bit); // Digital Value [0..1023]
	int16_t Get_Bit() const;
	float Get_mVolt() const;
	void PrintInstanceState() const;

protected:
private:
};
