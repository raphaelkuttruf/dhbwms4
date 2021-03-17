#include "ArduinoIO.h"

ArduinoIO::ArduinoIO()
{
#ifdef IN_ARDUINO_IDE
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A4, INPUT);
	pinMode(A5, INPUT);
#endif // IN_ARDUINO_IDE
}

ArduinoIO::~ArduinoIO()
{
}

void ArduinoIO::MeasureA0()
{
#ifdef IN_ARDUINO_IDE
	ADC_A0.UpdateSignal(analogRead(A0));
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "Set A0 In[0..1023]:" << std::endl;
	float inputValue = (float)NumericConsoleInput();
	Saturator::MaxMin(inputValue, 0.0f, 1023.0f);
	ADC_A0.UpdateSignal((uint16_t)inputValue);
#endif // IN_VISUALSTUDIO
}

void ArduinoIO::MeasureA1()
{
#ifdef IN_ARDUINO_IDE
	ADC_A1.UpdateSignal(analogRead(A1));
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "Set A1 In[0..1023]:" << std::endl;
	float inputValue = (float)NumericConsoleInput();
	Saturator::MaxMin(inputValue, 0.0f, 1023.0f);
	ADC_A0.UpdateSignal((uint16_t)inputValue);
#endif // IN_VISUALSTUDIO
}

void ArduinoIO::MeasureA2()
{
#ifdef IN_ARDUINO_IDE
	ADC_A2.UpdateSignal(analogRead(A2));
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "Set A2 In[0..1023]:" << std::endl;
	float inputValue = (float)NumericConsoleInput();
	Saturator::MaxMin(inputValue, 0.0f, 1023.0f);
	ADC_A0.UpdateSignal((uint16_t)inputValue);
#endif // IN_VISUALSTUDIO
}

void ArduinoIO::MeasureA3()
{
#ifdef IN_ARDUINO_IDE
	ADC_A3.UpdateSignal(analogRead(A3));
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "Set A3 In[0..1023]:" << std::endl;
	float inputValue = (float)NumericConsoleInput();
	Saturator::MaxMin(inputValue, 0.0f, 1023.0f);
	ADC_A0.UpdateSignal((uint16_t)inputValue);
#endif // IN_VISUALSTUDIO
}

void ArduinoIO::MeasureA4()
{
#ifdef IN_ARDUINO_IDE
	ADC_A4.UpdateSignal(analogRead(A4));
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "Set A4 In[0..1023]:" << std::endl;
	float inputValue = (float)NumericConsoleInput();
	Saturator::MaxMin(inputValue, 0.0f, 1023.0f);
	ADC_A0.UpdateSignal((uint16_t)inputValue);
#endif // IN_VISUALSTUDIO
}

void ArduinoIO::MeasureA5()
{
#ifdef IN_ARDUINO_IDE
	ADC_A5.UpdateSignal(analogRead(A5));
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "Set A5 In[0..1023]:" << std::endl;
	float inputValue = (float)NumericConsoleInput();
	Saturator::MaxMin(inputValue, 0.0f, 1023.0f);
	ADC_A0.UpdateSignal((uint16_t)inputValue);
#endif // IN_VISUALSTUDIO
}

void ArduinoIO::MeasureAllAnalog()
{
	MeasureA0();
	MeasureA1();
	MeasureA2();
	MeasureA3();
	MeasureA4();
	MeasureA5();
}

void ArduinoIO::PrintInstanceState()
{
#ifdef STATE_PRINT_IO
#ifdef IN_VISUALSTUDIO
	std::cout << "<>ArduinoIO: " << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("<>ArduinoIO: ");
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
	ADC_A0.PrintInstanceState();
	ADC_A1.PrintInstanceState();
	ADC_A2.PrintInstanceState();
	ADC_A3.PrintInstanceState();
	ADC_A4.PrintInstanceState();
	ADC_A5.PrintInstanceState();
	P1.PrintInstanceState();
	P2.PrintInstanceState();
	P3.PrintInstanceState();
	P4.PrintInstanceState();
	P5.PrintInstanceState();
	P6.PrintInstanceState();
	P7.PrintInstanceState();
	P8.PrintInstanceState();
	P9.PrintInstanceState();
	P10.PrintInstanceState();
	P11.PrintInstanceState();
	P12.PrintInstanceState();
	P13.PrintInstanceState();
#endif // STATE_PRINT_IO
}
