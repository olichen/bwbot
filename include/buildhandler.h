#pragma once
#include "unitdata.h"
#include "activeunit.h"
#include "expansions.h"
#include "larvahandler.h"
#include <vector>
#include <iterator>
using namespace std;

class BuildHandler {
	public:
		bool canBuild(UnitName) const;
		void spawn(UnitName, ActionName actionName = ActionName::Spawning, int timer = 0);
		void build(UnitName);
		int getMineralMinerCount() const;
		int getGasMinerCount() const;
		ActiveUnit update();
		void onGas();
		void offGas();
		void clear();

	private:
		bool hasUnit(UnitName) const;
		bool hasAvailableUnit(UnitName) const;
		bool hasUnit(UnitName, bool (ActiveUnit::*)()) const;
		void findAndUseBuilder(UnitStatBlock);
		void removeMorphingUnit(UnitName);
		vector<ActiveUnit>::iterator findAvailableUnit(UnitName);
		vector<ActiveUnit>::iterator findIdleUnit(UnitName);
		vector<ActiveUnit>::iterator findMiner(UnitName);
		vector<ActiveUnit>::iterator findMineralMiner();
		vector<ActiveUnit>::iterator findGasMiner();
		vector<ActiveUnit>::iterator findUnitByAction(bool (ActiveUnit::*)());
		int getMineralRate(UnitName) const;
		int getMineralRate(char race) const;
		int countUnit(bool (ActiveUnit::*)()) const;
		void updateLarva();
		void updateUnitAction(ActiveUnit&);
		void updateWorkerAction(ActiveUnit&);

		vector<ActiveUnit>::iterator unitListIterator;
		vector<ActiveUnit> unitList;
		UnitData unitData;
		Expansions expansion;
		LarvaHandler larvaHandler;
};
