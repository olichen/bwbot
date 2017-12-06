#pragma once
#include "unitname.h"
#include <string>

struct UnitStatBlock {
	char race;
	std::string name;
	int mineralCost;
	int gasCost;
	int buildTime;
	int supplyCost;
	int supplyProvided;
	UnitName prerequisite[2];
	UnitName buildsFrom;
	bool requireAddon;
	bool morph;
	bool expansion;
	bool gas;
	bool worker;
	char type; // [u]nit, [b]uilding, [a]ddon, [r]esearch, [n]umerical upgrade
	
	bool reqAddon() { return requireAddon; }
	bool isWarp() { return type=='b' && race=='p'; }
	bool isMorph() { return morph; }
	bool isExpansion() { return expansion; }
	bool isGas() { return gas; }
	bool isWorker() { return worker; }

	bool isUnit() { return type=='u'; }
	bool isBuilding() { return type=='b'; }
	bool isAddon() { return type=='a'; }
	bool isResearch() { return type=='r'; }
	bool isUpgrade() { return type=='n'; }

	int getBuildTime() {
		if(isMorph())
			return buildTime + 18;
		if(isWarp())
			return buildTime + 70;
		return buildTime;
	}
};
