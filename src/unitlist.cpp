// unitlist.cpp
#include "unitlist.h"

UnitList::UnitList()
{
	vActionList = new vector<string>;
}

UnitList::~UnitList()
{
	vActionList->clear();
	vUnitList.clear();
}

void UnitList::initUnit(Unit &unit, Action nextAction, Action idleAction, int num)
{
	for (int i=0; i<num; i++)
	{
		CurrentUnit newUnit(unit, nextAction, idleAction);
		vUnitList.push_back(newUnit);
	}
}

vector<string>* UnitList::update()
{
	for (CurrentUnit &iUnit : vUnitList)
	{
		string action = iUnit.update();
		if (action != "")
		{
			vActionList->push_back(action);
		}
	}
	
	vector<string>* tempActionList = vActionList;
	vActionList = new vector<string>;
	return tempActionList;
}
