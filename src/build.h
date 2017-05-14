// build.h
#pragma once
#include "resources.h"
#include "unit.h"
#include "currentunit.h"
#include "unittree.h"
#include "unitlist.h"
#include "action.h"
#include <vector>

class Build
{
	public:
		Build();
		~Build();

		void init(char race = 't');
		void run();
		void loadBuildOrder(vector<string> buildOrder);
		void loadFile(string fileName);

	private:
		void loadRace(char race);
		void update();
		void handleBuild();
		bool tryToBuild(string unitName);

		void handleActions();
		void spawnUnit(Unit &unit);
		void buildUnit(Unit &unit);

		void updateMineralRate();
		void printBuildOrder() const;
		void printResources() const;
		void printActions(bool hideMining = true) const;

		Resources cResources;
		UnitTree cUnitTree;
		UnitList cUnitList;
		vector<Action> vActionList;
		vector<string> vBuildOrder;
};
