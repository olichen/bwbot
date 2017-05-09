// unitlist.cpp
#include "unitlist.h"

UnitList::UnitList()
	: mMineralRate(177), mGasRate(111)
{
	//
}

void UnitList::init(string workerName, string gasName)
{
	mWorkerName = workerName;
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

//find the most idle worker (whoever is most done with mining)
CurrentUnit *UnitList::findWorker()
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
	return workerPtr;
}

void UnitList::addGasWorker(int number)
{
	int gasInit = 74;
	for (int i=0; i<number; i++)
	{
		CurrentUnit *workerPtr = findWorker();
		workerPtr->gotoAction(Action("GATHER GAS", gasInit));
		workerPtr->setIdleAction(Action("GATHER GAS", mGasRate));
		gasInit += 37;
	}
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
