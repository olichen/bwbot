// unitlist.h
#pragma once
#include "currentunit.h"
#include "unit.h"
#include <string>
#include <vector>
using namespace std;

class UnitList
{
	public:
		UnitList();
		~UnitList();

		void initUnit(Unit &unit, int num = 1, string nextAction = "IDLE", int nextTimer = -1, string idleAction = "IDLE", int idleTimer = -1);
		vector<string>* update();

	private:
		vector<CurrentUnit> vUnitList;
		vector<string>* vActionList;
};
