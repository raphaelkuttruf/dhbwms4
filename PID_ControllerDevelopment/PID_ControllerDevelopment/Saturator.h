#pragma once

#include "Defines.h"

class Saturator
{
	// Variables
public:
protected:
private:
	// Funktions
public:
	Saturator();
	~Saturator();
	static void Min(float &Signal, const float Limit);							// Saturate with lower limit
	static void Max(float &Signal, const float Limit);							// Saturate with upper limit
	static void MaxMin(float &Signal, const float Min, const float Max);		// Saturate range, first Max
	static void MinMax(float &Signal, const float Min, const float Max);		// Saturate range, first Min
	static float MinC(const float Signal, const float Limit);					// return copy of signal saturated with lower limit
	static float MaxC(const float Signal, const float Limit);					// return copy of signal saturated with upper limit
	static float MaxMinC(const float Signal, const float Min, const float Max); // return copy of signal saturated range, first Max
	static float MinMaxC(const float Signal, const float Min, const float Max); // return copy of signal saturated range, first Min

protected:
private:
};
