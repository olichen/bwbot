// unitlist.cpp
#include "unitlist.h"

UnitList::UnitList()
{
	//
}

void UnitList::initUnit(Unit &unit, Action nextAction, Action idleAction)
{
	CurrentUnit newUnit(unit, nextAction, idleAction);
	vUnitList.push_back(newUnit);
}

void UnitList::update(vector<Action> &actionList)
{
	for (CurrentUnit &iUnit : vUnitList)
	{
		iUnit.update(actionList);
	}
}
