#pragma once
#include "unitstatblock.h"
#include "actionname.h"

struct ActiveUnit {
	UnitName unit, targetUnit;
	ActionName action;
	int timer;

	ActiveUnit(UnitName, ActionName, int);
	ActiveUnit(int, int, int);
};

ActiveUnit::ActiveUnit(int unit, int action, int timer)
	: unit((UnitName)unit), action((ActionName)action), timer(timer)
{
	//
}
