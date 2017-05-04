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

void UnitList::initUnit(Unit &unit, int num, string nextAction, int nextTimer, string idleAction, int idleTimer)
{
	for (int i=0; i<num; i++)
	{
		CurrentUnit newUnit(unit, nextAction, nextTimer, idleAction, idleTimer);
		vUnitList.push_back(newUnit);
	}
}

vector<string>* UnitList::update()
{
	for (CurrentUnit &unit : vUnitList)
	{
		string action = unit.update();
		if (action != "")
		{
			vActionList->push_back(action);
		}
	}
	
	vector<string>* tempActionList = vActionList;
	vActionList = new vector<string>;
	return tempActionList;
}
