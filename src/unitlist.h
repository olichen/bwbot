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

		void initUnit(Unit &unit, Action nextAction, Action idleAction, int num = 1);
		vector<string>* update();

	private:
		vector<CurrentUnit> vUnitList;
		vector<string>* vActionList;
};
