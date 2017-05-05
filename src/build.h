// build.h
#pragma once
#include "resources.h"
#include "unit.h"
#include "currentunit.h"
#include "unittree.h"
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
		void tryToBuild();

		void handleActions();
		void spawnUnit(Unit &unit);
		void buildUnit(Unit &unit);

		void printResources();
		void printActions();

		Resources mResources;
		UnitTree mUnitTree;
		vector<CurrentUnit> vUnitList;
		vector<Action> vActionList;
		queue<Unit*> qBuildOrder;
};
