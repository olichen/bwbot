#pragma once
#include "unitdata.h"
#include "activeunit.h"
#include "expansionhandler.h"
#include "larvahandler.h"
#include <vector>
#include <iterator>
using namespace std;

class BuildHandler {
	public:
		BuildHandler();

		bool canBuild(UnitName) const;
		void build(UnitName);
		void spawn(UnitName, ActionName actionName = ActionName::Spawning, int timer = 0);
		int getMineralMinerCount() const;
		int getGasMinerCount() const;
		void onGas();
		void offGas();
		ActiveUnit update();
		void clear();

	private:
		bool hasUnit(UnitName) const;
		bool hasAvailableUnit(UnitName) const;
		bool hasUnit(UnitName, bool (ActiveUnit::*)()) const;
		void useBuilder(UnitStatBlock);
		void removeMorphingUnit(UnitName);
		vector<ActiveUnit>::iterator findAvailableUnit(UnitName);
		vector<ActiveUnit>::iterator findIdleUnit(UnitName);
		vector<ActiveUnit>::iterator findAvailableMiner(UnitName);
		vector<ActiveUnit>::iterator findMineralMiner();
		vector<ActiveUnit>::iterator findGasMiner();
		vector<ActiveUnit>::iterator findMinerByAction(bool (ActiveUnit::*)(), UnitName unitName = UnitName::UNIT_NULL);
		int getMineralRate(UnitName) const;
		int getMineralRate(char race) const;
		int countUnitByAction(bool (ActiveUnit::*)()) const;
		void updateLarva();
		void updateUnitAction(ActiveUnit&);
		void updateWorkerAction(ActiveUnit&);

		vector<ActiveUnit>::iterator unitListIterator;
		vector<ActiveUnit> unitList;
		UnitData unitData;
		ExpansionHandler expansionHandler;
		LarvaHandler larvaHandler;
};
