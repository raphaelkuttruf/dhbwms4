#include "SecondOrderFilter.h"

SecondOrderFilter::SecondOrderFilter()
{
	OperatingFrequency = 0.0f;
	Alpha = 0.0f;
	AlphaMode = 0;
	SampleTime = 0.0f;
	SampleTimeSqared = 0.0f;
	FilterTimeConstant = 0.0f;
	FilterTimeConstantSquared = 0.0f;
	Denominator = 0.0f;
	Inputsignal = 0.0f;
	FilteredSignal = 0.0f;
	FilteredSignalDerivative = 0.0f;
#ifdef UNIT_TEST
	//UnitTest(); // Test passed
#endif // UNIT_TEST
}

SecondOrderFilter::~SecondOrderFilter()
{
}

void SecondOrderFilter::Initialize()
{
	P[0] = 0.0f;
	P[1] = 0.0f;
	P[2] = 0.0f;
	P[3] = 0.0f;
	P[4] = 0.0f;
	Denominator = 0.0f;
	Inputsignal = 0.0f;
	FilteredSignal = 0.0f;
	FilteredSignalDerivative = 0.0f;
}

void SecondOrderFilter::SetOperatingFrequency(uint16_t frequency)
{
	OperatingFrequency = frequency;
	SampleTime = 1.0f / frequency;
	SampleTimeSqared = SampleTime * SampleTime;
	Initialize();
}

void SecondOrderFilter::SetAlpha(uint8_t alpha)
{
	AlphaMode = alpha;
	Alpha = alpha / 100.0f;
	Saturator::Max(Alpha, 0.05f);
}

void SecondOrderFilter::ComputeFilterTimeConstant_AMIGO(float L0, float tau)
{
	FilterTimeConstant = 2.0f * Alpha * L0;
	FilterTimeConstantSquared = FilterTimeConstant * FilterTimeConstant;
}

void SecondOrderFilter::ComputeFilterTimeConstant_Lambda(float L0, float tau, uint8_t Tcl_Mode)
{
	switch (Tcl_Mode)
	{
	default:
		FilterTimeConstant = (1.8f - tau) * Alpha * L0;
		;
		break;
	case 2:
		FilterTimeConstant = (0.7f / (tau - 0.02f)) * Alpha * L0;
		;
		break;
	}
	FilterTimeConstantSquared = FilterTimeConstant * FilterTimeConstant;
}

void SecondOrderFilter::ComputeFilterTimeConstant_SIMCE(float L0, float tau)
{
	FilterTimeConstant = 1.5f * Alpha * L0;
	FilterTimeConstantSquared = FilterTimeConstant * FilterTimeConstant;
}

void SecondOrderFilter::Filter(float signal)
{
	Inputsignal = signal;
	if (AlphaMode) // 0=Bypass
	{
		Denominator = FilterTimeConstantSquared / 2.0f + SampleTime * FilterTimeConstant + SampleTimeSqared;
		P[0] = 1.0f - SampleTimeSqared / Denominator;
		P[1] = SampleTime * FilterTimeConstantSquared / (2.0f * Denominator);
		P[2] = SampleTimeSqared / Denominator;
		P[3] = FilterTimeConstantSquared / (2.0f * Denominator);
		P[4] = SampleTime / Denominator;
		FilteredSignal = P[0] * FilteredSignal + P[1] * FilteredSignalDerivative + P[2] * Inputsignal;
		//Saturator::Min(FilteredSignal, 0.0f); // Not a good idea but neccessary to protect from variable overflow in Serial Signal
		FilteredSignalDerivative = P[3] * FilteredSignalDerivative - P[4] * FilteredSignal + P[4] * Inputsignal;
	}
	else
	{
		FilteredSignal = Inputsignal;
	}
	PrintInstanceState();
}

float SecondOrderFilter::GetAlpha() const
{
	return Alpha;
}

uint8_t SecondOrderFilter::GetAlphaMode() const
{
	return AlphaMode;
}

float SecondOrderFilter::GetFilterTimeConstant() const
{
	return FilterTimeConstant;
}

float SecondOrderFilter::GetBypassedSignal() const
{
	return Inputsignal;
}

float SecondOrderFilter::GetFilteredSignal() const
{
	return FilteredSignal;
}

float SecondOrderFilter::GetFilteredSignalDerivative() const
{
	return FilteredSignalDerivative;
}

void SecondOrderFilter::PrintInstanceState() const
{
#ifdef STATE_PRINT_2O_FILTER
#ifdef IN_VISUALSTUDIO
	std::cout << "SecondOrderFilter:" << std::endl;
	std::cout << "Inputsignal: " << Inputsignal << " FilterTimeConstant: " << FilterTimeConstant << std::endl;
	std::cout << "P[0]: " << P[0] << " P[1]: " << P[1] << " P[2]: " << P[2] << "P[3]: " << P[3] << " P[4]: " << P[4] << std::endl;
	std::cout << " Alpha: " << Alpha << " SampleTime: " << SampleTime << " Denominator: " << Denominator << std::endl;
	std::cout << "FilteredSignal: " << FilteredSignal << " FilteredSignalDerivative: " << FilteredSignalDerivative << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("SecondOrderFilter:\n");
	;
	Serial.print("Inputsignal: ");
	Serial.print(Inputsignal);
	Serial.print(" FilterTimeConstant: ");
	Serial.print(FilterTimeConstant);
	Serial.print("P[0]: ");
	Serial.print(P[0]);
	Serial.print(" P[1]: ");
	Serial.print(P[1]);
	Serial.print(" P[2]: ");
	Serial.print(P[2]);
	Serial.print("P[3]: ");
	Serial.print(P[3]);
	Serial.print(" P[4]: ");
	Serial.print(P[4]);
	Serial.print("\nAlpha: ");
	Serial.print(Alpha);
	Serial.print(" SampleTime: ");
	Serial.print(SampleTime);
	Serial.print(" Denominator: ");
	Serial.print(Denominator);
	Serial.print("\nFilteredSignal: ");
	Serial.print(FilteredSignal);
	Serial.print(" FilteredSignalDerivative: ");
	Serial.print(FilteredSignalDerivative);
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT_2O_FILTER
}

#ifdef IN_VISUALSTUDIO
void SecondOrderFilter::UnitTest()
{
	std::cout << std::endl
			  << "SecondOrderFilter Unit Test:" << std::endl
			  << std::endl;

	float Tau = 10.0f / (10.0f + 55.0f); // Tau = L / (L + T); // L=10, T=55

	Initialize();
	SetAlpha(2);
	SetOperatingFrequency(50);
	ComputeFilterTimeConstant_AMIGO(10.0f, Tau);
	Filter(1.0f);
	Filter(1.0f);
	PrintInstanceState();

	Initialize();
	SetAlpha(2);
	SetOperatingFrequency(50);
	ComputeFilterTimeConstant_SIMCE(10.0f, Tau);
	Filter(1.0f);
	Filter(1.0f);
	PrintInstanceState();

	Initialize();
	SetAlpha(2);
	SetOperatingFrequency(50);
	ComputeFilterTimeConstant_Lambda(10.0f, Tau, 1);
	Filter(1.0f);
	Filter(1.0f);
	PrintInstanceState();

	Initialize();
	SetAlpha(2);
	SetOperatingFrequency(50);
	ComputeFilterTimeConstant_Lambda(10.0f, Tau, 2);
	Filter(1.0f);
	Filter(1.0f);
	PrintInstanceState();
	Initialize();
	std::cout << std::endl
			  << "SecondOrderFilter Unit Test End" << std::endl
			  << std::endl;
}
#endif // IN_VISUALSTUDIO
