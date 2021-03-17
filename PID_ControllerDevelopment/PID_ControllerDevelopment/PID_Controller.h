#pragma once

#include "Defines.h"
#include <stdint.h>
#include <math.h>
#include "Saturator.h"
#include "SecondOrderFilter.h"

// https://en.wikipedia.org/wiki/PID_controller

class PID_Controller
{
	// Variables
public:
	SecondOrderFilter InputFilter;

protected:
	float OperatingFrequency;
	float Setpoint;
	float ActualState;
	//float ActualStateOld;
	float ActualError;
	float OldError;
	float KP;
	float KI;
	float KD;
	float Tr;	 // Tracking Constant for anti-Windup = sqrt(Ti * Td) with [Td < Tr < Ti]
	float Beta;	 // Smooth proportionanal response
	float Gamma; // Smooth differential response
	float Outputsignal_P;
	float Outputsignal_I;
	float Outputsignal_D;
	float Outputsignal;
	float OutputsignalSaturated;
	uint8_t ModeSelect; // [ 1=PI, 2=PID, 3=PID Fitered]
	uint8_t AntiWindupEnable;

private:
	// Funktions
public:
	PID_Controller();
	~PID_Controller();
	void SetOperatingFrequency(const uint16_t frequency);
	void SetSetpoint(const float setpoint);
	void SetBeta(const uint8_t PID_Beta);	// [0..255] => [0..1]
	void SetGamma(const uint8_t PID_Gamma); // [0..255] => [0..1]
	void SetAntiWindup(const uint8_t enable);
	void SetTuningParameter(const float kP, const float Ti);
	void SetTuningParameter(const float kP, const float Ti, const float Td);
	void ControlProcess(const float actualState);
	float GetSetpoint() const;
	float GetOutputsignal() const;
	float GetOutputsignalSaturated() const;
	float GetOutputsignal_P() const;
	float GetOutputsignal_I() const;
	float GetOutputsignal_D() const;

protected:
	void Control_PI();
	void Control_PID();
	void Compute_P();
	void Compute_I();
	void AntiWindup();
	void Compute_D();
	void PrintInstanceState() const;
#ifdef IN_VISUALSTUDIO
	void UnitTest();
#endif // IN_VISUALSTUDIO

private:
};
