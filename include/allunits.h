#pragma once
#include "unitdata.h"
#include "activeunit.h"
#include <vector>
using namespace std;

class AllUnits {
	public:
		bool canBuild(UnitName);
		void build(UnitName);
		void spawn(UnitName, UnitStatBlock);
		int update();
		void clear();

	private:
		bool hasUnit(UnitName);

		vector<ActiveUnit> unitList;
};
