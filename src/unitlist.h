// unitlist.h
#pragma once
#include "currentunit.h"
#include "unit.h"
#include "action.h"
#include <string>
#include <vector>
using namespace std;

class UnitList
{
	public:
		UnitList();

		void init(string workerName, string gasName, string expansionName);
		void addUnit(Unit &unit, Action nextAction = Action(), Action idleAction = Action());
		void update(vector<Action> &actionList);
		bool tryToBuild(Unit &unit);
		void buildUnit(Unit &unit);
		void spawnUnit(Unit &unit);
		void addGasWorker();
		void removeGasWorker();
		void scout();

		void setMineralRate(int mineralRate);
		void clear() { vUnitList.clear(); };

		int minerCount() const;
		int gasMinerCount() const;

		void printUnitStatus(bool hideMining = true, bool hideIdle = true) const;
		void printUnits() const;
		void printBuilding() const;

	private:
		bool mergeArchon(Unit &unit);
		CurrentUnit *findWorker(string action = "GATHER MINERALS");
		//bool hasUnit(const Unit unit) const;
		bool hasUnit(string unitName) const;
		int countUnit(string unitName) const;
		void updateGasRate();

		vector<CurrentUnit> vUnitList;
		string mWorkerName, mGasName, mExpansionName;
		int mMineralRate, mGasRate;
};
