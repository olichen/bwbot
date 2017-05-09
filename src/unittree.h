// unittree.h
#pragma once
#include "unit.h"
#include <vector>
#include <string>
using namespace std;

class UnitTree
{
	public:
		UnitTree();
		~UnitTree();

		void loadRace(char race);
		Unit *findUnit(string unitName);
		string getWorkerName() const { return vUnitList.front().getName(); }
		string getExpansionName() const { return vUnitList[1].getName(); }
		string getGasName() const { return vUnitList[2].getName(); }

	private:
		void addUnit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, string prereq, string buildsFrom, bool isAddon = false);
		void init();

		vector<Unit> vUnitList;
};
