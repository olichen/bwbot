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
	mMineralRate = mineralRate;
}

void UnitList::addUnit(Unit &unit, Action nextAction, Action idleAction)
{
	CurrentUnit newUnit(unit, nextAction, idleAction);
	vUnitList.push_back(newUnit);
}

bool UnitList::tryToBuild(Unit &unit)
{
	if (unit.getBuildsFromName() == mWorkerName)
	{
		CurrentUnit *workerPtr = NULL;
		int workerFrame = 9999;
		for (CurrentUnit &iCurrentUnit : vUnitList)
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
				if (iCurrentUnit.isIdle())
				{
					iCurrentUnit.addNextAction(Action("BUILDING", unit));
					return true;
				}
			}
		}
	}
	return false;
}

void UnitList::buildUnit(Unit &unit)
{
	vUnitList.push_back(CurrentUnit(unit, Action("CONSTRUCTING", unit)));
}

void UnitList::spawnUnit(Unit &unit)
{
	vUnitList.push_back(CurrentUnit(unit));
}

void UnitList::update(vector<Action> &actionList)
{
	for (CurrentUnit &iUnit : vUnitList)
	{
		iUnit.update(actionList);
	}
}

int UnitList::minerCount()
{
	int count = 0;
	for (CurrentUnit &iUnit : vUnitList)
	{
		if (iUnit.getActionName() == "GATHER MINERALS")
		{
			count++;
		}
	}
	return count;
}

int UnitList::gasMinerCount()
{
	int count = 0;
	for (CurrentUnit &iUnit : vUnitList)
	{
		if (iUnit.getActionName() == "GATHER GAS")
		{
			count++;
		}
	}
	return count;
}
