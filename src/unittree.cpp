#include "unittree.h"

UnitTree::UnitTree()
{
	//
}

UnitTree::~UnitTree()
{
	vUnitList.clear();
}

void UnitTree::addUnit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided, string prereq, string buildsFrom)
{
	Unit *newUnit = new Unit(name, mineralCost, gasCost, buildTime, supplyCost, supplyProvided, prereq, buildsFrom);
	vUnitList.push_back(*newUnit);
}

void UnitTree::init()
{
	for (Unit &unit : vUnitList)
	{
		Unit *prereq, *buildsFrom;
		for (Unit &findUnit : vUnitList)
		{
			if (unit.findPrereq() == findUnit.getName())
			{
				prereq = &findUnit;
			}
			if (unit.findBuildsFrom() == findUnit.getName())
			{
				buildsFrom = &findUnit;
			}
		}
		unit.init(*prereq, *buildsFrom);
	}
}
