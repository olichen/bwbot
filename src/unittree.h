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

		void addUnit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, string prereq, string buildsFrom);
		void init();

	private:
		vector<Unit> vUnitList;
};
