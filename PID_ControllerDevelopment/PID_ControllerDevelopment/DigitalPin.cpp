#include "DigitalPin.h"

DigitalPin::DigitalPin(const uint8_t number)
{
	PinNr = number;
	PinIn = 0;
	PinOut = 0;
#ifdef IN_ARDUINO_IDE
	Get(); // Initialize With Actual Hardware State
#endif	   // IN_ARDUINO_IDE
}

DigitalPin::~DigitalPin()
{
#ifdef IN_ARDUINO_IDE
	pinMode(PinNr, INPUT);
#endif // IN_ARDUINO_IDE
}

void DigitalPin::Set(const uint8_t high_low)
{
	PinOut = high_low;
#ifdef IN_ARDUINO_IDE
	pinMode(PinNr, OUTPUT);
	digitalWrite(PinNr, PinOut);
#endif // IN_ARDUINO_IDE
}

uint8_t DigitalPin::Get()
{
#ifdef IN_ARDUINO_IDE
	pinMode(PinNr, INPUT);
	PinIn = digitalRead(PinNr);
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "Set P" << (int)PinNr << " In:" << std::endl;
	std::string userInput;
	std::getline(std::cin, userInput);
	if (userInput[0] == '0')
	{
		PinIn = 0;
	}
	else
	{
		PinIn = 1;
	}
#endif // IN_VISUALSTUDIO
	return PinIn;
}

void DigitalPin::PrintInstanceState() const
{
#ifdef STATE_PRINT
#ifdef IN_VISUALSTUDIO
	std::cout << "<>P" << (int)PinNr << ": In " << (int)PinIn << " | Out " << (int)PinOut << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("<>P");
	Serial.print((int)PinNr);
	Serial.print(": In ");
	Serial.print((int)PinIn);
	Serial.print(" | Out ");
	Serial.print((int)PinOut);
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT
}
