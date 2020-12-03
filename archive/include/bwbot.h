#pragma once
#include "buildhandler.h"
#include "resourcehandler.h"
#include "buildorder2.h"
#include <vector>
#include <iterator>
using namespace std;

class BWBOT {
	public:
		void testinit();
		void testprint();
		void init(char);
		void run();

	private:
		void update();
		void addFrameToOutput(Frame);
		void useBuildOrder(Frame);
		void doAction(UnitName);
		bool canBuild(UnitName);
		Frame build(UnitName);
		void clear();

		BuildHandler buildHandler;
		BuildOrder buildOrder;
		ResourceHandler resourceHandler;
		vector<Frame> output;
		UnitData unitData;
};
