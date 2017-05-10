// unittree.cpp
#include "unittree.h"
#include <exception>
#include <algorithm>

UnitTree::UnitTree()
{
	//
}

UnitTree::~UnitTree()
{
	vUnitList.clear();
}

void UnitTree::addUnit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided,
	string prereq, string buildsFrom, bool isAddon, bool reqAddon, bool morph)
{
	Unit *newUnit = new Unit(name, mineralCost, gasCost, buildTime, supplyCost, supplyProvided,
		prereq, buildsFrom, isAddon, reqAddon);
	vUnitList.push_back(*newUnit);
}

void UnitTree::init()
{
	//
}

//return the unit
Unit *UnitTree::findUnit(string unitName)
{
	transform(unitName.begin(), unitName.end(), unitName.begin(), ::tolower);
	Unit *unitPtr = NULL;
	for (Unit &iUnit : vUnitList)
	{
		string iUnitName = iUnit.getName();
		transform(iUnitName.begin(), iUnitName.end(), iUnitName.begin(), ::tolower);
		if (iUnitName == unitName)
		{
			unitPtr = &iUnit;
			break;
		}
	}
	return unitPtr;
}

//load unit data
//start each race with its worker unit first, main building second, gas building third
void UnitTree::loadRace(char race)
{
	if (race == 't')
	{
		//resource stuff
		addUnit("Terran SCV",50,0,300,1,0,"Terran Command Center","Terran Command Center");
		addUnit("Terran Command Center",400,0,1800,0,10,"Terran SCV","Terran SCV");
		addUnit("Terran Refinery",100,0,600,0,0,"Terran SCV","Terran SCV");
		//ground units
		addUnit("Terran Marine",50,0,360,1,0,"Terran Barracks","Terran Barracks");
		addUnit("Terran Firebat",50,25,360,1,0,"Terran Academy","Terran Barracks");
		addUnit("Terran Ghost",25,75,750,1,0,"Terran Covert Ops","Terran Barracks");
		addUnit("Terran Medic",50,25,450,1,0,"Terran Academy","Terran Academy");
		addUnit("Terran Vulture",75,0,450,2,0,"Terran Factory","Terran Factory");
		addUnit("Terran Goliath",100,50,600,2,0,"Terran Armory","Terran Factory");
		addUnit("Terran Siege Tank",150,100,750,2,0,"Terran Machine Shop","Terran Factory", false, true);
		//air units
		addUnit("Terran Wraith",150,100,900,2,0,"Terran Starport","Terran Starport");
		addUnit("Terran Dropship",100,100,750,2,0,"Terran Control Tower","Terran Starport", false, true);
		addUnit("Terran Valkyrie",250,125,750,3,0,"Terran Armory","Terran Starport", false, true);
		addUnit("Terran Science Vessel",100,225,1200,2,0,"Terran Science Facility","Terran Starport", false, true);
		addUnit("Terran Battlecruiser",50,0,2000,6,0,"Terran Physics Lab","Terran Starport", false, true);
		//basic buildings
		addUnit("Terran Supply Depot",100,0,600,0,8,"Terran SCV","Terran SCV");
		addUnit("Terran Barracks",150,0,1200,0,0,"Terran Command Center","Terran SCV");
		addUnit("Terran Engineering Bay",125,0,900,0,0,"Terran Command Center","Terran SCV");
		addUnit("Terran Academy",150,0,1200,0,0,"Terran Barracks","Terran SCV");
		addUnit("Terran Bunker",100,0,450,0,0,"Terran Barracks","Terran SCV");
		addUnit("Terran Missile Turret",75,0,450,0,0,"Terran Engineering Bay","Terran SCV");
		//advanced buildings
		addUnit("Terran Factory",200,100,1200,0,0,"Terran Barracks","Terran SCV");
		addUnit("Terran Armory",100,50,1200,0,0,"Terran Factory","Terran SCV");
		addUnit("Terran Starport",150,100,1050,0,0,"Terran Factory","Terran SCV");
		addUnit("Terran Science Facility",100,150,900,0,0,"Terran Starport","Terran SCV");
		//addons
		addUnit("Terran Comsat Station",50,50,600,0,0,"Terran Academy","Terran Command Center", true);
		addUnit("Terran Machine Shop",50,50,600,0,0,"Terran Factory","Terran Factory", true);
		addUnit("Terran Control Tower",50,50,600,0,0,"Terran Starport","Terran Starport", true);
		addUnit("Terran Covert Ops",50,50,600,0,0,"Terran Science Facility","Terran Science Facility", true);
		addUnit("Terran Physics Lab",50,50,600,0,0,"Terran Science Facility","Terran Science Facility", true);
		addUnit("Terran Nuclear Silo",100,100,1200,0,0,"Terran Covert Ops","Terran Command Center", true);
	}
	init();
}

