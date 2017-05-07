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

		void initUnit(Unit &unit, Action nextAction = Action(), Action idleAction = Action());
		void update(vector<Action> &actionList);

		int minerCount();
		int gasMinerCount();

	private:
		vector<CurrentUnit> vUnitList;
};
