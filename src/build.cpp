// build.cpp
#include "build.h"
#include <iostream>

Build::Build()
{
	init();
}

Build::~Build()
{
	//
}

void Build::init(char race)
{
	//load up initial state
	loadRace(race);
}

void Build::reset()
{
	//initialize starting units and resources
	cUnitList.clear();
	for (int i=0; i<4; i++)
		cUnitList.spawnUnit(*(cUnitTree.findUnit(cUnitTree.getWorkerName())));
	cUnitList.spawnUnit(*(cUnitTree.findUnit(cUnitTree.getExpansionName())));

	//reset resources
	cResources.clear();
	updateMineralRate();
	cResources.useSupply(4);
	cResources.addSupplyMax(cUnitTree.findUnit(cUnitTree.getExpansionName())->getSupplyProvided());
	cResources.addMinerals(50);

	cBuildOrder.reset();
}

//load up initial state
void Build::loadRace(char race)
{
	if (race != 'z' && race != 't' && race != 'p')
		throw "Race '" + string(1, race) + "' not found.";
	//clear old data
	cBuildOrder.clear();
	cBuildOrder.setRace(race);
	//load unit list
	cUnitTree.loadRace(race);
	cResources.setRace(race);
	//load worker name
	cUnitList.init(cUnitTree.getWorkerName());
	reset();
}

void Build::loadFile(string fileName)
{
	ifstream buildOrderFile("buildorders/" + fileName);
	if(buildOrderFile.is_open())
	{
		cBuildOrder.clear();
		string line = "";
		getline(buildOrderFile, line);
		loadRace(tolower(line.at(0)));
		while (getline(buildOrderFile, line))
			cBuildOrder.addToBuildOrder(line);
		buildOrderFile.close();
	}
	else
		throw "Unable to open file 'buildorders/" + fileName + "'";
}

void Build::run()
{
	reset();
	// DEBUG: print build order
	cBuildOrder.printBuildOrder();
	while(cResources.getFrame() <= 10000) // && !vBuildOrder.empty())
		update();
}

void Build::update()
{
	//try to build
	try
	{
		handleBuild();
	}
	catch (const string &ex)
	{
		cout << "Error: " << ex << "\n";
		cBuildOrder.setLength();
	}
	//update state of all units
	cUnitList.update(vActionList);
	//handle any thrown actions
	handleActions();
	//DEBUG: print out actions
	//printActions();
	//refresh mining rate
	updateMineralRate();
	//update frame number
	cResources.nextFrame();
}

void Build::handleBuild()
{
	while (!cBuildOrder.atEnd())
	{
		if (cBuildOrder.getNext()=="SCOUT")
		{
			cUnitList.scout();
			cBuildOrder.next();

			//DEBUG: print stuff
			cout << "Sending one worker to scout\n Constructing:";
			cUnitList.printBuilding();
			cUnitList.printUnits();
			cout << endl;
			printResources();
		}
		else if (tryToBuild(cBuildOrder.getNext()));
		else break;
	}

}

bool Build::tryToBuild(string unitName)
{
	Unit *buildUnitPtr = cUnitTree.findUnit(unitName);

	if (buildUnitPtr == NULL)
	{
		throw "Unit '" + unitName + "' not found.";
	}

	//if not enough resources, give up
	if (buildUnitPtr->getMineralCost() > cResources.getMinerals())
		 return false;
	if (buildUnitPtr->getGasCost() > cResources.getGas())
		 return false;
	if (buildUnitPtr->getSupplyCost() > cResources.getAvailableSupply())
		 return false;

	if (cUnitList.tryToBuild(*(buildUnitPtr)))
	{
		cResources.useMinerals(buildUnitPtr->getMineralCost());
		cResources.useGas(buildUnitPtr->getGasCost());
		cResources.useSupply(buildUnitPtr->getSupplyCost());
		cUnitList.buildUnit(*(buildUnitPtr));
		cBuildOrder.next();

		//DEBUG PRINTING
		cout << "Starting to build: " << buildUnitPtr->getName() << " (" << buildUnitPtr->getBuildTime() << " frames)\n Constructing:";
		cUnitList.printBuilding();
		cUnitList.printUnits();
		cout << "\n";
		printResources();
		return true;
	}
	return false;
}

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
			else if(iAction.getActionName()=="CONSTRUCTING")
			{
				cResources.addSupplyMax(iAction.getTargetUnit().getSupplyProvided());
				if(iAction.getTargetUnit().getName() == cUnitTree.getGasName())
					cUnitList.addGasWorker(3);
			}
		}
	}
	vActionList.clear();
}

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

void Build::printResources() const
{
	printf(" Frame |  Min  |  Gas  | Supply | Time | Miners\n");
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
		cout << " "<<  iAction.getActionName() << " " << iAction.getTimer();
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
