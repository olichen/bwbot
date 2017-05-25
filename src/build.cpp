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

	//zergs get more stuff
	if (cResources.getRace() == 'z')
	{
		cUnitList.spawnUnit(*(cUnitTree.findUnit("Zerg Overlord")));
		cResources.addSupplyMax(cUnitTree.findUnit("Zerg Overlord")->getSupplyProvided());
		addLarvaSpawner();
		cUnitList.addLarva(*(cUnitTree.findUnit("Zerg Larva")));
		cUnitList.addLarva(*(cUnitTree.findUnit("Zerg Larva")));
	}

	cBuildOrder.reset();
}

void Build::clear()
{
	cBuildOrder.clear();
	reset();
}

//load up initial state
void Build::loadRace(char race)
{
	if (race != 'z' && race != 't' && race != 'p')
		throw "Race '" + string(1, race) + "' not found.";
	//clear old data
	cBuildOrder.setRace(race);
	//load unit list
	cUnitTree.loadRace(race);
	cResources.setRace(race);
	//load worker name
	cUnitList.init(cUnitTree.getWorkerName(), cUnitTree.getExpansionName(), cUnitTree.getGasName());
	clear();
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
			cBuildOrder.push_back(line);
		buildOrderFile.close();
	}
	else
		throw "Unable to open file 'buildorders/" + fileName + "'";
}

void Build::run()
{
	// DEBUG: print build order
	cout << "Build Order: ";
	cBuildOrder.printBuildOrder();

	reset();
	while(cResources.getFrame() <= 20000 && !cBuildOrder.atEnd())
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
	//DEBUG: print out actions
	//printActions(false);

	//try to build larva
	if (cResources.getRace() == 'z')
		while (cUnitList.addLarva(*(cUnitTree.findUnit("Zerg Larva")), Action("CONSTRUCTING", *(cUnitTree.findUnit("Zerg Larva")))));
	//handle any thrown actions
	handleActions();
	//refresh mining rate
	//update frame number
	cResources.nextFrame();
}

void Build::handleBuild()
{
	while (!cBuildOrder.atEnd())
	{
		if (cBuildOrder.getNext()=="SEARCH")
			cUnitList.scout();
		else if (cBuildOrder.getNext()=="OFF GAS")
			cUnitList.removeGasWorker();
		else if (cBuildOrder.getNext()=="ON GAS")
			cUnitList.addGasWorker();
		else if (cBuildOrder.getNext()=="EXPAND")
		{
			Unit *expansionPtr = cUnitTree.findUnit(cUnitTree.getExpansionName());
			if (expansionPtr->getMineralCost() + 8 > cResources.getMinerals())
				 break;
			if (cUnitList.tryToExpand(*expansionPtr))
			{
				cResources.useMinerals(expansionPtr->getMineralCost());
				if (expansionPtr->isMorph())
					cResources.useSupply(expansionPtr->getSupplyCost() - cUnitTree.findUnit(expansionPtr->getBuildsFromName())->getSupplyCost());
				//
				cout << "$> Starting to build: " << cBuildOrder.getNext();
				cout << " (" << 1800 << " frames, ";
				cout << 42.0 * 1800/1000 << " seconds)\n Constructing:";
				cUnitList.printBuilding();
				cUnitList.printUnits();
				cout << "\n";
				printResources();
			}
		}
		else if ((cBuildOrder.getNext() != cUnitTree.getGasName() || cUnitList.gasCount() < cResources.getGasGeysers()) && tryToBuild(cBuildOrder.getNext()))
		{
			if (true || cBuildOrder.getNext() != cUnitTree.getWorkerName())
			{
				//DEBUG PRINTING
				cout << "$> Starting to build: " << cBuildOrder.getNext();
				cout << " (" << cUnitTree.findUnit(cBuildOrder.getNext())->getBuildTime() << " frames, ";
				cout << 42.0 * cUnitTree.findUnit(cBuildOrder.getNext())->getBuildTime()/1000 << " seconds)\n Constructing:";
				cUnitList.printBuilding();
				cUnitList.printUnits();
				cout << "\n";
				printResources();
				//
			}
		}
		else break;

		updateMineralRate();
		cBuildOrder.next();
	}

}

bool Build::tryToBuild(string unitName)
{
	Unit *buildUnitPtr = cUnitTree.findUnit(unitName);

	if (buildUnitPtr == NULL)
		throw "Unit '" + unitName + "' not found.";

	//if not enough resources, give up
	if (buildUnitPtr->getMineralCost() > cResources.getMinerals())
		 return false;
	if (buildUnitPtr->getGasCost() > cResources.getGas())
		 return false;
	if (buildUnitPtr->isMorph() && buildUnitPtr->getSupplyCost() > 0)
	{
		if (buildUnitPtr->getSupplyCost() - cUnitTree.findUnit(buildUnitPtr->getBuildsFromName())->getSupplyCost() > 0)
			if (buildUnitPtr->getSupplyCost() - cUnitTree.findUnit(buildUnitPtr->getBuildsFromName())->getSupplyCost() > cResources.getAvailableSupply())
				return false;
	}
	else if (buildUnitPtr->getSupplyCost() > 0 && buildUnitPtr->getSupplyCost() > cResources.getAvailableSupply())
		 return false;

	if (cUnitList.tryToBuild(*(buildUnitPtr)))
	{
		cResources.useMinerals(buildUnitPtr->getMineralCost());
		cResources.useGas(buildUnitPtr->getGasCost());
		if (buildUnitPtr->isMorph())
			cResources.useSupply(buildUnitPtr->getSupplyCost() - cUnitTree.findUnit(buildUnitPtr->getBuildsFromName())->getSupplyCost());
		else
			cResources.useSupply(buildUnitPtr->getSupplyCost());
		cUnitList.buildUnit(*(buildUnitPtr));
		return true;
	}
	return false;
}

void Build::addLarvaSpawner()
{
	cUnitList.spawnUnit(*(cUnitTree.findUnit("Zerg Larva Spawner")));
	cUnitList.addLarva(*(cUnitTree.findUnit("Zerg Larva")));
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
			else if(iAction.getActionName()=="EXPANDING")
			{
				cResources.addExpansion();
				updateMineralRate();
			}
			else if(iAction.getActionName()=="CONSTRUCTING")
			{
				cResources.addSupplyMax(iAction.getTargetUnit().getSupplyProvided());
				if(iAction.getTargetUnit().getName() == "Zerg Hatchery")
					addLarvaSpawner();
				if(iAction.getTargetUnit().getName() == cUnitTree.getGasName())
					for (int i=0; i<3; i++)
						cUnitList.addGasWorker();
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
		cUnitList.setMineralRate((240) * (minerCount - minPatches) / (minPatches * 2) + baseRate * (minPatches * 3 - minerCount) / (minPatches * 2));
	else
		cUnitList.setMineralRate(240 * minerCount / minPatches * 3);
}

void Build::printResources() const
{
	//printf(" Frame |  Min  |  Gas  | Supply |  Time | Miners\n");
	printf("%6d |", cResources.getFrame());
	printf("%5d  |", cResources.getMinerals());
	printf("%5d  |", cResources.getGas());
	printf("%4d/%-3d|", cResources.getSupply(), cResources.getSupplyMax());
	printf("%6.1f |", 42.0 * cResources.getFrame()/1000);
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
