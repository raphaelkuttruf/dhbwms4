#pragma once

#include "Defines.h"
#include <stdint.h>

class DigitalPin
{
	// Variables
public:
protected:
	uint8_t PinNr;
	uint8_t PinIn;
	uint8_t PinOut;

private:
	// Funktions
public:
	DigitalPin(const uint8_t number);
	~DigitalPin();
	void Set(const uint8_t high_low);
	uint8_t Get();
	void PrintInstanceState() const;

protected:
private:
};
