#pragma once
#include "activeunit.h"
#include <vector>
using namespace std;

class AllUnits {
	public:
		bool canBuild(UnitStatBlock);
		void build(UnitStatBlock);
		int update();
		void clear();

	private:
		bool hasUnit(UnitName);

		vector<ActiveUnit> unitList;
};
