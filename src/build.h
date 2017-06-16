// build.h
#pragma once
#include "resources.h"
#include "unit.h"
#include "currentunit.h"
#include "unittree.h"
#include "unitlist.h"
#include "frame.h"
#include "action.h"
#include "string_alg.hpp"
#include "buildorder.hpp"
#include <fstream>
#include <vector>

class Build
{
	public:
		Build();
		~Build();

		void init(char race = 't'); //loads up race
		void reset(); //resets build to frame 0
		void clear(); //clears build order and resets build
		void loadRace(char race); //loads up race
		void run(); //runs build order
		//void loadBuildOrder(vector<string> buildOrder);
		void loadFile(string fileName); //load file (race, build)
		void loadVector(vector<string> build); //load file (race, build)

		void pushBuildOrder(string build) { cBuildOrder.push_back(build); }
		void popBuildOrder() { cBuildOrder.pop(); }

		vector<Frame> getOutput() { return vOutput; };

	private:
		void update();
		void handleBuild();
		bool tryToExpand();
		bool tryToBuild(string unitName);

		void handleActions();
		void spawnUnit(Unit &unit);
		void buildUnit(Unit &unit);
		void addLarvaSpawner();

		void updateMineralRate();
		void addOutput(string action = "", int time = -1, string unit = "");
		void printOutput() const;

		Resources cResources;
		UnitTree cUnitTree;
		UnitList cUnitList;
		vector<Action> vActionList;
		BuildOrder cBuildOrder;
		vector<Frame> vOutput;
};
