#pragma once

#include "Defines.h"
#include <stdint.h>
#include "Saturator.h"

class SecondOrderFilter
{
	// Variables
public:
protected:
	float OperatingFrequency;
	float SampleTime; // = 1 / OperatingFrequency
	float Alpha;
	uint8_t AlphaMode;
	float SampleTimeSqared; // h^2
	float FilterTimeConstant;
	float FilterTimeConstantSquared;
	float P[5] = {0};
	float Denominator; // Equation Denominator
	float Inputsignal;
	float FilteredSignal;
	float FilteredSignalDerivative;

private:
	// Funktions
public:
	SecondOrderFilter();
	~SecondOrderFilter();
	void Initialize();
	void SetOperatingFrequency(uint16_t frequency);
	void SetAlpha(uint8_t alpha);
	void ComputeFilterTimeConstant_AMIGO(float L0, float tau);
	void ComputeFilterTimeConstant_Lambda(float L0, float tau, uint8_t Tcl_Mode);
	void ComputeFilterTimeConstant_SIMCE(float L0, float tau);
	void Filter(float signal);
	float GetAlpha() const;
	uint8_t GetAlphaMode() const;
	float GetFilterTimeConstant() const;
	float GetBypassedSignal() const;
	float GetFilteredSignal() const;
	float GetFilteredSignalDerivative() const;
	void PrintInstanceState() const;

protected:
#ifdef IN_VISUALSTUDIO
	void UnitTest();
#endif // IN_VISUALSTUDIO
private:
};
