#include "PID_Controller.h"

PID_Controller::PID_Controller()
{
	OperatingFrequency = 1.0f;
	Setpoint = 0.0f;
	ActualState = 0.0f;
	ActualError = 0.0f;
	OldError = 0.0f;
	//ActualStateOld = 0.0f;
	KP = 0.0f;
	KI = 0.0f;
	KD = 0.0f;
	Tr = 0.0f;
	Beta = 1.0f;
	Gamma = 1.0f;
	Outputsignal_P = 0.0f;
	Outputsignal_I = 0.0f;
	Outputsignal_D = 0.0f;
	Outputsignal = 0.0f;
	OutputsignalSaturated = 0.0f;
	ModeSelect = 0;
	AntiWindupEnable = 0;
#ifdef UNIT_TEST
	//UnitTest();
#endif // UNIT_TEST
}

PID_Controller::~PID_Controller()
{
}

void PID_Controller::SetOperatingFrequency(const uint16_t frequency)
{
	OperatingFrequency = frequency;
	InputFilter.SetOperatingFrequency(frequency);
}

void PID_Controller::SetSetpoint(const float setpoint)
{
	Setpoint = setpoint;
}

void PID_Controller::SetBeta(const uint8_t PID_Beta)
{
	Beta = PID_Beta / 255.0f;
}

void PID_Controller::SetGamma(const uint8_t PID_Gamma)
{
	Gamma = PID_Gamma / 255.0f;
}

void PID_Controller::SetAntiWindup(const uint8_t enable)
{
	AntiWindupEnable = enable;
}

void PID_Controller::SetTuningParameter(const float kP, const float Ti)
{
	ModeSelect = 1;
	KP = kP;
	KI = kP / (Ti * OperatingFrequency);
	Tr = sqrtf(Ti);
}

void PID_Controller::SetTuningParameter(const float kP, const float Ti, const float Td)
{
	ModeSelect = 2;
	KP = kP;
	KI = kP / (Ti * OperatingFrequency);
	KD = kP * Td * OperatingFrequency;
	Tr = sqrtf(Ti * Td);
	Saturator::MinMax(Tr, Tr, Ti);
	if (InputFilter.GetAlphaMode()) // Filter is Active
	{
		ModeSelect = 3;
	}
}
void PID_Controller::ControlProcess(const float actualState)
{
	//ActualStateOld = ActualState;
	ActualState = actualState;
	OldError = ActualError;
	ActualError = Setpoint - actualState;
	InputFilter.Filter(actualState);
	switch (ModeSelect)
	{
	case 1:
		Control_PI();
		break;
	default:
		Control_PID();
		break;
	}
#ifdef STATE_PRINT_PID
	PrintInstanceState();
#endif // STATE_PRINT_PID
}

void PID_Controller::Control_PI()
{
	Compute_P();
	Compute_I();
	Outputsignal_D = 0.0f;
	AntiWindup();
}

void PID_Controller::Control_PID()
{
	Compute_P();
	Compute_I();
	Compute_D();
	AntiWindup();
}

void PID_Controller::Compute_P()
{
	Outputsignal_P = KP * (Setpoint * Beta - ActualState);
}

void PID_Controller::Compute_I()
{
	Outputsignal_I += KI * ActualError;
}

void PID_Controller::AntiWindup()
{
	Outputsignal = Outputsignal_P + Outputsignal_I + Outputsignal_D;
	OutputsignalSaturated = Saturator::MaxMinC(Outputsignal, 0.0f, 5000.0f);
	if (AntiWindupEnable)
	{
		Outputsignal_I += (1.0f / (Tr * OperatingFrequency)) * (OutputsignalSaturated - Outputsignal);
		Outputsignal = Outputsignal_P + Outputsignal_I + Outputsignal_D;
		OutputsignalSaturated = Saturator::MaxMinC(Outputsignal, 0.0f, 5000.0f);
	}
}

void PID_Controller::Compute_D()
{
	switch (ModeSelect)
	{
	case 2:
		//Outputsignal_D = KD * (Gamma * ActualState - ActualStateOld);
		Outputsignal_D = KD * (Gamma * ActualError - OldError);
		break;
	case 3:
		// Filter is active
		Outputsignal_D = -KD * InputFilter.GetFilteredSignalDerivative(); // No Gamma Applied !!
		break;
	default:
		Outputsignal_D = 0.0f;
		break;
	}
 Outputsignal_D /= 5.0f;
	Saturator::MaxMin(Outputsignal_D, -2000.0f, 2000.f);
}

