#pragma once

#include "Defines.h"
#include "DigitalPin.h"
#include "Saturator.h"

class DigitalPinPWM : public DigitalPin
{
	// Variables
public:
	const float Max_mV = 5000.0f; // 5V
	const float Max_Bit = 255.0f; // 8 Bit Resolution
protected:
	float PinOut_mV; // [0V..5V]
private:
	// Funktions
public:
	DigitalPinPWM(const uint8_t number);
	~DigitalPinPWM();
	void PMW_Bit(const uint8_t pwm_Bit);
	void PWM_mV(float pwm_mV);
	uint8_t GetPMW_Bit() const;
	float GetPMW_mV() const;

protected:
private:
};
