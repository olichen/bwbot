// build.h
#pragma once
#include "resources.h"
#include "unit.h"
#include "currentunit.h"
#include "unittree.h"
#include "unitlist.h"
#include "action.h"
#include <vector>
#include <queue>

class Build
{
	public:
		Build();
		~Build();

		void init();

	private:
		void loadRace(char race = 't');
		void loadBuildOrder();
		void run();
		void update();
		void handleBuild();
		void tryToBuild(string unitName);

		void handleActions();
		void spawnUnit(Unit &unit);
		void buildUnit(Unit &unit);

		void updateMineralRate();
		int getGasRate();
		void printResources();
		void printActions();

		Resources cResources;
		UnitTree cUnitTree;
		UnitList cUnitList;
		vector<Action> vActionList;
		queue<string> qBuildOrder;
};
