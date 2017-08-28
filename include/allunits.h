#pragma once
#include "unitdata.h"
#include "activeunit.h"
#include "expansions.h"
#include <vector>
#include <iterator>
using namespace std;

class AllUnits {
	public:
		bool canBuild(UnitName) const;
		void spawn(UnitName, ActionName actionName = ActionName::Idle, int timer = -1);
		void build(UnitName);
		int getMineralMinerCount() const;
		int getGasMinerCount() const;
		ActiveUnit update();
		void clear();

	private:
		bool hasUnit(UnitName) const;
		bool hasAvailableUnit(UnitName) const;
		bool hasUnit(UnitName, bool (ActiveUnit::*)()) const;
		bool isNonNullUnit(UnitName) const;
		int getBuildTime(UnitStatBlock);
		vector<ActiveUnit>::iterator findAvailableUnit(UnitName);
		int getMineralRate(char race) const;
		int getGasRate() const;
		int countUnit(bool (ActiveUnit::*)()) const;
		void updateUnitAction(ActiveUnit&);

		vector<ActiveUnit>::iterator unitListIterator;
		vector<ActiveUnit> unitList;
		UnitData unitData;
		Expansions expansion;
};
