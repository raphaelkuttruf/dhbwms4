#pragma once

#include "Defines.h"
#include <stdint.h>
#include "ControlSample.h"
#include "DataSample.h"

// An ASCII Table might be helpful
// https://www.torsten-horn.de/techdocs/ascii.htm

class Serial_SimulinkInterface
{
	// Variables
public:
protected:
	const uint8_t SendDataByteSize = 32;
	const uint8_t SendHeaderByteSize = 3;
	const uint8_t SendHeader[3] = {'<', 'D', '>'};
	uint8_t SendDataIndex;
	uint8_t SendData[256] = {0};

	const uint8_t RecieveDataByteSize = 32;
	const uint8_t RecieveHeaderByteSize = 3;
	const uint8_t RecieveHeader[3] = {'<', 'C', '>'};
	uint8_t RecievedDataIndex;
	uint8_t RecievedData[256] = {0};

	const uint8_t Terminator = '\n';
	uint8_t NewDataRecieved;
	uint8_t NewDataRecievedAndMirrored;

private:
	// Funktions
public:
	Serial_SimulinkInterface();
	~Serial_SimulinkInterface();
	void SerializeDataSample(const DataSample &dataSample);
	void DeserializeControlSample(ControlSample &controlSample);
	void RecieveSerial();
	void SendSerial();
	void MirrorRecievedSerial();
	void PrintInstanceState() const;
#ifdef IN_VISUALSTUDIO
	void UnitTest();
#endif // IN_VISUALSTUDIO

protected:
	void Serialize(const uint8_t value);
	void Serialize(const uint16_t value);
	void Serialize(const uint32_t value);
	//void Serialize(const int8_t value);
	//void Serialize(const int16_t value);
	//void Serialize(const int32_t value);
	uint8_t Deserialize8U();
	uint16_t Deserialize16U();
	uint32_t Deserialize32U();
	//int8_t Deserialize8();
	//int16_t Deserialize16();
	//int32_t Deserialize32();

private:
};
