#pragma once
#include "unitname.h"
#include <string>
using namespace std;

struct UnitData {
	char race;
	string name;
	string shortNames[2];
	int mineralCost;
	int gasCost;
	int supplyCost;
	int supplyProvided;
	int buildTime;
	UnitName prerequisite[2];
	UnitName buildsFrom;
	bool addon;
	bool requireAddon;
	bool morph;
	bool warp;
	bool expansion;
	bool gas;
	bool worker;
};
