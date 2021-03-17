#include "ProcessModel_FOTD.h"

ProcessModel_FOTD::ProcessModel_FOTD()
{
	ActiveTuningMethod = 0;
	K = 0.0f;
	T = 0.0f;
	L = 0.0f;
	Ta = 0.0f;
	La = 0.0f;
	Kp_Tuning = 0.0f;
	Ti_Tuning = 0.0f;
	Td_Tuning = 0.0f;
	Tau = 0.0f;
	Lambda_Tcl = 0.0f;
	SIMC_Tcl = 0.0f;
	SIMC_Ti = 0.0f;
	SIMC_Td = 0.0f;
	P_s = 0.0f;
#ifdef UNIT_TEST
	//UnitTest(); // Test passed
#endif // UNIT_TEST
}

ProcessModel_FOTD::~ProcessModel_FOTD()
{
}

void ProcessModel_FOTD::SetCharacteristics(float K_StaticGain, float T_ApparentTimeDelay, float L_ApparentTimeConstant)
{
	ActiveTuningMethod = 0;
	K = K_StaticGain;
	T = T_ApparentTimeDelay;
	L = L_ApparentTimeConstant;
	Tau = L / (L + T);
}

void ProcessModel_FOTD::TuneController_PI_AMIGO(PID_Controller &controller)
{
	ActiveTuningMethod = 1;
	Kp_Tuning = 0.15f / K;
	float LT = L * T;
	Kp_Tuning += (T / (K * L)) * (0.35f - LT / ((L + T) * (L + T)));
	Ti_Tuning = 0.35f * L;
	Ti_Tuning += 13.0f * LT * T / (T * T + 12.0f * LT + 7.0f * L * L);
	controller.SetTuningParameter(Kp_Tuning, Ti_Tuning);
}

void ProcessModel_FOTD::TuneController_PID_AMIGO(PID_Controller &controller)
{
	ActiveTuningMethod = 2;
	controller.InputFilter.ComputeFilterTimeConstant_AMIGO(L, Tau);
	ComputeAddedFilterDynamics(controller.InputFilter.GetFilterTimeConstant());
	Kp_Tuning = (0.2f + 0.45f * T / L) / K;
	Ti_Tuning = L * (0.4f * L + 0.8f * T) / (L + 0.1f * T);
	Td_Tuning = (0.5f * L * T) / (0.3f * L + T);
	controller.SetTuningParameter(Kp_Tuning, Ti_Tuning, Td_Tuning);
}

void ProcessModel_FOTD::TuneController_PI_Lambda(PID_Controller &controller, uint8_t Tcl_Mode)
{
	ActiveTuningMethod = 3;
	Set_Lambda_Tcl(Tcl_Mode);
	Kp_Tuning = T / (K * (L + Lambda_Tcl));
	Ti_Tuning = T;
	controller.SetTuningParameter(Kp_Tuning, Ti_Tuning);
}

void ProcessModel_FOTD::TuneController_PID_Lambda(PID_Controller &controller, uint8_t Tcl_Mode)
{
	ActiveTuningMethod = 4;
	controller.InputFilter.ComputeFilterTimeConstant_Lambda(L, Tau, Tcl_Mode);
	ComputeAddedFilterDynamics(controller.InputFilter.GetFilterTimeConstant());
	Set_Lambda_Tcl(Tcl_Mode);
	Kp_Tuning = (L / 2.0f + T) / (K * (L / 2.0f + Lambda_Tcl));
	Ti_Tuning = T + L / 2.0f;
	Td_Tuning = T * L / (L + 2.0f * T);
	controller.SetTuningParameter(Kp_Tuning, Ti_Tuning, Td_Tuning);
}

void ProcessModel_FOTD::TuneController_PI_SIMC(PID_Controller &controller)
{
	ActiveTuningMethod = 5;
	float Ti_1 = T + L / 3.0f;
	Kp_Tuning = Ti_1 / (K * (L + L));
	float Ti_2 = 8.0f * L;
	if (Ti_1 < Ti_2)
	{
		Ti_Tuning = Ti_1;
	}
	else
	{
		Ti_Tuning = Ti_2;
	}
	controller.SetTuningParameter(Kp_Tuning, Ti_Tuning);
}

void ProcessModel_FOTD::TuneController_PID_SIMC(PID_Controller &controller)
{
	ActiveTuningMethod = 6;
	controller.InputFilter.ComputeFilterTimeConstant_SIMCE(L, Tau);
	ComputeAddedFilterDynamics(controller.InputFilter.GetFilterTimeConstant());
	SIMC_Tcl = L / 2.0f;
	float Ti_2 = 4.0f * (SIMC_Tcl + L);
	if (T < Ti_2)
	{
		SIMC_Ti = T;
	}
	else
	{
		SIMC_Ti = Ti_2;
	}
	SIMC_Td = L / 3.0f;
	Kp_Tuning = (T * (3.0f * SIMC_Ti + L)) / (3.0f * K * SIMC_Ti * (SIMC_Tcl + L));
	Ti_Tuning = SIMC_Ti + SIMC_Td;
	Td_Tuning = SIMC_Td / (1.0f + SIMC_Td / SIMC_Ti);
	controller.SetTuningParameter(Kp_Tuning, Ti_Tuning, Td_Tuning);
}

