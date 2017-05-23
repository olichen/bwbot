// unitlist.cpp
#include "unitlist.h"

UnitList::UnitList()
	: mMineralRate(177), mGasRate(111)
{
	//
}

void UnitList::init(string workerName, string expansionName, string gasName)
{
	mWorkerName = workerName;
	mExpansionName = expansionName;
	mGasName = gasName;
}

void UnitList::setMineralRate(int mineralRate)
{
	if (mMineralRate != mineralRate)
	{
		for (CurrentUnit &iCurrentUnit : vUnitList)
		{
			if (iCurrentUnit.getIdleActionName() == "GATHER MINERALS")
			{
				iCurrentUnit.setIdleActionTimer(mineralRate);
				mMineralRate = mineralRate;
			}
		}
	}
}

void UnitList::updateGasRate()
{
	if (gasMinerCount() >= 3 * countUnit(mGasName))
		mGasRate = 111 * gasMinerCount() / (3 * countUnit(mGasName));
	else
		mGasRate = 111;
	for (CurrentUnit &iCurrentUnit : vUnitList)
		if (iCurrentUnit.getIdleActionName() == "GATHER GAS")
			iCurrentUnit.setIdleActionTimer(mGasRate);
}

bool UnitList::addLarva(Unit &larva, Action nextAction)
{
	for (CurrentUnit &iCurrentUnit : vUnitList)
	{
		if (iCurrentUnit.getName() == "Zerg Larva Spawner")
		{
			if (iCurrentUnit.getCount() == 3)
				continue;
			if (iCurrentUnit.isIdle())
			{
				iCurrentUnit.addCount();
				CurrentUnit newUnit(larva, nextAction);
				if (nextAction.getActionName() != "IDLE")
					iCurrentUnit.gotoAction(Action("BUILDING", larva));
				vUnitList.push_back(newUnit);
				return true;
			}
		}
	}
	return false;
}

void UnitList::useLarva()
{
	CurrentUnit *larvaSpawner = NULL;
	int larvaCount = 0;
	int larvaFrame = 342;
	for (CurrentUnit &iCurrentUnit : vUnitList)
	{
		if (iCurrentUnit.getName() == "Zerg Larva Spawner")
		{
			if (iCurrentUnit.getCount() > larvaCount)
			{
				larvaSpawner = &iCurrentUnit;
				larvaCount = iCurrentUnit.getCount();
				larvaFrame = iCurrentUnit.getTimer();
			}
			if (iCurrentUnit.getCount() == larvaCount && iCurrentUnit.getTimer() < larvaFrame)
			{
				larvaSpawner = &iCurrentUnit;
				larvaFrame = iCurrentUnit.getTimer();
			}
		}
	}
	larvaSpawner->addCount(-1);
}

void UnitList::addUnit(Unit &unit, Action nextAction, Action idleAction)
{
	CurrentUnit newUnit(unit, nextAction, idleAction);
	vUnitList.push_back(newUnit);
}

bool UnitList::tryToExpand(Unit &expansion)
{

	//otherwise find an idle worker
	CurrentUnit *workerPtr = findWorker("GATHER MINERALS", expansion.isMorph());
	if (workerPtr != NULL)
	{
		if(expansion.getBuildsFromName() != "Protoss Probe" && !expansion.isMorph())
			workerPtr->gotoAction(Action("BUILDING", expansion));
	}
	else
		return false;
	CurrentUnit newExpansion(expansion, Action("EXPANDING",expansion.getBuildTime()-1));
	newExpansion.addNextAction(Action("CONSTRUCTING",1,expansion));
	vUnitList.push_back(newExpansion);
	return true;
}

