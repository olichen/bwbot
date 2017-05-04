// build.h
#pragma once
#include "resources.h"
#include "unittree.h"
#include "unitlist.h"

class Build
{
	public:
		Build();
		~Build();

		void init();

	private:
		void update();
		void printResources();
		void loadRace(char race = 't');

		Resources cResources;
		UnitTree cUnitTree;
		UnitList cUnitList;
};
