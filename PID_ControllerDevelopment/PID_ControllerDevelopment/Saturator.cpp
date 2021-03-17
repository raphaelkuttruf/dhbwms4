#include "Saturator.h"

Saturator::Saturator()
{
}

Saturator::~Saturator()
{
}

void Saturator::Min(float &Signal, const float Limit)
{
	if (Signal < Limit)
	{
		Signal = Limit;
	}
}

void Saturator::Max(float &Signal, const float Limit)
{
	if (Signal > Limit)
	{
		Signal = Limit;
	}
}

void Saturator::MinMax(float &Signal, const float Min, const float Max)
{
	if (Signal < Min)
	{
		Signal = Min;
		return;
	}
	if (Signal > Max)
	{
		Signal = Max;
	}
}

void Saturator::MaxMin(float &Signal, const float Min, const float Max)
{
	if (Signal > Max)
	{
		Signal = Max;
		return;
	}
	if (Signal < Min)
	{
		Signal = Min;
	}
}

float Saturator::MinC(const float Signal, const float Limit)
{
	if (Signal < Limit)
	{
		return Limit;
	}
	return Signal;
}

float Saturator::MaxC(const float Signal, const float Limit)
{
	if (Signal > Limit)
	{
		return Limit;
	}
	return Signal;
}

float Saturator::MaxMinC(const float Signal, const float Min, const float Max)
{
	if (Signal > Max)
	{
		return Max;
	}
	if (Signal < Min)
	{
		return Min;
	}
	return Signal;
}

float Saturator::MinMaxC(const float Signal, const float Min, const float Max)
{
	if (Signal < Min)
	{
		return Min;
	}
	if (Signal > Max)
	{
		return Max;
	}
	return Signal;
}
