#include "Serial_SimulinkInterface.h"

Serial_SimulinkInterface::Serial_SimulinkInterface()
{
	SendDataIndex = 0;
	RecievedDataIndex = 0;
	NewDataRecieved = 0;
	NewDataRecievedAndMirrored = 0;
#ifdef UNIT_TEST
	//UnitTest(); // OK
#endif // UNIT_TEST
}

Serial_SimulinkInterface::~Serial_SimulinkInterface()
{
}

void Serial_SimulinkInterface::RecieveSerial()
{
	RecievedDataIndex = 0; // Start writing valid Recieved Data from Index 0
	uint8_t HeaderCompareIndex = 0;
#ifdef IN_ARDUINO_IDE
	while (Serial.available())
	{
		uint8_t value = Serial.read();
		if (HeaderCompareIndex == RecieveHeaderByteSize)
		{
			// Read Data after Headers matched
			RecievedData[RecievedDataIndex] = value;
			RecievedDataIndex++;
		}
		else
		{
			if (value == RecieveHeader[HeaderCompareIndex])
			{
				// Value is part of The Header, compare next recieved value to next Header value
				HeaderCompareIndex++;
			}
			else
			{
				// Invalid Header, start from scratch
				HeaderCompareIndex = 0;
			}
			continue;
		}
		if (value == Terminator)
		{
			NewDataRecieved = 1;
			NewDataRecievedAndMirrored = 0;
			//Serial.flush(); // Flush Hardware Serial Buffer, not neccesary
		}
	}
#endif // IN_ARDUINO_IDE
}

void Serial_SimulinkInterface::SendSerial()
{
#ifdef IN_ARDUINO_IDE
	Serial.write('\n'); // Just to make some space
#endif					// IN_ARDUINO_IDE
	for (uint8_t i = 0; i < SendHeaderByteSize; i++)
	{
#ifdef IN_ARDUINO_IDE
		Serial.write(SendHeader[i]);
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
		std::cout << SendHeader[i] << " ";
#endif // IN_VISUALSTUDIO
	}
	for (uint8_t i = 0; i < SendDataByteSize; i++)
	{
#ifdef IN_ARDUINO_IDE
		Serial.write(SendData[i]);
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
		std::cout << (int)SendData[i] << " ";
#endif // IN_VISUALSTUDIO
	}
#ifdef IN_ARDUINO_IDE
	Serial.write(Terminator);
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
	std::cout << std::endl;
#endif // IN_VISUALSTUDIO
}

void Serial_SimulinkInterface::MirrorRecievedSerial()
{
	if (NewDataRecieved)
	{
		NewDataRecieved = 0;
		NewDataRecievedAndMirrored = 1;
#ifdef IN_ARDUINO_IDE
		Serial.print("\nMirror: ");
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
		std::cout << "Mirror: " << std::endl;
#endif				   // IN_VISUALSTUDIO
		uint8_t i = 0; // read Index
		uint8_t value = 0;
		while (value != Terminator)
		{
			value = RecievedData[i];
#ifdef IN_ARDUINO_IDE
			Serial.write(value);
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
			std::cout << (int)value << " ";
#endif // IN_VISUALSTUDIO
			i++;
		}
#ifdef IN_ARDUINO_IDE
		Serial.write(Terminator);
#endif // IN_ARDUINO_IDE
#ifdef IN_VISUALSTUDIO
		std::cout << std::endl;
#endif // IN_VISUALSTUDIO
	}
}

void Serial_SimulinkInterface::DeserializeControlSample(ControlSample &controlSample)
{
	if (NewDataRecieved | NewDataRecievedAndMirrored)
	{
		NewDataRecieved = 0;
		NewDataRecievedAndMirrored = 0;
		RecievedDataIndex = 255; // Set Index 1 Byte before the First Data Byte
		controlSample.SampleNr++;
		controlSample.Setpoint_mm = Deserialize16U();
		controlSample.FOTD_K = Deserialize16U();
		controlSample.FOTD_T = Deserialize16U();
		controlSample.FOTD_L = Deserialize16U();
		controlSample.SelectTuningMethod = Deserialize8U();
		controlSample.Lambda_Tcl_Mode = Deserialize8U();
		controlSample.FilterAlpha = Deserialize8U();
		controlSample.PID_Beta = Deserialize8U();
		controlSample.PID_Gamma = Deserialize8U();
		controlSample.AntiWindupEnable = Deserialize8U();
		controlSample.ActuatorOverwriteEnable = Deserialize8U();
		controlSample.ActuatorSpeedOverwrite_mV = Deserialize16U();
	}
	controlSample.PrintInstanceState();
}

void Serial_SimulinkInterface::SerializeDataSample(const DataSample &dataSample)
{
	SendDataIndex = 0;
	Serialize(dataSample.SampleNr);
	Serialize(dataSample.SystemState_mV);
	Serialize(dataSample.SystemState_mm);
	Serialize(dataSample.SystemStatePostFilter_mV);
	Serialize(dataSample.SystemStatePostFilter_mm);
	Serialize(dataSample.ControllerSetpoint_mm);
	Serialize(dataSample.ConrollerOutput_mV);
	Serialize(dataSample.ActuatorOutput_mV);
	Serialize(dataSample.ActuatorOutput_Bit);
	Serialize(dataSample.OverflowDetected);
	Serialize(dataSample.PID_P);
	Serialize(dataSample.PID_I);
	Serialize(dataSample.PID_D);
	Serialize((uint8_t)'E');
	Serialize((uint8_t)'n');
	Serialize((uint8_t)'d');
}

