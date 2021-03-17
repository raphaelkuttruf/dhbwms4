#include "LevelProcess.h"

LevelProcess::LevelProcess()
{
	UpdateCycleCounter = 0;
	IO.P9.Set(1);	  // Pump Direction, connected to PWM Shield
	IO.P10.Set(0);	  // Pump Direction, connected to PWM Shield
	IO.P3.PMW_Bit(0); // Pump PWM 0V
	WaterOverflow = 0;
	ActuatorOverwriteEnable = 0;
	ActuatorSpeedOverwrite_mV = 0.0f;
}

LevelProcess::~LevelProcess()
{
}

void LevelProcess::SetOperatingFrequency(uint8_t frequency)
{
	Timer.SetCycleFrequency(frequency);
	PID.SetOperatingFrequency(frequency/5); // TEST
}

void LevelProcess::Run()
{
	ReadControlSample();
	// Conrol Routine
#ifdef FORCE_CYCLETIME
	Timer.ForceCycleTime(); // Program will wait here util the wanted cycle time is reached
#endif						// FORCE_CYCLETIME
	IO.MeasureA0(); // Read Water Level Sensor
	PID.ControlProcess(IO.ADC_A0.Get_mVolt()); // Compute Controller Response
	ProtectFromOverflow(); // Safety First
	if (!WaterOverflow)
	{
		if (ActuatorOverwriteEnable)
		{
			IO.P3.PWM_mV(ActuatorSpeedOverwrite_mV); // Overwritevalue -> PWM -> Pump Driver -> Pump
		}
		else
		{
			IO.P3.PWM_mV(PID.GetOutputsignalSaturated()); // PID -> PWM -> Pump Driver -> Pump
		}
	}
#ifdef STATE_PRINT_IO_RELEVANT
	IO.P9.PrintInstanceState();
	IO.P10.PrintInstanceState();
	IO.ADC_A0.PrintInstanceState();
	IO.P3.PrintInstanceState();
#endif // STATE_PRINT_IO_RELEVANT
#ifdef STATE_PRINT_IO
	IO.PrintInstanceState();
#endif // STATE_PRINT_IO
	UpdateCycleCounter++;
	// End Conrol Routine
	WriteDataSample();
}

void LevelProcess::ProtectFromOverflow()
{
	if (IO.ADC_A0.Get_mVolt() > WaterLevel_Max_mV)
	{
		WaterOverflow = 1;
		IO.P3.PMW_Bit(0);
#ifdef IN_VISUALSTUDIO
		std::cout << "<!>Overflow!" << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
		Serial.write("<!>Overflow!\n");
#endif // IN_ARDUINO_IDE
	}
	else
	{
		WaterOverflow = 0;
	}
}

void LevelProcess::ReadControlSample()
{
#ifdef OVERWRITE_CONTROLSAMPLE
	Control.OverwriteWithTestData();
#endif																									// OVERWRITE_CONTROLSAMPLE
	FOTD.SetCharacteristics(Control.FOTD_K / 100.0f, Control.FOTD_T / 100.0f, Control.FOTD_L / 100.0f); // remove gain from simulink
	PID.InputFilter.SetAlpha(Control.FilterAlpha);
	PID.SetSetpoint(Control.Setpoint_mm / WaterLevel_mm_per_mV);
	PID.SetBeta(Control.PID_Beta);
	PID.SetGamma(Control.PID_Gamma);
	PID.SetAntiWindup(Control.AntiWindupEnable);
	ActuatorOverwriteEnable = Control.ActuatorOverwriteEnable;
	ActuatorSpeedOverwrite_mV = Control.ActuatorSpeedOverwrite_mV;

	switch (Control.SelectTuningMethod)
	{
	case 1:
		FOTD.TuneController_PI_AMIGO(PID);
		break;
	case 2:
		FOTD.TuneController_PID_AMIGO(PID);
		break;
	case 3:
		FOTD.TuneController_PI_Lambda(PID, Control.Lambda_Tcl_Mode);
		break;
	case 4:
		FOTD.TuneController_PID_Lambda(PID, Control.Lambda_Tcl_Mode);
		break;
	case 5:
		FOTD.TuneController_PI_SIMC(PID);
		break;
	case 6:
		FOTD.TuneController_PID_SIMC(PID);
		break;
	default:
		break;
	}
	FOTD.PrintInstanceState();
	Control.PrintInstanceState();
}

void LevelProcess::WriteDataSample()
{
	Data.SampleNr++;
	Data.SystemState_mV = (uint16_t)IO.ADC_A0.Get_mVolt();
	Data.SystemState_mm = (uint16_t)(IO.ADC_A0.Get_mVolt() * WaterLevel_mm_per_mV);
	Data.SystemStatePostFilter_mV = 32768 + (uint16_t)(PID.InputFilter.GetFilteredSignal());
	Data.SystemStatePostFilter_mm = 32768 + (uint16_t)(PID.InputFilter.GetFilteredSignal() * WaterLevel_mm_per_mV);
	Data.ControllerSetpoint_mm = (uint16_t)(PID.GetSetpoint() * WaterLevel_mm_per_mV);
	Data.ConrollerOutput_mV = (int16_t)PID.GetOutputsignalSaturated();
	Data.ActuatorOutput_mV = (uint16_t)(IO.P3.GetPMW_mV());
	Data.ActuatorOutput_Bit = IO.P3.GetPMW_Bit();
	Data.OverflowDetected = WaterOverflow;
	Data.PID_P = 32768 + (uint16_t)Saturator::MaxMinC(PID.GetOutputsignal_P(), -32768.0f, 32767.0);
	Data.PID_I = 32768 + (uint16_t)Saturator::MaxMinC(PID.GetOutputsignal_I(), -32768.0f, 32767.0);
	Data.PID_D = 32768 + (uint16_t)Saturator::MaxMinC(PID.GetOutputsignal_D(), -32768.0f, 32767.0);
#ifdef OVERWRITE_DATASAMPLE
	Data.OverwriteWithTestData();
#endif // OVERWRITE_DATASAMPLE
	Data.PrintInstanceState();
}
