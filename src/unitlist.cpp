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

void UnitList::addUnit(Unit &unit, Action nextAction, Action idleAction)
{
	CurrentUnit newUnit(unit, nextAction, idleAction);
	vUnitList.push_back(newUnit);
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
		//warp it in if builds from probe
		if (unit.getBuildsFromName() == "Protoss Probe")
			return true;

		//otherwise find an idle worker
		CurrentUnit *workerPtr = findWorker();
		if (workerPtr != NULL)
		{
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
		for (CurrentUnit &iCurrentUnit : vUnitList)
		{
			if (iCurrentUnit.getName() == unit.getBuildsFromName())
			{
				//continue if unit requires addon but building does not have one
				if (unit.reqAddon() && !iCurrentUnit.hasAddon())
					continue;
				if (unit.isAddon() && iCurrentUnit.hasAddon())
					continue;
				if (iCurrentUnit.isIdle())
				{
					iCurrentUnit.gotoAction(Action("BUILDING", unit));
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
CurrentUnit *UnitList::findWorker(string action)
{
	CurrentUnit *workerPtr = NULL;
	int workerFrame = -1;
	for (CurrentUnit &iCurrentUnit : vUnitList)
	{
		if (iCurrentUnit.getActionName() == action)
		{
			if (iCurrentUnit.getTimer() > workerFrame)
			{
				workerPtr = &iCurrentUnit;
				workerFrame = iCurrentUnit.getTimer();
			}
		}
	}
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
	if (unit.getName() == mWorkerName)
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit), Action("GATHER MINERALS", mMineralRate)));
	else if (unit.getBuildsFromName() == "Protoss Probe")
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit.getBuildTime() + 80, unit)));
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
}

void UnitList::printBuilding() const
{
	for (CurrentUnit iUnit : vUnitList)
		if (iUnit.getActionName() == "CONSTRUCTING")
			printf(" %s: %d,", iUnit.getName().c_str(), iUnit.getTimer());
}
