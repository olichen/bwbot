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

		//load a build order
		loadBuildOrder();

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
	mUnitTree.loadRace(race);

	//load initial units
	if (race == 't')
	{
		mResources.addMinerals(50);
		vActionList.push_back(Action("SPAWN", mUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("SPAWN", mUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("SPAWN", mUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("SPAWN", mUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("SPAWN", mUnitTree.findUnit("Terran Command Center")));
	}
}

//load up build order
void Build::loadBuildOrder()
{
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
}

//game loop
void Build::run()
{
	while(mResources.getFrame() <= 1000)
	{
		update();
		printResources();
	}
	//typedef std::chrono::milliseconds ms;
	//typedef std::chrono::nanoseconds ns;
	//typedef std::chrono::high_resolution_clock clock;

	////framerate (10ms is 100fps, about 4x time)
	//const ns timestep = std::chrono::duration_cast<ns>(ms(10));

	//auto time_start = clock::now();
	//ns lag(0);

	//while(mResources.getFrame() <= 400)
	//{
	//	auto time_delta = clock::now() - time_start;
	//	time_start = clock::now();
	//	lag += std::chrono::duration_cast<ns>(time_delta);

	//	while(lag >= timestep)
	//	{
	//		lag -= timestep;

	//		//update
	//		update();

	//		//DEBUG: print resources as they change
	//		printResources();
	//	}
	//}
}

void Build::update()
{
	mResources.nextFrame();
	handleActions();
	tryToBuild();
	for (CurrentUnit &iCurrentUnit : vUnitList)
	{
		iCurrentUnit.update(vActionList);
	}
}

void Build::tryToBuild()
{
	if (!qBuildOrder.empty())
	{
		Unit &buildUnit = *(qBuildOrder.front());

		if (buildUnit.getMineralCost() > mResources.getMinerals())
			 return;
		if (buildUnit.getGasCost() > mResources.getGas())
			 return;
		if (buildUnit.getSupplyCost() > mResources.getAvailableSupply())
			 return;

		for (CurrentUnit &iCurrentUnit : vUnitList)
		{
			if (iCurrentUnit.isIdle() && iCurrentUnit.getName() == buildUnit.getBuildsFromName())
			{
				iCurrentUnit.addNextAction(Action("BUILDING", buildUnit.getBuildTime()));
				vActionList.push_back(Action("BUILD", buildUnit));
				qBuildOrder.pop();
			}
		}
	}
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
				mResources.addMinerals();
			}
			else if(iAction.getActionName()=="GATHER GAS")
			{
				mResources.addGas();
			}
			else if(iAction.getActionName()=="BUILD")
			{
				buildUnit(iAction.getTargetUnit());
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
		vUnitList.push_back(CurrentUnit(unit, Action(), Action("GATHER MINERALS", 176)));
	}
	else
	{
		vUnitList.push_back(CurrentUnit(unit));
	}
	mResources.useSupply(unit.getSupplyCost());
	mResources.addSupplyMax(unit.getSupplyProvided());
}

void Build::buildUnit(Unit &unit)
{
	if (unit.getName()=="Terran SCV")
	{
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING",unit.getBuildTime()), Action("GATHER MINERALS", 176)));
	}
	else
	{
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING",unit.getBuildTime())));
	}
	mResources.useMinerals(unit.getMineralCost());
	mResources.useGas(unit.getGasCost());
	mResources.useSupply(unit.getSupplyCost());
	mResources.addSupplyMax(unit.getSupplyProvided());
}
////END action handling

////START debug printing
void Build::printResources()
{
	//printf(" Frame |  Min  |  Gas  | Supply\n");
	printf("%6d |", mResources.getFrame());
	printf("%5d  |", mResources.getMinerals());
	printf("%5d  |", mResources.getGas());
	printf("%4d/%d", mResources.getSupply(), mResources.getSupplyMax());
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
