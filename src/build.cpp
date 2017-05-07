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
		loadRace(cResources.getRace());

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
	cUnitTree.loadRace(race);

	//load initial units
	if (race == 't')
	{
		vActionList.push_back(Action("CREATE", cUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("CREATE", cUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("CREATE", cUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("CREATE", cUnitTree.findUnit("Terran SCV")));
		vActionList.push_back(Action("CREATE", cUnitTree.findUnit("Terran Command Center")));
	}
	cResources.addMinerals(50);
}

//load up build order
void Build::loadBuildOrder()
{
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran Supply Depot"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran Barracks"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
}

//game loop
void Build::run()
{
	while(cResources.getFrame() <= 10000 && !qBuildOrder.empty())
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

	//while(cResources.getFrame() <= 400)
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
	cResources.nextFrame();
}

void Build::tryToBuild()
{
	if (!qBuildOrder.empty())
	{
		Unit &buildUnit = *(qBuildOrder.front());

		//if not enough resources (any of them)
		if (buildUnit.getMineralCost() > cResources.getMinerals())
			 return;
		if (buildUnit.getGasCost() > cResources.getGas())
			 return;
		if (buildUnit.getSupplyCost() > cResources.getAvailableSupply())
			 return;

		//if it is built by a worker, find one that is mining and use it
		if (buildUnit.getBuildsFromName() == cUnitTree.getWorkerName())
		{
			CurrentUnit *workerPtr = NULL;
			int workerFrame = 9999;
			for (CurrentUnit &iCurrentUnit : vUnitList)
			{
				if (iCurrentUnit.getName() == cUnitTree.getWorkerName())
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
				workerPtr->gotoAction(Action("BUILDING", buildUnit));
				vActionList.push_back(Action("STARTBUILDING", buildUnit));
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
					iCurrentUnit.addNextAction(Action("BUILDING", buildUnit));
					vActionList.push_back(Action("STARTBUILDING", buildUnit));
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
				cResources.addMinerals();
			}
			else if(iAction.getActionName()=="GATHER GAS")
			{
				cResources.addGas();
			}
			else if(iAction.getActionName()=="STARTBUILDING")
			{
				buildUnit(iAction.getTargetUnit());
			}
			else if(iAction.getActionName()=="CREATE")
			{
				spawnUnit(iAction.getTargetUnit());
			}
			else if(iAction.getActionName()=="CONSTRUCTING")
			{
				cResources.addSupplyMax(iAction.getTargetUnit().getSupplyProvided());
			}
		}
	}
	vActionList.clear();
}

void Build::spawnUnit(Unit &unit)
{
	if (unit.getName() == cUnitTree.getWorkerName())
	{
		vUnitList.push_back(CurrentUnit(unit, Action(), Action("GATHER MINERALS", getMineralRate())));
	}
	else
	{
		vUnitList.push_back(CurrentUnit(unit));
	}
	cResources.useSupply(unit.getSupplyCost());
	cResources.addSupplyMax(unit.getSupplyProvided());
}

void Build::buildUnit(Unit &unit)
{
	if (unit.getName() == cUnitTree.getWorkerName())
	{
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING",unit), Action("GATHER MINERALS", getMineralRate())));
	}
	else
	{
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING",unit)));
	}
	cResources.useMinerals(unit.getMineralCost());
	cResources.useGas(unit.getGasCost());
	cResources.useSupply(unit.getSupplyCost());
}
////END action handling

int Build::getMineralRate()
{
	int baseRate = cResources.getBaseMineRate();
	int minerCount = 9;
	int minPatches = cResources.getMineralPatches();
	if (minerCount <= minPatches)
		return baseRate;
	else if (minerCount <= minPatches * 3)
		return (250 - baseRate) * minerCount / minPatches + baseRate;
	else
		return 250 * minerCount / minPatches * 3;
}

int Build::getGasRate()
{
	return 111;
}

////START debug printing
void Build::printResources()
{
	//printf(" Frame |  Min  |  Gas  | Supply | Time\n");
	printf("%6d |", cResources.getFrame());
	printf("%5d  |", cResources.getMinerals());
	printf("%5d  |", cResources.getGas());
	printf("%4d/%-3d|", cResources.getSupply(), cResources.getSupplyMax());
	printf("%5d", cResources.getFrame()*42/1000);
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
