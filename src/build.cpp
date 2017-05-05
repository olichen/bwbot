// build.cpp
#include "build.h"
#include <iostream>
#include <chrono>

Build::Build()
{
	//
}

Build::~Build()
{
	//
}

void Build::init()
{
	try
	{
		//load initial units
		loadRace('t');

		//start running
		run();
	}
	catch (const string &ex)
	{
		cout << "EXCEPTION CAUGHT; PROGRAM TERMINATED\n";
		cout << "" << ex << "\n";
	}
}

//load up initial state
void Build::loadRace(char race)
{
	//load unit list
	cUnitTree.loadRace(race);

	//load initial units
	if (race == 't')
	{
		vActionList.push_back(Action("SPAWN", cUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("SPAWN", cUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("SPAWN", cUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("SPAWN", cUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("SPAWN", cUnitTree.findUnit("Terran Command Center")));
	}
}

//game loop
void Build::run()
{
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::nanoseconds ns;
	typedef std::chrono::high_resolution_clock clock;

	//framerate (10ms is 100fps, about 4x time)
	const ns timestep = std::chrono::duration_cast<ns>(ms(10));

	auto time_start = clock::now();
	ns lag(0);

	while(cResources.getFrame() <= 400)
	{
		auto time_delta = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<ns>(time_delta);

		while(lag >= timestep)
		{
			lag -= timestep;

			//update
			update();

			//DEBUG: print resources as they change
			printResources();
		}
	}
}

void Build::update()
{
	cResources.nextFrame();
	cUnitList.update(vActionList);
	handleActions();
}

////START action handling
void Build::handleActions()
{
	if (!vActionList.empty())
	{
		//DEBUG: print actions as they happen
		printActions();

		for (Action &iAction : vActionList)
		{
			if(iAction.getActionName()=="GATHER MINERALS")
			{
				cResources.addMinerals();
			}
			else if(iAction.getActionName()=="SPAWN")
			{
				spawnUnit(iAction.getTargetUnit());
			}
		}
	}
	vActionList.clear();
}

void Build::spawnUnit(Unit &unit)
{
	if (unit.getName()=="Terran SCV")
	{
		cUnitList.initUnit(unit, Action(), Action("GATHER MINERALS", 176));
	}
	else
	{
		cUnitList.initUnit(unit);
	}
}
////END action handling

////START debug printing
void Build::printResources()
{
	//printf(" Frame |  Min  |  Gas  | Supply\n");
	printf("%6d |", cResources.getFrame());
	printf("%5d  |", cResources.getMinerals());
	printf("%5d  |", cResources.getGas());
	printf("%4d/%d", cResources.getSupply(), cResources.getSupplyMax());
	printf("\n");
}

//debug purposes
void Build::printActions()
{
	for (Action &iAction : vActionList)
	{
		cout << iAction.getActionName() << "//";
	}
	cout << "\n";
}
////END debug printing
