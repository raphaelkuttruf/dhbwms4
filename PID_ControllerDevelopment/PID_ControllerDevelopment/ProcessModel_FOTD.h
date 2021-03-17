#pragma once

#include "Defines.h"
#include <stdint.h>
#include "ControlSample.h"
#include "PID_Controller.h"

// https://de.wikipedia.org/wiki/PT1-Glied

class ProcessModel_FOTD
{
	// Variables
public:
protected:
	uint8_t ActiveTuningMethod;
	// DataSample Characterization_Start;
	// DataSample Characterization_63;
	// DataSample Characterization_MaxIncrease;
	// DataSample Characterization_FinalState;
	float K;		 // Static Gain
	float T;		 // Apparent Time Delay
	float L;		 // Apparent Time Constant
	float Ta;		 // Added Filter Dynamics to T
	float La;		 // Added Filter Dynamics to L
	float Kp_Tuning; // Tuning Parameter Kp for PID Controller
	float Ti_Tuning; // Tuning Parameter Ti for PID Controller
	float Td_Tuning; // Tuning Parameter Td for PID Controller
	float Tau;		 // normalized time delay(L / (L + T))
	float Lambda_Tcl;
	float SIMC_Tcl;
	float SIMC_Ti; // Ti'
	float SIMC_Td; // Td'
	float P_s;	   // Simulated System state

private:
	// Funktions
public:
	ProcessModel_FOTD();
	~ProcessModel_FOTD();
	/*
	* @param Static Gain K
	* @param Apparent Time Delay T
	* @param Apparent Time Constant L
	*/
	void SetCharacteristics(float K, float T, float L);
	void TuneController_PI_AMIGO(PID_Controller &controller);
	void TuneController_PID_AMIGO(PID_Controller &controller);
	/*
	* Replaces Tcl with Selected Variable via Tcl Mode, default is L
	* @param The Controller used to Control this System
	* @param Tcl Mode [0,1,2] => [L,T,3T]
	*/
	void TuneController_PI_Lambda(PID_Controller &controller, const uint8_t Tcl_Mode);
	/*
	* Replaces Tcl with Selected Variable via Tcl Mode, default is L
	* @param The Controller used to Control this System
	* @param Tcl Mode [1,2,3] => [L,T,3T]
	*/
	void TuneController_PID_Lambda(PID_Controller &controller, const uint8_t Tcl_Mode);
	void TuneController_PI_SIMC(PID_Controller &controller);
	void TuneController_PID_SIMC(PID_Controller &controller);
	float RunSimulation(PID_Controller &controller);
	float GetK() const;
	float GetT() const;
	float GetL() const;
	uint8_t GetActiveTuningMethod() const;
	void PrintInstanceState() const;

protected:
	/*
	*@param Tcl Mode[1, 2, 3] = > [L, T, 3T]
	*/
	void Set_Lambda_Tcl(uint8_t Tcl_Mode);
	void ComputeAddedFilterDynamics(const float filterTimeConstant);
#ifdef IN_VISUALSTUDIO
	void UnitTest();
#endif // IN_VISUALSTUDIO
private:
};
