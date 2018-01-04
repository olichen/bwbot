#pragma once
#include "buildhandler.h"
#include "resourcehandler.h"
#include "buildorder2.h"
#include <vector>
#include <iterator>
using namespace std;

class BWBOT {
	public:
		void run();
		void init(char);
		void testinit();
		void testprint();

	private:
		void update();
		void addFrameToOutput(Frame);
		bool tryToBuild(UnitName);
		void clear();

		BuildHandler buildHandler;
		BuildOrder buildOrder;
		ResourceHandler resourceHandler;
		vector<Frame> output;
		UnitData unitData;
};
