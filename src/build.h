// build.h
#pragma once
#include "resources.h"
#include "unittree.h"
#include "unitlist.h"
#include "action.h"

class Build
{
	public:
		Build();
		~Build();

		void init();
		void run();

	private:
		void update();
		void printResources();
		void loadRace(char race = 't');
		void handleActions();
		void spawnUnit(Unit &unit);
		void printActions();

		Resources cResources;
		UnitTree cUnitTree;
		UnitList cUnitList;
		vector<Action> vActionList;
};
