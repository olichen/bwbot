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

		void init(string workerName);
		void addUnit(Unit &unit, Action nextAction = Action(), Action idleAction = Action());
		void update(vector<Action> &actionList);
		bool tryToBuild(Unit &unit);
		void buildUnit(Unit &unit);
		void spawnUnit(Unit &unit);
		void addGasWorker(int number);
		void scout();

		void setMineralRate(int mineralRate);
		void setGasRate(int mineralRate);

		int minerCount() const;
		int gasMinerCount() const;

		void printUnitStatus() const;

	private:
		CurrentUnit *findWorker();
		//bool hasUnit(const Unit unit) const;
		bool hasUnit(const string unitName) const;

		vector<CurrentUnit> vUnitList;
		string mWorkerName, mGasName;
		int mMineralRate, mGasRate;
};
