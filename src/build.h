// build.h
#pragma once
#include "resources.h"
#include "unittree.h"
#include "unitlist.h"
#include "actionlist.h"

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
		void executeActions();
		void printActions();

		Resources cResources;
		UnitTree cUnitTree;
		UnitList cUnitList;
		ActionList cActionList;
		vector<string> *pExecuteActions;
};
