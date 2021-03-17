#pragma once

#include "Defines.h"
#include <stdint.h>

class DataSample
{
	// Variables
public:
	uint32_t SampleNr;
	uint16_t SystemState_mV;
	uint16_t SystemState_mm;
	uint16_t SystemStatePostFilter_mV;
	uint16_t SystemStatePostFilter_mm;
	uint16_t ControllerSetpoint_mm;
	uint16_t ConrollerOutput_mV;
	uint16_t ActuatorOutput_mV;
	uint8_t ActuatorOutput_Bit;
	uint8_t OverflowDetected;
	uint16_t PID_P; // + 32768 offset
	uint16_t PID_I; // + 32768 offset
	uint16_t PID_D; // + 32768 offset

protected:
private:
	// Funktions
public:
	DataSample();
	~DataSample();
	void OverwriteWithTestData();
	void PrintInstanceState() const;

protected:
private:
};
