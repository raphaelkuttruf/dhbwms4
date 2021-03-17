#include "ControlSample.h"

ControlSample::ControlSample()
{
	SampleNr = 0;
	Setpoint_mm = 0;
	FOTD_K = 0;
	FOTD_T = 0;
	FOTD_L = 0;
	SelectTuningMethod = 0;
	Lambda_Tcl_Mode = 0;
	FilterAlpha = 0;
	PID_Beta = 0;
	PID_Gamma = 0;
	AntiWindupEnable = 0;
	ActuatorOverwriteEnable = 0;
	ActuatorSpeedOverwrite_mV = 0;

	NewDataFlag = 0;
}

ControlSample::~ControlSample()
{
}

void ControlSample::PrintInstanceState() const
{
#ifdef STATE_PRINT_CONTROLSAMPLE
#ifdef IN_VISUALSTUDIO
	std::cout << "<>ControlSample:" << std::endl;
	std::cout << "SampleNr: " << SampleNr << std::endl;
	std::cout << "Setpoint_mm: " << Setpoint_mm << std::endl;
	std::cout << "FOTD_K: " << FOTD_K << " FOTD_T: " << FOTD_T << " FOTD_T: " << FOTD_T << std::endl;
	std::cout << "SelectTuningMethod: " << (int)SelectTuningMethod << " Lambda_Tcl_Mode: " << (int)Lambda_Tcl_Mode << std::endl;
	std::cout << "FilterAlpha: " << (int)FilterAlpha << std::endl;
	std::cout << "PID_Beta: " << (int)PID_Beta << " PID_Gamma: " << (int)PID_Gamma << " AntiWindupEnable: " << (int)AntiWindupEnable << std::endl;
	std::cout << "ActuatorOverwriteEnable: " << (int)ActuatorOverwriteEnable << " ActuatorOverwriteEnable: " << ActuatorSpeedOverwrite_mV << std::endl;
	std::cout << "NewDataFlag: " << (int)NewDataFlag << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("<>ControlSample:\n");
	Serial.print("SampleNr: ");
	Serial.print(SampleNr);
	Serial.print("\nSetpoint_mm: ");
	Serial.print(Setpoint_mm);
	Serial.print("\nFOTD_K: ");
	Serial.print(FOTD_K);
	Serial.print(" FOTD_T: ");
	Serial.print(FOTD_T);
	Serial.print(" FOTD_T: ");
	Serial.print(FOTD_T);
	Serial.print("\nSelectTuningMethod: ");
	Serial.print((int)SelectTuningMethod);
	Serial.print(" Lambda_Tcl_Mode: ");
	Serial.print((int)Lambda_Tcl_Mode);
	Serial.print("\nFilterAlpha: ");
	Serial.print((int)FilterAlpha);
	Serial.print("\nPID_Beta: ");
	Serial.print((int)PID_Beta);
	Serial.print(" PID_Gamma: ");
	Serial.print((int)PID_Gamma);
	Serial.print(" AntiWindupEnable: ");
	Serial.print((int)AntiWindupEnable);
	Serial.print("\nActuatorOverwriteEnable: ");
	Serial.print((int)ActuatorOverwriteEnable);
	Serial.print(" ActuatorOverwriteEnable: ");
	Serial.print(ActuatorSpeedOverwrite_mV);
	Serial.print("\nNewDataFlag: ");
	Serial.print((int)NewDataFlag);
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT_CONTROLSAMPLE
}

void ControlSample::OverwriteWithTestData()
{
	// Values From Documentation
	Setpoint_mm = 60;
	FOTD_K = 147;  // 1.47
	FOTD_T = 5500; // 55
	FOTD_L = 1000; // 10
	SelectTuningMethod = 6;
	Lambda_Tcl_Mode = 0;		 // L
	FilterAlpha = 2;			 // 0.02
	PID_Beta = 255;				 // 1.0
	PID_Gamma = 255;			 // 1.0
	AntiWindupEnable = 1;		 // 0=Off
	ActuatorOverwriteEnable = 0; // 0=Off
	ActuatorSpeedOverwrite_mV = 1000;

	NewDataFlag = 0;
}
