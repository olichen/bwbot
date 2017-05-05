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
		vActionList.push_back(Action("CREATE", mUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("CREATE", mUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("CREATE", mUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("CREATE", mUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("CREATE", mUnitTree.findUnit("Terran Command Center")));
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
	qBuildOrder.push(&mUnitTree.findUnit("Terran Supply Depot"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran Barracks"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&mUnitTree.findUnit("Terran SCV"));
}

//game loop
void Build::run()
{
	while(mResources.getFrame() <= 10000 && !qBuildOrder.empty())
	{
		update();
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
	handleActions();
	tryToBuild();
	for (CurrentUnit &iCurrentUnit : vUnitList)
	{
		iCurrentUnit.update(vActionList);
	}
	mResources.nextFrame();
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

		//if it is built by a worker, find one that is mining and use it
		if (buildUnit.getBuildsFromName() == mUnitTree.getWorkerName())
		{
			CurrentUnit *workerPtr = NULL;
			int workerFrame = 9999;
			for (CurrentUnit &iCurrentUnit : vUnitList)
			{
				if (iCurrentUnit.getName() == mUnitTree.getWorkerName())
				{
					if (iCurrentUnit.getActionName() == "GATHER MINERALS")
					{
						if (iCurrentUnit.getTimer() < workerFrame)
						{
							workerPtr = &iCurrentUnit;
							workerFrame = iCurrentUnit.getTimer();
						}
					}
				}
			}
			if (workerPtr != NULL)
			{
				workerPtr->gotoAction(Action("PRODUCING", buildUnit));
				vActionList.push_back(Action("CREATEUNIT", buildUnit));
				qBuildOrder.pop();
				return;
			}
		}

		//find an idle production facility
		for (CurrentUnit &iCurrentUnit : vUnitList)
		{
			if (iCurrentUnit.getName() == buildUnit.getBuildsFromName())
			{
				if (iCurrentUnit.isIdle())
				{
					iCurrentUnit.addNextAction(Action("PRODUCING", buildUnit));
					vActionList.push_back(Action("CREATEUNIT", buildUnit));
					qBuildOrder.pop();
					return;
				}
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
			else if(iAction.getActionName()=="CREATEUNIT")
			{
				buildUnit(iAction.getTargetUnit());
			}
			else if(iAction.getActionName()=="CREATE")
			{
				spawnUnit(iAction.getTargetUnit());
			}
			else if(iAction.getActionName()=="SPAWNING")
			{
				mResources.addSupplyMax(iAction.getTargetUnit().getSupplyProvided());
			}
		}
	}
	vActionList.clear();
}

void Build::spawnUnit(Unit &unit)
{
	if (unit.getName() == mUnitTree.getWorkerName())
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
	if (unit.getName() == mUnitTree.getWorkerName())
	{
		vUnitList.push_back(CurrentUnit(unit, Action("SPAWNING",unit), Action("GATHER MINERALS", 176)));
	}
	else
	{
		vUnitList.push_back(CurrentUnit(unit, Action("SPAWNING",unit)));
	}
	mResources.useMinerals(unit.getMineralCost());
	mResources.useGas(unit.getGasCost());
	mResources.useSupply(unit.getSupplyCost());
}
////END action handling

////START debug printing
void Build::printResources()
{
	//printf(" Frame |  Min  |  Gas  | Supply | Time\n");
	printf("%6d |", mResources.getFrame());
	printf("%5d  |", mResources.getMinerals());
	printf("%5d  |", mResources.getGas());
	printf("%4d/%-3d|", mResources.getSupply(), mResources.getSupplyMax());
	printf("%5d", mResources.getFrame()*42/1000);
	printf("\n");
}

void Build::printActions()
{
	printResources();
	for (Action &iAction : vActionList)
	{
		cout << iAction.getActionName();
		if (iAction.hasTargetUnit())
		{
			cout << " " << iAction.getTargetUnit().getName();
		}
		cout << "//";
	}
	cout << "\n\n";
}
////END debug printing
