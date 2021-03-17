#include "ArduinoTimer.h"

ArduinoTimer::ArduinoTimer(uint8_t id)
{
	ID = id;
	ActualTime = 0;
	WantedCycleTime = (unsigned long)1E6; // 1 Second as default -> 1 Hz
	ActualCycleTime = 0;
#ifdef IN_VISUALSTUDIO
	std::cout << "ArduinoTimer[" << (int)ID << "] created." << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("ArduinoTimer[");
	Serial.print((int)ID);
	Serial.print("] created.\n");
#endif // IN_ARDUINO_IDE
	ReadRuntime();
	CycleStartedTime = ActualTime;
	PrintInstanceState();
#ifdef UNIT_TEST
	UnitTest();
#endif // UNIT_TEST
}

ArduinoTimer::~ArduinoTimer()
{
	PrintInstanceState();
}

void ArduinoTimer::ReadRuntime()
{
#ifdef IN_ARDUINO_IDE
	ActualTime = micros();
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "Set ArduinoTimer[" << (int)ID << "] Runtime in [us]:" << std::endl;
#ifndef FORCE_CYCLETIME
	ActualTime = (unsigned long)UnsignedNumericConsoleInput();
#endif // !NO_TIMER
#endif // IN_VISUALSTUDIO
}

void ArduinoTimer::SetCycleFrequency(uint16_t frequency)
{
	WantedCycleTime = (unsigned long)(1.0E6 / frequency);
}

void ArduinoTimer::ForceCycleTime()
{
#ifdef IN_VISUALSTUDIO
	std::cout << "ArduinoTimer[" << (int)ID << "] is forcing Cycle Time:" << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("T[");
	Serial.print((int)ID);
	Serial.print("] FCT\n");
#endif // IN_ARDUINO_IDE
	ReadRuntime();
	while (!GetTrigger())
	{
		// Wait here und update Runtime
		ReadRuntime();
		PrintInstanceState();
	}
}

uint8_t ArduinoTimer::GetTrigger()
{
	ActualCycleTime = ActualTime - CycleStartedTime;
	if (ActualTime < CycleStartedTime) // ActualTime Overflow detected
	{
		ActualCycleTime = ULONG_MAX - CycleStartedTime + ActualTime;
	}
	if (ActualCycleTime >= WantedCycleTime)
	{
		CycleStartedTime = ActualTime;
		return 1;
	}
	return 0;
}

unsigned long ArduinoTimer::GetActualTime()
{
	ReadRuntime();
	return ActualTime;
}

void ArduinoTimer::PrintCycleRuntime_ms()
{
	// Just to see if the wanted operating frequency can be reached
#ifdef IN_ARDUINO_IDE
	Serial.print("\nCT: ");
	Serial.print(ActualCycleTime / 1000);
	Serial.print(" [ms]\n");
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << "<>ArduinoTimer[" << (int)ID << "]: ActualCycleTime: " << ActualCycleTime / 1000 << " [ms]" << std::endl;
#endif // IN_VISUALSTUDIO
}

void ArduinoTimer::PrintInstanceState() const
{
#ifdef STATE_PRINT_TIMER
#ifdef IN_VISUALSTUDIO
	std::cout << "<>ArduinoTimer[" << (int)ID << "]:" << std::endl;
	std::cout << "WantedCycleTime: " << WantedCycleTime << " ActualCycleTime: " << ActualCycleTime
			  << "  ActualTime: " << ActualTime << " CycleStartedTime: " << CycleStartedTime << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	// Keep this short because it takes a lot of time
	Serial.print("<>AT[");
	Serial.print((int)ID);
	Serial.print("]:\nWCT: ");
	Serial.print(WantedCycleTime);
	Serial.print(" ACT: ");
	Serial.print(ActualCycleTime);
	Serial.print("\nAT: ");
	Serial.print(ActualTime);
	Serial.print(" CST: ");
	Serial.print(CycleStartedTime);
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT_TIMER
}

#ifdef IN_VISUALSTUDIO
void ArduinoTimer::UnitTest()
{
	std::cout << "ArduinoTimer Unit Test:" << std::endl;
	std::cout << "TODO" << std::endl;
	// Done with debugger
	//SetCycleFrequency(30000);
	//PrintInstanceState();
	//ForceCycleTime();
	// Normal

	// Overflow
	std::cout << std::endl
			  << "ArduinoTimer Unit Test End" << std::endl
			  << std::endl;
}
#endif // IN_VISUALSTUDIO
