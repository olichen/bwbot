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
	for (Unit &iUnit : vUnitList)
	{
		Unit *prereq = NULL;
		Unit *buildsFrom = NULL;

		for (Unit &iFindUnit : vUnitList)
		{
			if (iUnit.getPrereqName() == iFindUnit.getName())
			{
				prereq = &iFindUnit;
			}
			if (iUnit.getBuildsFromName() == iFindUnit.getName())
			{
				buildsFrom = &iFindUnit;
			}
		}
		iUnit.init(*prereq, *buildsFrom);
	}
}

//return the unit
Unit &UnitTree::findUnit(string unitName)
{
	for (Unit &iUnit : vUnitList)
	{
		if (iUnit.getName() == unitName)
		{
			return iUnit;
		}
	}
	throw "Unit " + unitName + " not found.";
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

