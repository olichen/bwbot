#pragma once
#include "unitstatblock.h"
#include "actionname.h"

struct ActiveUnit {
	UnitName unit;
	ActionName action;
	short int timer;

	ActiveUnit(int, int, int);
	void setTravelling(int time = 64);

	bool isAvailable();
	bool exists() { return true; }
	bool isBuilding() { return action == ActionName::Build; }
	bool isIdle() { return action == ActionName::Idle; }
	bool isMiningMinerals() { return action == ActionName::Gather_Minerals; }
	bool isMiningGas() { return action == ActionName::Gather_Gas; }
};
