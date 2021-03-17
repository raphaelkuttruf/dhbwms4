#pragma once

#include "Defines.h"
#include "ArduinoIO.h"
#include "ArduinoTimer.h"
#include "ProcessModel_FOTD.h"
#include "PID_Controller.h"
#include "ControlSample.h"
#include "DataSample.h"

class LevelProcess
{
	// Variables
public:
	ArduinoIO IO;
	ArduinoTimer Timer = ArduinoTimer(1);
	ProcessModel_FOTD FOTD;
	PID_Controller PID;
	ControlSample Control;
	DataSample Data;
	//const float WaterLevel_mm_per_Bit = 0.294118f; // AnalogSignal_mm = AnalogSignal_Bit / B_Pro_mm;
	const float WaterLevel_mm_per_mV = 0.060929f; //
	const float WaterLevel_Max_mV = 3800.0f;	  // max ~230mm
protected:
	uint32_t UpdateCycleCounter;
	uint8_t WaterOverflow;
	uint8_t ActuatorOverwriteEnable; // 0=Off
	float ActuatorSpeedOverwrite_mV; // [0..5000mV]

private:
	// Funktions
public:
	LevelProcess();
	~LevelProcess();
	void SetOperatingFrequency(uint8_t frequency);
	void Run();

protected:
	void ProtectFromOverflow();
	void ReadControlSample();
	void WriteDataSample();

private:
};
