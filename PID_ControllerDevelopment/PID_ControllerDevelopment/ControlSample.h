#pragma once

#include "Defines.h"
#include <stdint.h>

class ControlSample
{
	// Variables
public:
	uint32_t SampleNr; // Cout recieved Samples
	uint16_t Setpoint_mm;
	uint16_t FOTD_K;					// Static Gain
	uint16_t FOTD_T;					// Apparent Time Delay
	uint16_t FOTD_L;					// Apparent Time Constant
	uint8_t SelectTuningMethod;			// [1=PI AMIGO, 2=PID AMIGO, 3=PI Lambda, 4=PID Lambda, 5=PI SIMC, 6=PID SIMC]
	uint8_t Lambda_Tcl_Mode;			// [1, 2, 3] = > [L, T, 3T]
	uint8_t FilterAlpha;				// [1..5] => [0.01..0.05], 0 => Bypass
	uint8_t PID_Beta;					// [0..255] => [Min,Max]
	uint8_t PID_Gamma;					// [0..255] => [Min,Max]
	uint8_t AntiWindupEnable;			// 0=Off
	uint8_t ActuatorOverwriteEnable;	// 0=Off
	uint16_t ActuatorSpeedOverwrite_mV; // [0..5000mV]

protected:
	uint8_t NewDataFlag;

private:
	// Funktions
public:
	ControlSample();
	~ControlSample();
	void OverwriteWithTestData();
	void PrintInstanceState() const;

protected:
private:
};
