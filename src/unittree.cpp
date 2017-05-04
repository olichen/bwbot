// unittree.cpp
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

//return the unit
Unit &UnitTree::findUnit(string unitName)
{
	for (Unit &unit : vUnitList)
	{
		if (unit.getName() == unitName)
		{
			return unit;
		}
	}
}

//load unit data
//start each race with its worker unit first!!
void UnitTree::loadRace(char race)
{
	if (race == 't')
	{
		addUnit("Terran SCV",50,0,300,1,0,"Terran Command Center","Terran Command Center");
		addUnit("Terran Command Center",400,0,1800,0,10,"Terran SCV","Terran SCV");
	}
	init();
}

