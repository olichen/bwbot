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

		void init();

	private:
		void loadRace(char race = 't');
		void loadBuildOrder();
		void run();
		void update();
		void handleBuild();
		void tryToBuild(string unitName);

		void interactiveMode();

		void handleActions();
		void spawnUnit(Unit &unit);
		void buildUnit(Unit &unit);

		void updateMineralRate();
		//void updateGasRate();
		void printBuildOrder() const;
		void printResources() const;
		void printActions(bool hideMining = true) const;

		Resources cResources;
		UnitTree cUnitTree;
		UnitList cUnitList;
		vector<Action> vActionList;
		vector<string> vBuildOrder;
};
