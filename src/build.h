#pragma once
#include "resources.h"
#include "unittree.h"

class Build
{
	public:
		Build();
		~Build();

		void init();

	private:
		Resources resources;
		UnitTree unitTree;
		void update();
		void loadRace(char race);
		void printResources();
};
