#include "DataSample.h"

DataSample::DataSample()
{
	SampleNr = 0;
	SystemState_mV = 0;
	SystemState_mm = 0;
	SystemStatePostFilter_mV = 0;
	SystemStatePostFilter_mm = 0;
	ControllerSetpoint_mm = 0;
	ConrollerOutput_mV = 0;
	ActuatorOutput_mV = 0;
	ActuatorOutput_Bit = 0;
	OverflowDetected = 0;
	PID_P = 32768;
	PID_I = 32768;
	PID_D = 32768;
}

DataSample::~DataSample()
{
}

void DataSample::OverwriteWithTestData()
{
	SampleNr = 111111;
	SystemState_mV = 22222;
	SystemState_mm = -3333;
	SystemStatePostFilter_mV = 4444;
	SystemStatePostFilter_mm = 5555;
	ControllerSetpoint_mm = 6666;
	ConrollerOutput_mV = 7777;
	ActuatorOutput_mV = 88;
	ActuatorOutput_Bit = 99;
}

void DataSample::PrintInstanceState() const
{
#ifdef STATE_PRINT_DATASAMPLE
#ifdef IN_VISUALSTUDIO
	std::cout << "<>DataSample:" << std::endl;
	std::cout << "SampleNr: " << SampleNr << std::endl;
	std::cout << "SystemState_mV: " << SystemState_mV << " SystemState_mm: " << SystemState_mm << std::endl;
	std::cout << "SystemStatePostFilter_mV: " << SystemStatePostFilter_mV << " SystemStatePostFilter_mm: " << SystemStatePostFilter_mm << std::endl;
	std::cout << "ControllerSetpoint_mm: " << ControllerSetpoint_mm << std::endl;
	std::cout << "ConrollerOutput_mV: " << ConrollerOutput_mV << std::endl;
	std::cout << "ActuatorOutput_mV: " << ActuatorOutput_mV << " ActuatorOutput_Bit: " << (int)ActuatorOutput_Bit << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("<>DataSample:\n");
	Serial.print("SampleNr: ");
	Serial.print(SampleNr);
	Serial.print("\nSystemState_mV: ");
	Serial.print(SystemState_mV);
	Serial.print(" SystemState_mm: ");
	Serial.print(SystemState_mm);
	Serial.print("\nSystemStatePostFilter_mV: ");
	Serial.print(SystemStatePostFilter_mV);
	Serial.print(" SystemStatePostFilter_mm: ");
	Serial.print(SystemStatePostFilter_mm);
	Serial.print("\nControllerSetpoint_mm: ");
	Serial.print(ControllerSetpoint_mm);
	Serial.print("\nConrollerOutput_mV: ");
	Serial.print(ConrollerOutput_mV);
	Serial.print("\nActuatorOutput_mV: ");
	Serial.print(ActuatorOutput_mV);
	Serial.print(" ActuatorOutput_Bit: ");
	Serial.print((int)ActuatorOutput_Bit);
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT_DATASAMPLE
}