#pragma once

#include "Defines.h"
#include <limits.h>
#include "Saturator.h"

class ArduinoTimer
{
	// Variables
public:
protected:
	uint8_t ID;						// Identification Number
	unsigned long ActualTime;		// [us], overflow after ~70 min
	unsigned long CycleStartedTime; // [us], last Measurment with ReadRuntime()
	unsigned long WantedCycleTime;	// [us], Time between trigger Flags
	unsigned long ActualCycleTime;	// [us]

private:
	// Funktions
public:
	ArduinoTimer(uint8_t id);
	~ArduinoTimer();
	unsigned long GetActualTime();
	void SetCycleFrequency(uint16_t frequency);

	// Call in a cyclic execution to set exact execution frequency
	// (compensates for program execution time as long as the wanted cycle time is smaller than the needed program execution time)
	void ForceCycleTime();
	uint8_t GetTrigger(); // Returns 1 if more time is passed than a cycle should take
	void PrintCycleRuntime_ms();
	void PrintInstanceState() const;

protected:
	void ReadRuntime();
#ifdef IN_VISUALSTUDIO
	void UnitTest();
#endif // IN_VISUALSTUDIO
private:
};
