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
	loadRace(cResources.getRace());
}

//load up initial state
void Build::loadRace(char race)
{
	//load unit list
	cUnitTree.loadRace(race);

	//load workers
	cUnitList.init(cUnitTree.getWorkerName());
	updateMineralRate();

	//load initial units
	for (int i=0; i<4; i++)
		vActionList.push_back(Action("CREATE", *(cUnitTree.findUnit(cUnitTree.getWorkerName()))));
	vActionList.push_back(Action("CREATE", *(cUnitTree.findUnit(cUnitTree.getExpansionName()))));

	cResources.addMinerals(50);
}

//load up build order
void Build::loadBuildOrder(vector<string> buildOrder)
{
	vBuildOrder = buildOrder;
	// DEBUG: print build order
	printBuildOrder();
}

void Build::run()
{
	while(cResources.getFrame() <= 10000) // && !vBuildOrder.empty())
		update();
	//game loop commented out
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
	//	}
	//}
}

void Build::update()
{
	//update state of all units
	cUnitList.update(vActionList);
	//try to do build order
	handleBuild();
	//handle any thrown actions
	printActions();
	handleActions();
	//refresh mining rate
	updateMineralRate();
	//update frame number
	cResources.nextFrame();
}

void Build::handleBuild()
{
	if (!vBuildOrder.empty())
	{
		if (vBuildOrder.front()=="SCOUT")
		{
			cUnitList.scout();
			vBuildOrder.erase(vBuildOrder.begin());
		}
		else
			tryToBuild(vBuildOrder.front());
	}

}

void Build::tryToBuild(string unitName)
{
	Unit *buildUnitPtr = cUnitTree.findUnit(unitName);

	if (buildUnitPtr == NULL)
		throw "Unit " + unitName + " not found.";

	//if not enough resources, give up
	if (buildUnitPtr->getMineralCost() > cResources.getMinerals())
		 return;
	if (buildUnitPtr->getGasCost() > cResources.getGas())
		 return;
	if (buildUnitPtr->getSupplyCost() > cResources.getAvailableSupply())
		 return;

	if (cUnitList.tryToBuild(*(buildUnitPtr)))
	{
		vActionList.push_back(Action("STARTBUILDING", *(buildUnitPtr)));
		vBuildOrder.erase(vBuildOrder.begin());
	}
}

////START action handling
void Build::handleActions()
{
	if (!vActionList.empty())
	{
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
			else if(iAction.getActionName()=="SCOUT")
				cUnitList.scout();
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
		cUnitList.setMineralRate((250) * (minerCount - minPatches) / (minPatches * 2) + baseRate * (minPatches * 3 - minerCount) / (minPatches * 2));
	else
		cUnitList.setMineralRate(250 * minerCount / minPatches * 3);
}

////START debug printing
void Build::printBuildOrder() const
{
	int count = 1;
	for (string buildorder : vBuildOrder)
	{
		cout << buildorder << ", ";
		if (count%5 == 0)
			cout << "\n";
		count++;
	}
	cout << "\n\n";
}

void Build::printResources() const
{
	//printf(" Frame |  Min  |  Gas  | Supply | Time | Miners\n");
	printf("%6d |", cResources.getFrame());
	printf("%5d  |", cResources.getMinerals());
	printf("%5d  |", cResources.getGas());
	printf("%4d/%-3d|", cResources.getSupply(), cResources.getSupplyMax());
	printf("%5d |", cResources.getFrame()*42/1000);
	printf("%5d", cUnitList.minerCount());
	printf("\n");
}

void Build::printActions(bool hideMining) const
{
	bool print = false;
	for (Action iAction : vActionList)
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
		cUnitList.printUnitStatus();
		printResources();
	}
}
////END debug printing
