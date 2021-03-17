#include "DigitalPinPWM.h"

DigitalPinPWM::DigitalPinPWM(const uint8_t number) : DigitalPin(number)
{
	PinOut_mV = 0.0f;
#ifdef IN_ARDUINO_IDE
	pinMode(PinNr, OUTPUT);
	analogWrite(PinNr, PinOut);
#endif // IN_ARDUINO_IDE
}

DigitalPinPWM::~DigitalPinPWM()
{
}

void DigitalPinPWM::PMW_Bit(const uint8_t pwm_Bit)
{
	PinOut_mV = pwm_Bit * Max_mV / Max_Bit;
	PinOut = pwm_Bit;
#ifdef IN_ARDUINO_IDE
	pinMode(PinNr, OUTPUT);
	analogWrite(PinNr, PinOut);
#endif // IN_ARDUINO_IDE
}

void DigitalPinPWM::PWM_mV(float pwm_mV)
{
	Saturator::MaxMin(pwm_mV, 0.0f, Max_mV);
	PinOut_mV = pwm_mV;
	PinOut = (uint8_t)(pwm_mV * Max_Bit / Max_mV);
#ifdef IN_ARDUINO_IDE
	pinMode(PinNr, OUTPUT);
	analogWrite(PinNr, PinOut);
#endif // IN_ARDUINO_IDE
}

uint8_t DigitalPinPWM::GetPMW_Bit() const
{
	return PinOut;
}

float DigitalPinPWM::GetPMW_mV() const
{
	return PinOut_mV;
}