float PID_Controller::GetSetpoint() const
{
	return Setpoint;
}

float PID_Controller::GetOutputsignal() const
{
	return Outputsignal;
}

float PID_Controller::GetOutputsignalSaturated() const
{
	return OutputsignalSaturated;
}

float PID_Controller::GetOutputsignal_P() const
{
	return Outputsignal_P;
}
float PID_Controller::GetOutputsignal_I() const
{
	return Outputsignal_I;
}
float PID_Controller::GetOutputsignal_D() const
{
	return Outputsignal_D;
}

void PID_Controller::PrintInstanceState() const
{
#ifdef STATE_PRINT_PID
#ifdef IN_VISUALSTUDIO
	std::cout << "<>PID_Controller:" << std::endl;
	std::cout << "ModeSelect:" << ModeSelect << " AntiWindupEnable: " << AntiWindupEnable std::endl;
	std::cout << "KP: " << KP << " KI: " << KI << " KD: " << KD << " Beta: " << Beta << " Gamma: " << Gamma << " Tr: " << Tr << std::endl;
	std::cout << "Setpoint: " << Setpoint << " ActualState: " << ActualState << std::endl;
	std::cout << "ActualError: " << ActualError << " OldError: " << OldError << std::endl;
	std::cout << "Outputsignal_P: " << Outputsignal_P << " Outputsignal_I: " << Outputsignal_I << " Outputsignal_D: " << Outputsignal_D << std::endl;
	std::cout << "Outputsignal: " << Outputsignal << " OutputsignalSaturated: " << OutputsignalSaturated << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("<>PID_Controller:\n");
	Serial.print("\nModeSelect:");
	Serial.print(ModeSelect);
	Serial.print(" AntiWindupEnable: ");
	Serial.print(AntiWindupEnable);
	Serial.print("\nKP: ");
	Serial.print(KP);
	Serial.print(" KI*10e3: ");
	Serial.print(KI * 1000);
	Serial.print(" KD: ");
	Serial.print(KD);
	Serial.print(" Beta: ");
	Serial.print(Beta);
	Serial.print(" Gamma: ");
	Serial.print(Gamma);
	Serial.print(" Tr: ");
	Serial.print(Tr);
	Serial.print("\nSetpoint: ");
	Serial.print(Setpoint);
	Serial.print(" ActualState: ");
	Serial.print(ActualState);
	Serial.print("\nActualError: ");
	Serial.print(ActualError);
	Serial.print(" OldError: ");
	Serial.print(OldError);
	Serial.print("\nOutputsignal_P: ");
	Serial.print(Outputsignal_P);
	Serial.print(" Outputsignal_I: ");
	Serial.print(Outputsignal_I);
	Serial.print(" Outputsignal_D: ");
	Serial.print(Outputsignal_D);
	Serial.print("\nOutputsignal: ");
	Serial.print(Outputsignal);
	Serial.print(" OutputsignalSaturated: ");
	Serial.print(OutputsignalSaturated);
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT_PID
}

#ifdef IN_VISUALSTUDIO
void PID_Controller::UnitTest()
{
	std::cout << "PID_Controller Unit Test:" << std::endl;
	std::cout << "TODO" << std::endl;
	SetBeta(0);
	SetBeta(120);
	SetBeta(255);
	SetGamma(0);
	SetGamma(80);
	SetGamma(255);
	SetOperatingFrequency(10);
	SetTuningParameter(0.925f, 41.59f);		  // PI
	SetTuningParameter(1.82f, 32.97f, 4.47f); // PID
	SetSetpoint(10.0f);
	float ActState = 0.0f;
	for (size_t i = 0; i < 200; i++)
	{
		ControlProcess(ActState);
		ActState += GetOutputsignalSaturated() / (2.0f * OperatingFrequency);
		ActState -= 1.0f;
	}

	std::cout << std::endl
			  << "PID_Controller Unit Test End" << std::endl
			  << std::endl;
}
#endif // IN_VISUALSTUDIO
