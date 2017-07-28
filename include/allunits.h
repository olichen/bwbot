#pragma once
#include "unitdata.h"
#include "activeunit.h"
#include "expansions.h"
#include <vector>
using namespace std;

class AllUnits {
	public:
		bool canBuild(UnitName) const;
		void spawn(UnitName, ActionName = ActionName::Idle, int timer = -1);
		void build(UnitName);
		int getMineralMinerCount() const;
		int getGasMinerCount() const;
		ActionName update();
		void clear();

	private:
		bool hasUnit(UnitName) const;
		bool hasIdleUnit(UnitName) const;
		bool hasUnit(UnitName, bool (ActiveUnit::*)()) const;
		bool isNonNullUnit(UnitName) const;
		int findIdleUnit(UnitName) const;
		int getMineralRate(char race) const;
		int getGasRate() const;
		int countUnit(bool (ActiveUnit::*)()) const;

		vector<ActiveUnit> unitList;
		UnitData unitdata;
		Expansions expansion;
};
