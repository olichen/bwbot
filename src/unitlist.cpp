// unitlist.cpp
#include "unitlist.h"

UnitList::UnitList()
	: mMineralRate(177), mGasRate(111)
{
	//
}

void UnitList::init(string workerName)
{
	mWorkerName = workerName;
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

void UnitList::setGasRate(int gasRate)
{
	if (mMineralRate != gasRate)
	{
		for (CurrentUnit &iCurrentUnit : vUnitList)
		{
			if (iCurrentUnit.getIdleActionName() == "GATHER GAS")
			{
				iCurrentUnit.setIdleActionTimer(gasRate);
				mGasRate = gasRate;
			}
		}
	}
}

void UnitList::addUnit(Unit &unit, Action nextAction, Action idleAction)
{
	CurrentUnit newUnit(unit, nextAction, idleAction);
	vUnitList.push_back(newUnit);
}

bool UnitList::tryToBuild(Unit &unit)
{
	if (!hasUnit(unit.getPrereqName()))
		return false;
	if (unit.reqAddon())
		return false;
	if (unit.getBuildsFromName() == mWorkerName)
	{
		CurrentUnit *workerPtr = findWorker();
		if (workerPtr != NULL)
		{
			workerPtr->gotoAction(Action("BUILDING", unit));
			return true;
		}
	}
	else
	{
		for (CurrentUnit &iCurrentUnit : vUnitList)
		{
			if (iCurrentUnit.getName() == unit.getBuildsFromName())
			{
				if (unit.reqAddon())
					if (!iCurrentUnit.hasAddon())
						return false;
				if (iCurrentUnit.isIdle())
				{
					iCurrentUnit.addNextAction(Action("BUILDING", unit));
					if (unit.isAddon())
						iCurrentUnit.addAddon();
					return true;
				}
			}
		}
	}
	return false;
}

bool UnitList::hasUnit(const string unitName) const
{
	for (CurrentUnit iCurrentUnit : vUnitList)
		if (iCurrentUnit.getName() == unitName)
			if (iCurrentUnit.getActionName() != "CONSTRUCTING")
				return true;
	return false;
}

//find the most idle worker (whoever is most done with mining)
CurrentUnit *UnitList::findWorker()
{
	CurrentUnit *workerPtr = NULL;
	int workerFrame = 1;
	for (CurrentUnit &iCurrentUnit : vUnitList)
	{
		if (iCurrentUnit.getActionName() == "GATHER MINERALS")
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

void UnitList::addGasWorker(int number)
{
	int gasInit = mGasRate;
	for (int i=0; i<number; i++)
	{
		CurrentUnit *workerPtr = findWorker();
		workerPtr->gotoAction(Action("GATHER GAS", gasInit));
		workerPtr->setIdleAction(Action("GATHER GAS", mGasRate));
		gasInit += 37;
	}
}

void UnitList::scout()
{
	findWorker()->gotoAction(Action("SCOUT",999999));
}

void UnitList::buildUnit(Unit &unit)
{
	if (unit.getName() == mWorkerName)
		vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit), Action("GATHER MINERALS", mMineralRate)));
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

void UnitList::printBuilding() const
{
	for (CurrentUnit iUnit : vUnitList)
		if (iUnit.getActionName() == "CONSTRUCTING")
			printf(" %s: %d,", iUnit.getName().c_str(), iUnit.getTimer());
}