bool UnitList::tryToBuild(Unit &unit)
{
	//check prerequisites
	if (!hasUnit(unit.getPrereqName()))
		return false;
	if (unit.hasPrereq2() && !hasUnit(unit.getPrereq2Name()))
		return false;

	//if unit builds from worker
	if (unit.getBuildsFromName() == mWorkerName)
	{
		//find an idle worker
		CurrentUnit *workerPtr = findWorker("GATHER MINERALS", unit.isMorph());
		if (workerPtr != NULL)
		{
			//warp it in if builds from probe
			if (unit.getBuildsFromName() == "Protoss Probe")
				return true;

			if(unit.isMorph())
				return true;
			workerPtr->gotoAction(Action("BUILDING", unit));
			return true;
		}
	}
	else if (unit.getName() == "Protoss Archon" || unit.getName() == "Protoss Dark Archon")
		return mergeArchon(unit);
	//if unit builds from something else
	else
	{
		//find an idle production facility
		for (unsigned int i=0; i < vUnitList.size(); i++) //CurrentUnit &iCurrentUnit : vUnitList)
		{
			CurrentUnit &iCurrentUnit = vUnitList[i];
			if (iCurrentUnit.getName() == unit.getBuildsFromName())
			{
				if (unit.getName() == "Protoss Interceptor")
				{
					if (iCurrentUnit.getCount() == 8)
						continue;
					if (iCurrentUnit.getCount() == 4 && !hasUnit("Protoss Carrier Capacity"))
						continue;
				}
				if (unit.getName() == "Protoss Scarab")
				{
					if (iCurrentUnit.getCount() == 10)
						continue;
					if (iCurrentUnit.getCount() == 5 && !hasUnit("Protoss Reaver Capacity"))
						continue;
				}
				//continue if unit requires addon but building does not have one
				if (unit.reqAddon() && !iCurrentUnit.hasAddon())
					continue;
				if (unit.isAddon() && iCurrentUnit.hasAddon())
					continue;
				if (iCurrentUnit.isIdle())
				{
					iCurrentUnit.gotoAction(Action("BUILDING", unit));
					if (unit.isMorph())
						vUnitList.erase(vUnitList.begin() + i);
					if (unit.getBuildsFromName() == "Zerg Larva")
						useLarva();
					if (unit.isAddon())
						iCurrentUnit.addAddon();
					return true;
				}
			}
		}
	}
	return false;
}

bool UnitList::mergeArchon(Unit &unit)
{
	int temp1 = -1;
	int temp2 = -1;
	for (int i=0; i < (int) vUnitList.size(); i++)
	{
		if (vUnitList[i].getName() == unit.getBuildsFromName() && vUnitList[i].isIdle())
		{
			if (temp1 == -1)
				temp1 = i;
			else
				temp2 = i;
		}
	}
	if (temp1 != -1 && temp2 != -1)
	{
		vUnitList.erase(vUnitList.begin() + temp2);
		vUnitList.erase(vUnitList.begin() + temp1);
		return true;
	}

	return false;
}

bool UnitList::hasUnit(string unitName) const
{
	for (CurrentUnit iCurrentUnit : vUnitList)
		if (iCurrentUnit.getName() == unitName)
			if (iCurrentUnit.getActionName() != "CONSTRUCTING")
				return true;
	return false;
}

int UnitList::countUnit(string unitName) const
{
	int count = 0;
	for (CurrentUnit iCurrentUnit : vUnitList)
		if (iCurrentUnit.getName() == unitName)
			count++;
	return count;
}

//find the most idle worker (whoever is most done with mining)
CurrentUnit *UnitList::findWorker(string action, bool morph)
{
	CurrentUnit *workerPtr = NULL;
	int workerFrame = -1;
	unsigned int workerID = -1;
	for (unsigned int i = 0; i<vUnitList.size(); i++) //CurrentUnit &iCurrentUnit : vUnitList)
	{
		CurrentUnit &iCurrentUnit = vUnitList[i];
		if (iCurrentUnit.getActionName() == action)
		{
			if (iCurrentUnit.getTimer() > workerFrame)
			{
				workerPtr = &iCurrentUnit;
				workerFrame = iCurrentUnit.getTimer();
				workerID = i;
			}
		}
	}
	if (morph)
		vUnitList.erase(vUnitList.begin() + workerID);
	return workerPtr;
}

