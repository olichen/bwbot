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
	vOutput.clear();

	//reset resources
	cResources.clear();
	updateMineralRate();
	cResources.useSupply(4);
	cResources.addSupplyMax(cUnitTree.findUnit(cUnitTree.getExpansionName())->getSupplyProvided());
	cResources.addMinerals(50);

	//initialize starting units and resources
	cUnitList.clear();
	for (int i=0; i<4; i++)
	{
		cUnitList.spawnUnit(*(cUnitTree.findUnit(cUnitTree.getWorkerName())));
		addOutput("SPAWN", -1, cUnitTree.getWorkerName());
	}
	cUnitList.spawnUnit(*(cUnitTree.findUnit(cUnitTree.getExpansionName())));
	addOutput("SPAWN", -1, cUnitTree.getExpansionName());


	//zergs get more stuff
	if (cResources.getRace() == 'z')
	{
		cUnitList.spawnUnit(*(cUnitTree.findUnit("Zerg Overlord")));
		cResources.addSupplyMax(cUnitTree.findUnit("Zerg Overlord")->getSupplyProvided());
		addOutput("SPAWN", -1, "Zerg Overlord");
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

void Build::loadVector(vector<string> build)
{
	cBuildOrder.clear();
	loadRace(tolower(build.front().at(0)));
	for (unsigned int i=1; i<build.size(); i++)
	{
		cBuildOrder.push_back(build[i]);
	}
}

void Build::run()
{
	// DEBUG: print build order
	cout << "Build Order: ";
	cBuildOrder.printBuildOrder();

	reset();
	while(cResources.getFrame() <= 20000 && !cBuildOrder.atEnd())
		update();
	printOutput();
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

	//try to build larva
	if (cResources.getRace() == 'z')
		while (cUnitList.addLarva(*(cUnitTree.findUnit("Zerg Larva")), Action("CONSTRUCTING", *(cUnitTree.findUnit("Zerg Larva")))))
			addOutput("STARTBUILD", 342, "Zerg Larva");
	//handle any thrown actions
	handleActions();
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
		{
			if (!cUnitList.removeGasWorker())
				break;
		}
		else if (cBuildOrder.getNext()=="ON GAS")
		{
			if (!cUnitList.addGasWorker())
				break;
		}
		else if (cBuildOrder.getNext()=="EXPAND")
		{
			if (!tryToExpand())
				break;
		}
		else if (cBuildOrder.getNext()=="EXTRACTOR TRICK")
		{
			if(cResources.getRace() != 'z' || cResources.getMinerals() < 100)
				break;
			cResources.addSupplyMax(1);
			if (tryToBuild(cUnitTree.getWorkerName()))
			{
				cResources.useMinerals(25);
				cResources.addSupplyMax(-1);
			}
			else
			{
				cResources.addSupplyMax(-1);
				break;
			}
		}
		else if ((cBuildOrder.getNext() != cUnitTree.getGasName() || cUnitList.gasCount() < cResources.getGasGeysers()) && tryToBuild(cBuildOrder.getNext()))
		{
			//don't let players build too many gasses (idk if this matters tbh)
		}
		else break;

		updateMineralRate();
		//add to output
		addOutput(cBuildOrder.getNext());
		cBuildOrder.next();
	}

}

bool Build::tryToExpand()
{
	Unit *expansionPtr = cUnitTree.findUnit(cUnitTree.getExpansionName());
	if (expansionPtr->getMineralCost() + 8 > cResources.getMinerals())
		 return false;
	if (cUnitList.tryToExpand(*expansionPtr))
	{
		cResources.useMinerals(expansionPtr->getMineralCost() + 8);
		if (expansionPtr->isMorph())
			cResources.useSupply(expansionPtr->getSupplyCost() - cUnitTree.findUnit(expansionPtr->getBuildsFromName())->getSupplyCost());
		//add to output
		addOutput("STARTBUILD", expansionPtr->getBuildTime(), expansionPtr->getName());
		return true;
	}
	return false;
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

	//otherwise build it if prereqs are there
	if (cUnitList.tryToBuild(*(buildUnitPtr)))
	{
		cResources.useMinerals(buildUnitPtr->getMineralCost());
		cResources.useGas(buildUnitPtr->getGasCost());
		if (buildUnitPtr->isMorph())
			cResources.useSupply(buildUnitPtr->getSupplyCost() - cUnitTree.findUnit(buildUnitPtr->getBuildsFromName())->getSupplyCost());
		else
			cResources.useSupply(buildUnitPtr->getSupplyCost());
		cUnitList.buildUnit(*(buildUnitPtr));

		//add to output
		addOutput("STARTBUILD", buildUnitPtr->getBuildTime(), buildUnitPtr->getName());
		return true;
	}
	return false;
}

void Build::addLarvaSpawner()
{
	cUnitList.spawnUnit(*(cUnitTree.findUnit("Zerg Larva Spawner")));
	cUnitList.addLarva(*(cUnitTree.findUnit("Zerg Larva")));
	addOutput("SPAWN",-1,"Zerg Larva");
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

			//add to output
			if (iAction.hasTargetUnit())
				addOutput(iAction.getActionName(), iAction.getTimer(), iAction.getTargetUnit().getName());
			else
				addOutput(iAction.getActionName(), iAction.getTimer());
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

void Build::addOutput(string action, int time, string unit)
{
	Frame newFrame = {
		cResources.getFrame(),
		cResources.getMinerals(),
		cResources.getGas(),
		cResources.getSupply(),
		cResources.getSupplyMax(),
		cUnitList.minerCount(),
		cUnitList.gasMinerCount(),
		time,
		action,
		unit
	};
	vOutput.push_back(newFrame);
}

vector<int> Build::getBuildOrder()
{
	vector<int> output;
	cBuildOrder.reset();
	while (!cBuildOrder.atEnd())
	{
		string unit = cBuildOrder.getNext();
		cBuildOrder.next();
		if(unit == "SEARCH")
			output.push_back(-1);
		else if (unit == "ON GAS")
			output.push_back(-2);
		else if (unit == "OFF GAS")
			output.push_back(-3);
		else if (unit == "EXPAND")
			output.push_back(-4);
		else if (unit == "EXTRACTOR TRICK")
			output.push_back(-5);
		else
			output.push_back(cUnitTree.getId(unit));
	}
	cBuildOrder.reset();
	return output;
}

void Build::printOutput() const
{
	for (Frame iFrame : vOutput)
	{
		printf("%5d %4d %4d %3d/%-3d %3d %3d %-15s %4d %s\n",
			iFrame.frame, iFrame.minerals, iFrame.gas,
			iFrame.supply, iFrame.supplymax,
			iFrame.miners, iFrame.gasminers,
			iFrame.action.c_str(), iFrame.time, iFrame.unit.c_str());
	}
}
