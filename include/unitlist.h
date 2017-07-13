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
		bool tryToExpand(Unit &expansion);
		bool tryToBuild(Unit &unit);
		void buildUnit(Unit &unit);
		void spawnUnit(Unit &unit);
		bool addGasWorker();
		bool removeGasWorker();
		void scout();
		bool addLarva(Unit &larva, Action nextAction = Action());
		void useLarva();

		void setMineralRate(int mineralRate);
		void clear() { vUnitList.clear(); };

		int minerCount() const;
		int gasMinerCount() const;
		int gasCount() const { return countUnit(mGasName); }

	private:
		bool mergeArchon(Unit &unit);
		CurrentUnit *findWorker(string action = "GATHER MINERALS", bool morph = false);
		bool hasUnit(string unitName) const;
		void updateGasRate();
		int countUnit(string unitName) const;

		vector<CurrentUnit> vUnitList;
		string mWorkerName, mGasName, mExpansionName;
		int mMineralRate, mGasRate;
};
