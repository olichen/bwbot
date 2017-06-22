#pragma once
#include <string>

struct Frame
{
	int frame, minerals, gas, supply, supplymax, miners, gasminers, time;
	std::string action, unit;
};
