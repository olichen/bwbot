#pragma once
#include "activeunit.h"
#include <vector>
using namespace std;

class AllUnits {
	ActionName action;
	int timer;
	private:
		vector<ActiveUnit> unitList;
};
