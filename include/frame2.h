#pragma once
#include "unitname.h"
#include "actionname.h"

struct Frame
{
	int frame, minerals, gas, supply, supplymax, miners, gasminers;
	UnitName unit;
	ActionName action;
};
