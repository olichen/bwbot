#pragma once
#include "unitstatblock.h"
#include "actionname.h"

struct ActiveUnit {
	UnitName unit;
	ActionName action;
	short int timer, count;

	ActiveUnit(int, int, int, int count = 0);
	bool isAvailable();
	bool exists() { return true; }
	bool isIdle() { return action == ActionName::Idle; }
	bool isMiningMinerals() { return action == ActionName::Gather_Minerals; }
	bool isMiningGas() { return action == ActionName::Gather_Gas; }
};
