#pragma once
#include "unit.h"
#include "unitname.h"
#include "unitdata.h"
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
		string getExpansionName() const { return vUnitList.at(1).getName(); }
		string getGasName() const { return vUnitList.at(2).getName(); }
		int getId(string unit) const;
		const UnitData unitList[UnitName::NUMBER_OF_UNITS];

	private:
		void clear() { vUnitList.clear(); }
		void addUnit(int id, string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided,
			string prereq, string buildsFrom, string prereq2 = "", bool isAddon = false, bool reqAddon = false, bool morph = false);

		vector<Unit> vUnitList;
};
