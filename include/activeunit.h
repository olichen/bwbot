#pragma once
#include "unitstatblock.h"
#include "actionname.h"

struct ActiveUnit {
	UnitName unit;
	ActionName action;
	int timer;

	ActiveUnit(int, int, int);
	bool isAvailable();
	bool exists() { return true; }
	bool isIdle() { return action == ActionName::Idle; }
	bool isMiningMinerals() { return action == ActionName::Gather_Minerals; }
	bool isMiningGas() { return action == ActionName::Gather_Gas; }
};
