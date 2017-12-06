#pragma once
#include "buildhandler.h"
#include "currentframe.h"
#include "buildorder2.h"
#include <vector>
#include <iterator>
using namespace std;

class BWBOT {
	public:

	private:
		BuildHandler buildHandler;

		BuildOrder buildOrder;
		CurrentFrame currentFrame;
		vector<Frame> output;
		UnitData unitData;
};
