#pragma once
#include "buildhandler.h"
#include "resourcehandler.h"
#include "buildorder2.h"
#include <vector>
#include <iterator>
using namespace std;

class BWBOT {
	public:
		void main();
		void run();

	private:
		void update();
		void testinit();
		void testprint();
		void init(char);
		bool tryToBuild(UnitName);
		void clear();

		BuildHandler buildHandler;
		BuildOrder buildOrder;
		ResourceHandler resourceHandler;
		vector<Frame> output;
		UnitData unitData;
};