float ProcessModel_FOTD::RunSimulation(PID_Controller &controller)
{
#ifdef SIMULATE_FOTD
	std::cout << "ProcessModel_FOTD Simulation: " << std::endl;
	std::cout << "P(s) = " << P_s << std::endl;
	controller.ControlProcess(P_s);
	float s = controller.GetOutputsignal();
	// Compute System Response
	P_s = K / (1 + s * T);
	P_s *= expf(-s * L);
	std::cout << "P(s) = " << P_s << std::endl;
#endif // SIMULATE_FOTD
	return P_s;
}

float ProcessModel_FOTD::GetK() const
{
	return K;
}

float ProcessModel_FOTD::GetT() const
{
	return T;
}

float ProcessModel_FOTD::GetL() const
{
	return L;
}

uint8_t ProcessModel_FOTD::GetActiveTuningMethod() const
{
	return ActiveTuningMethod;
}

void ProcessModel_FOTD::Set_Lambda_Tcl(uint8_t Tcl_Mode)
{
	switch (Tcl_Mode)
	{
	default:
		Lambda_Tcl = L;
		break;
	case 2:
		Lambda_Tcl = T;
		break;
	case 3:
		Lambda_Tcl = 3.0f * T;
		break;
	}
}

void ProcessModel_FOTD::ComputeAddedFilterDynamics(const float filterTimeConstant)
{
	float tau_8 = Tau * Tau * Tau * Tau * Tau * Tau * Tau * Tau;
	Ta = 1.1f * tau_8 * filterTimeConstant;
	T += Ta;
	La = (1.0f - 0.65f * tau_8) * filterTimeConstant;
	L += La;
}

void ProcessModel_FOTD::PrintInstanceState() const
{
#ifdef STATE_PRINT_FOTD
#ifdef IN_VISUALSTUDIO
	std::cout << "<>ProcessModel_FOTD:" << std::endl;
	std::cout << "ActiveTuningMethod: " << (int)ActiveTuningMethod << " [1=AMIGO PI, 2=AMIGO PID, 3=Lambda PI, 4=Lambda PID, 5=SIMC PI, 6=SIMC PID]" << std::endl;
	std::cout << "K: " << K << " T: " << T << " L: " << L << std::endl;
	std::cout << "Kp_Tuning: " << Kp_Tuning << " Ti_Tuning: " << Ti_Tuning << " Td_Tuning: " << Td_Tuning << std::endl;
	std::cout << "Lambda_Tcl: " << Lambda_Tcl << " SIMC_Tcl: " << SIMC_Tcl << " SIMC_Ti: " << SIMC_Ti << " SIMC_Td: " << SIMC_Td << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("<>ProcessModel_FOTD:");
	Serial.print("\nActiveTuningMethod: ");
	Serial.print(ActiveTuningMethod);
	Serial.print(" [1=AMIGO PI, 2=AMIGO PID, 3=Lambda PI, 4=Lambda PID, 5=SIMC PI, 6=SIMC PID]\n");
	Serial.print("K: ");
	Serial.print(K);
	Serial.print(" T: ");
	Serial.print(T);
	Serial.print(" L: ");
	Serial.print(L);
	Serial.print("\nKp_Tuning: ");
	Serial.print(Kp_Tuning);
	Serial.print(" Ti_Tuning: ");
	Serial.print(Ti_Tuning);
	Serial.print(" Td_Tuning: ");
	Serial.print(Td_Tuning);
	Serial.print("\nLambda_Tcl: ");
	Serial.print(Lambda_Tcl);
	Serial.print(" SIMC_Tcl: ");
	Serial.print(SIMC_Tcl);
	Serial.print(" SIMC_Ti: ");
	Serial.print(SIMC_Ti);
	Serial.print(" SIMC_Td: ");
	Serial.print(SIMC_Td);
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT_FOTD
}

#ifdef IN_VISUALSTUDIO
void ProcessModel_FOTD::UnitTest()
{
	std::cout << std::endl
			  << "ProcessModel_FOTD Unit Test:" << std::endl
			  << std::endl;
	float k = 1.47f;
	float t = 55.0f;
	float l = 10.0f;
	SetCharacteristics(k, t, l);
	PID_Controller PID;
	TuneController_PI_AMIGO(PID);
	TuneController_PID_AMIGO(PID);
	TuneController_PI_Lambda(PID, 1);
	TuneController_PI_Lambda(PID, 2);
	TuneController_PI_Lambda(PID, 3);
	TuneController_PI_SIMC(PID);
	TuneController_PID_SIMC(PID);
	std::cout << std::endl
			  << "ProcessModel_FOTD Unit Test End" << std::endl
			  << std::endl;
}
#endif // IN_VISUALSTUDIO