void Serial_SimulinkInterface::Serialize(const uint8_t value)
{
	SendData[SendDataIndex] = value;
	SendDataIndex++;
}

void Serial_SimulinkInterface::Serialize(const uint16_t value)
{
	Serialize((uint8_t)value);
	Serialize((uint8_t)(value >> 8));
}

void Serial_SimulinkInterface::Serialize(const uint32_t value)
{
	Serialize((uint16_t)value);
	Serialize((uint16_t)(value >> 16));
}
/*
void Serial_SimulinkInterface::Serialize(const int8_t value)
{
	SendData[SendDataIndex] = value;
	SendDataIndex++;
}

void Serial_SimulinkInterface::Serialize(const int16_t value)
{
	Serialize((int8_t)value);
	Serialize((int8_t)(value >> 8));
}

void Serial_SimulinkInterface::Serialize(const int32_t value)
{
	Serialize((int16_t)value);
	Serialize((int16_t)(value >> 16));
}
*/

uint8_t Serial_SimulinkInterface::Deserialize8U()
{
	RecievedDataIndex++;
	return (int8_t)RecievedData[RecievedDataIndex];
}

uint16_t Serial_SimulinkInterface::Deserialize16U()
{
	uint16_t value = Deserialize8U();
	value |= ((uint16_t)Deserialize8U() << 8);
	return value;
}

uint32_t Serial_SimulinkInterface::Deserialize32U()
{
	uint32_t value = Deserialize16U();
	value |= ((uint32_t)Deserialize16U() << 16);
	return value;
}

/*
int8_t Serial_SimulinkInterface::Deserialize8()
{
	RecievedDataIndex++;
	return RecievedData[RecievedDataIndex] | 0x7F;
}

int16_t Serial_SimulinkInterface::Deserialize16()
{
	int16_t value = Deserialize8();
	value |= (Deserialize8() << 8);
	return value;
}

int32_t Serial_SimulinkInterface::Deserialize32()
{
	int32_t value = Deserialize16();
	value |= (Deserialize16() << 16);
	return value;
}
*/

void Serial_SimulinkInterface::PrintInstanceState() const
{
#ifdef STATE_PRINT_SERIAL_BUFFERS
#ifdef IN_VISUALSTUDIO
	std::cout << "<>Serial_SimulinkInterface:" << std::endl;
	uint8_t i = 0;
	std::cout << "RecievedData[dec]:" << std::endl; // decimal interpretation
	for (uint16_t i = 0; i < 255; i++)
	{
		std::cout << (int)RecievedData[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "SendData[dec]:" << std::endl;
	for (uint16_t i = 0; i < 255; i++)
	{
		std::cout << (int)SendData[i] << " ";
	}
	std::cout << std::endl;
#endif // IN_VISUALSTUDIO
#ifdef IN_ARDUINO_IDE
	Serial.print("<>Serial_SimulinkInterface:\n");
	;
	uint8_t i = 0;
	Serial.print("RecievedData[dec]:\n"); // decimal interpretation
	for (uint16_t i = 0; i < 255; i++)
	{
		Serial.print((int)RecievedData[i]);
		Serial.write(' ');
	}
	Serial.print("\nSendData[dec]:\n");
	for (uint16_t i = 0; i < 255; i++)
	{
		Serial.print((int)SendData[i]);
		Serial.write(' ');
	}
	Serial.write('\n');
#endif // IN_ARDUINO_IDE
#endif // STATE_PRINT_SERIAL_BUFFERS
}

#ifdef IN_VISUALSTUDIO
void Serial_SimulinkInterface::UnitTest()
{
	std::cout << "Serial_SimulinkInterface Unit Test:" << std::endl;
	RecievedData[0] = 255;
	RecievedData[1] = 255;
	RecievedData[2] = 255;
	RecievedData[3] = 255;
	// Read Test Unsigned
	RecievedDataIndex = 255;
	if (255 != Deserialize8U())
	{
		std::cout << "Fehler Deserialize8U" << std::endl;
	}
	RecievedDataIndex = 255;
	if (65535 != Deserialize16U())
	{
		std::cout << "Fehler Deserialize16U" << std::endl;
	}
	RecievedDataIndex = 255;
	if (4294967295 != Deserialize32U())
	{
		std::cout << "Fehler Deserialize32U" << std::endl;
	}
	std::cout << std::endl
			  << "Serial_SimulinkInterface Unit Test End" << std::endl
			  << std::endl;

	// Read Test Signed, This is a bigger Issue..
	//if (-128 != Deserialize8())
	//{
	//	std::cout << "Fehler Deserialize8" << std::endl;
	//}
	//RecievedDataIndex = 255;
	//if (-32768 != Deserialize16())
	//{
	//	std::cout << "Fehler Deserialize16" << std::endl;
	//}

	//RecievedDataIndex = 255;
	//if (2.147483648 != Deserialize32())
	//{
	//	std::cout << "Fehler Deserialize32" << std::endl;
	//}
}
#endif // IN_VISUALSTUDIO