void UnitList::addGasWorker()
{
	CurrentUnit *workerPtr = findWorker();
	int gasInit = mGasRate;
	CurrentUnit *gasWorkerPtr = findWorker("GATHER GAS");
	if (gasWorkerPtr != NULL)
		gasInit = gasWorkerPtr->getTimer() + 37;
	workerPtr->gotoAction(Action("GATHER GAS", gasInit));
	workerPtr->setIdleAction(Action("GATHER GAS", mGasRate));
	updateGasRate();
}

void UnitList::removeGasWorker()
{
	CurrentUnit *workerPtr = findWorker("GATHER GAS");
	workerPtr->gotoAction(Action("GATHER MINERALS", mMineralRate - mGasRate + workerPtr->getTimer()));
	workerPtr->setIdleAction(Action("GATHER MINERALS", mMineralRate));
	updateGasRate();
}

void UnitList::scout()
{
	findWorker()->gotoAction(Action("SCOUT",999999));
}

void UnitList::buildUnit(Unit &unit)
{
	if (unit.getName() == "Zerg Drone")
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit.getBuildTime() + 18, unit), Action("GATHER MINERALS", mMineralRate)));
	else if (unit.getName() == mWorkerName)
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit), Action("GATHER MINERALS", mMineralRate)));
	else if (unit.isMorph())
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit.getBuildTime() + 18, unit)));
	else if (unit.getBuildsFromName() == "Protoss Probe")
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit.getBuildTime() + 70, unit)));
	else
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit)));
}

void UnitList::spawnUnit(Unit &unit)
{
	if (unit.getName() == mWorkerName)
		vUnitList.push_back(CurrentUnit(unit, Action(), Action("GATHER MINERALS", mMineralRate)));
	else
		vUnitList.push_back(CurrentUnit(unit));
}

void UnitList::update(vector<Action> &actionList)
{
	for (CurrentUnit &iUnit : vUnitList)
		iUnit.update(actionList);
}

int UnitList::minerCount() const
{
	int count = 0;
	for (CurrentUnit iUnit : vUnitList)
		if (iUnit.getActionName() == "GATHER MINERALS")
			count++;
	return count;
}

int UnitList::gasMinerCount() const
{
	int count = 0;
	for (CurrentUnit iUnit : vUnitList)
		if (iUnit.getActionName() == "GATHER GAS")
			count++;
	return count;
}

void UnitList::printUnitStatus(bool hideMining, bool hideIdle) const
{
	bool print = false;
	for (CurrentUnit iUnit : vUnitList)
	{
		if (hideMining && iUnit.getActionName().at(0) == 'G')
			continue;
		if (hideMining && iUnit.getActionName().at(0) == 'I')
			continue;
		printf("  %s: %d %s", iUnit.getName().c_str(), iUnit.getTimer(), iUnit.getActionName().c_str());
		print = true;
	}
	if(print)
		printf("\n");
}

void UnitList::printUnits() const
{
	vector<string> unitNames;
	vector<unsigned int> unitCount;
	for (CurrentUnit iUnit : vUnitList)
	{
		if (iUnit.getActionName() != "CONSTRUCTING")
		{
			int hasUnit = -1;
			for (unsigned int i=0; i<unitNames.size(); i++)
			{
				if (unitNames[i] == iUnit.getName())
				{
					hasUnit = i;
					break;
				}
			}
			if (hasUnit != -1)
				unitCount[hasUnit] += 1;
			else
			{
				unitNames.push_back(iUnit.getName());
				unitCount.push_back(1);
			}
		}
	}
	printf(" // Units: ");
	for (unsigned int i=0; i<unitNames.size(); i++)
		printf("%i %s, ", unitCount[i], unitNames[i].c_str());
	printLarva();
}

void UnitList::printLarva() const
{
	for (CurrentUnit iUnit : vUnitList)
	{
		if (iUnit.getName() == "Zerg Larva Spawner")
			printf("(%i), ", iUnit.getCount());
	}
}

void UnitList::printBuilding() const
{
	for (CurrentUnit iUnit : vUnitList)
		if (iUnit.getActionName() == "CONSTRUCTING")
			printf(" %s: %d,", iUnit.getName().c_str(), iUnit.getTimer());
}
