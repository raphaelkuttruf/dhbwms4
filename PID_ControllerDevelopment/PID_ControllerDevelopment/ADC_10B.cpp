#include "ADC_10B.h"

ADC_10B::ADC_10B(const uint8_t pinNr)
{
	PinNr = pinNr;
	AnalogSignal_Bit = 0;
	AnalogSignal_mVolt = 0.0f;
}

ADC_10B::~ADC_10B()
{
}

void ADC_10B::UpdateSignal(const int16_t signal_Bit)
{
	if (AnalogSignal_Bit != signal_Bit)
	{
		AnalogSignal_Bit = signal_Bit;
		AnalogSignal_mVolt = AnalogSignal_Bit * Max_mV / Max_Bit;
	}
}

int16_t ADC_10B::Get_Bit() const
{
	return AnalogSignal_Bit;
}

float ADC_10B::Get_mVolt() const
{
	return AnalogSignal_mVolt;
}

void ADC_10B::PrintInstanceState() const
{
#ifdef STATE_PRINT
#ifdef IN_VISUALSTUDIO
	std::cout << "<>A" << (int)PinNr << ": " << AnalogSignal_Bit << " [B] = " << AnalogSignal_mVolt << " [mV]" << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("<>A");
	Serial.print((int)PinNr);
	Serial.print(": ");
	Serial.print(AnalogSignal_Bit);
	Serial.print(" [B] = ");
	Serial.print(AnalogSignal_mVolt);
	Serial.write(' [mV]\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT
}
