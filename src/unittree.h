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
		Unit &findUnit(string unitName);
		string getWorkerName() { return vUnitList.front().getName(); }

	private:
		void addUnit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, string prereq, string buildsFrom);
		void init();

		vector<Unit> vUnitList;
};
