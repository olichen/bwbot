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

	//load workers
	cUnitList.init(cUnitTree.getWorkerName(), cUnitTree.getGasName());
	updateMineralRate();

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
	qBuildOrder.push(&cUnitTree.findUnit("Terran Refinery"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran SCV"));
	qBuildOrder.push(&cUnitTree.findUnit("Terran Factory"));
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
	//update state of all units
	cUnitList.update(vActionList);
	//try to build based off build order
	tryToBuild();
	//handle any thrown actions
	handleActions();
	//refresh mining rate
	updateMineralRate();
	//update frame number
	cResources.nextFrame();
}

void Build::tryToBuild()
{
	if (!qBuildOrder.empty())
	{
		Unit &buildUnit = *(qBuildOrder.front());

		//if not enough resources, give up
		if (buildUnit.getMineralCost() > cResources.getMinerals())
			 return;
		if (buildUnit.getGasCost() > cResources.getGas())
			 return;
		if (buildUnit.getSupplyCost() > cResources.getAvailableSupply())
			 return;

		if (cUnitList.tryToBuild(buildUnit))
		{
			vActionList.push_back(Action("STARTBUILDING", buildUnit));
			qBuildOrder.pop();
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
				cResources.addMinerals();
			else if(iAction.getActionName()=="GATHER GAS")
				cResources.addGas();
			else if(iAction.getActionName()=="STARTBUILDING")
			{
				cResources.useMinerals(iAction.getTargetUnit().getMineralCost());
				cResources.useGas(iAction.getTargetUnit().getGasCost());
				cResources.useSupply(iAction.getTargetUnit().getSupplyCost());
				cUnitList.buildUnit(iAction.getTargetUnit());
			}
			else if(iAction.getActionName()=="CONSTRUCTING")
			{
				cResources.addSupplyMax(iAction.getTargetUnit().getSupplyProvided());
				if(iAction.getTargetUnit().getName() == cUnitTree.getGasName())
					cUnitList.addGasWorker(3);
			}
			else if(iAction.getActionName()=="CREATE")
			{
				cResources.useSupply(iAction.getTargetUnit().getSupplyCost());
				cResources.addSupplyMax(iAction.getTargetUnit().getSupplyProvided());
				cUnitList.spawnUnit(iAction.getTargetUnit());
			}
		}
	}
	vActionList.clear();
}

////END action handling

void Build::updateMineralRate()
{
	int baseRate = cResources.getBaseMineRate();
	int minerCount = cUnitList.minerCount();
	int minPatches = cResources.getMineralPatches();
	if (minerCount <= minPatches)
		cUnitList.setMineralRate(baseRate);
	else if (minerCount <= minPatches * 3)
		cUnitList.setMineralRate((240) * (minerCount - minPatches) / (minPatches * 2) + baseRate * (minPatches * 3 - minerCount) / (minPatches * 2));
	else
		cUnitList.setMineralRate(240 * minerCount / minPatches * 3);
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
	bool hideMining = false;
	bool print = false;
	for (Action &iAction : vActionList)
	{
		if (iAction.getActionName().at(0) == 'G' && hideMining)
			continue;
		cout << iAction.getActionName() << " " << iAction.getTimer();
		if (iAction.hasTargetUnit())
		{
			cout << " " << iAction.getTargetUnit().getName();
		}
		cout << "//";
		print = true;
	}
	if(print)
	{
		cout << "\n";
		printResources();
	}
}
////END debug printing
