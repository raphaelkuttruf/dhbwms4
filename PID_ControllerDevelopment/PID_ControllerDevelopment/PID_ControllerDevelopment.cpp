// PID_ControllerDevelopment.cpp
// DHBW Mosbach
// Mechatronische Systeme 4
// Dr.-Ing. Vanessa Romero Segovia
// MT17B Gruppe 3 (Sarah Plieninger, Fabian Redaoui, Raphael Kuttruf)

#include "Defines.h" // Check this File before Compiling !
#ifdef IN_VISUALSTUDIO
#include <iostream>

#include "LevelProcess.h"
#include "Serial_SimulinkInterface.h"

int main()
{
	std::cout << "Have Fun Coding and Debugging!" << std::endl;
	std::cout << VERSION << std::endl;
	std::string nextcycle = "y";
	uint32_t Cycles = 0;

	ArduinoIO IO;
	Serial_SimulinkInterface Interface;
	LevelProcess WaterLevelProcess;
	WaterLevelProcess.SetOperatingFrequency(OPERATING_FREQUENCY);
#ifdef CONSTANT_WATERLEVEL
	IO.MeasureA0(); // Read Water Level Sensor
#endif // CONSTANT_WATERLEVEL

	// CYCLIC EXECUTION
	while (nextcycle[0] != 'x')
	{
		Interface.RecieveSerial();
		Interface.MirrorRecievedSerial();
		Interface.DeserializeControlSample(WaterLevelProcess.Control);

		WaterLevelProcess.Run();

		Interface.SerializeDataSample(WaterLevelProcess.Data);
		Interface.PrintInstanceState();
		Interface.SendSerial();
		//
		std::cout << "End Cycle Nr: " << Cycles << std::endl;
		//std::cout << "Continue / Exit with [x]: " << std::endl;
		//std::getline(std::cin, nextcycle);
		Cycles++;
	}
}

double UnsignedNumericConsoleInput()
{
	std::string userInput;
	std::getline(std::cin, userInput);
	while (userInput.find_first_not_of("0123456789.") != std::string::npos || userInput.find_first_of("0123456789.") == std::string::npos)
	{
		std::cout << "[UnsignedNumeric] Try again!" << std::endl;
		std::getline(std::cin, userInput);
	}
	return std::stod(userInput + " "); // Throws exeption for invalid input !
}

double NumericConsoleInput()
{
	std::string userInput;
	std::getline(std::cin, userInput);
	while (userInput.find_first_not_of("-0123456789.") != std::string::npos || userInput.find_first_of("-0123456789.") == std::string::npos)
	{
		std::cout << "[Numeric] Try again!" << std::endl;
		std::getline(std::cin, userInput);
	}
	return std::stod(userInput + " "); // Throws exeption for invalid input !
}

#endif // IN_VISUALSTUDIO
