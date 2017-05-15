// unittree.cpp
#include "unittree.h"
#include "string_alg.hpp"
#include <exception>

UnitTree::UnitTree()
{
	//
}

UnitTree::~UnitTree()
{
	vUnitList.clear();
}

void UnitTree::addUnit(string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided,
	string prereq, string prereq2, string buildsFrom, bool isAddon, bool reqAddon, bool morph)
{
	Unit *newUnit = new Unit(name, mineralCost, gasCost, buildTime, supplyCost, supplyProvided,
		prereq, prereq2, buildsFrom, isAddon, reqAddon, morph);
	vUnitList.push_back(*newUnit);
}

//return the unit
Unit *UnitTree::findUnit(string unitName)
{
	Unit *unitPtr = NULL;
	for (Unit &iUnit : vUnitList)
	{
		if (string_alg::lower_eq(iUnit.getName(), unitName))
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
		//economy
		addUnit("Terran SCV",50,0,300,1,0,"Terran Command Center","Terran Command Center");
		addUnit("Terran Command Center",400,0,1800,0,10,"Terran SCV","Terran SCV");
		addUnit("Terran Refinery",100,0,600,0,0,"Terran Command Center","Terran SCV");
		//ground units
		addUnit("Terran Marine",50,0,360,1,0,"Terran Barracks","Terran Barracks");
		addUnit("Terran Firebat",50,25,360,1,0,"Terran Academy","Terran Barracks");
		addUnit("Terran Ghost",25,75,750,1,0,"Terran Covert Ops","Terran Barracks","Terran Academy");
		addUnit("Terran Medic",50,25,450,1,0,"Terran Academy","Terran Academy");
		addUnit("Terran Vulture",75,0,450,2,0,"Terran Factory","Terran Factory");
		addUnit("Terran Goliath",100,50,600,2,0,"Terran Armory","Terran Factory");
		addUnit("Terran Siege Tank",150,100,750,2,0,"Terran Machine Shop","Terran Factory","",false,true);
		//air units
		addUnit("Terran Wraith",150,100,900,2,0,"Terran Starport","Terran Starport");
		addUnit("Terran Dropship",100,100,750,2,0,"Terran Control Tower","Terran Starport","",false,true);
		addUnit("Terran Valkyrie",250,125,750,3,0,"Terran Armory","Terran Starport","",false,true);
		addUnit("Terran Science Vessel",100,225,1200,2,0,"Terran Science Facility","Terran Starport","",false,true);
		addUnit("Terran Battlecruiser",50,0,2000,6,0,"Terran Physics Lab","Terran Starport","",false,true);
		//basic buildings
		addUnit("Terran Supply Depot",100,0,600,0,8,"Terran Command Center","Terran SCV");
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
		addUnit("Terran Comsat Station",50,50,600,0,0,"Terran Academy","Terran Command Center","",true);
		addUnit("Terran Machine Shop",50,50,600,0,0,"Terran Factory","Terran Factory","",true);
		addUnit("Terran Control Tower",50,50,600,0,0,"Terran Starport","Terran Starport","",true);
		addUnit("Terran Covert Ops",50,50,600,0,0,"Terran Science Facility","Terran Science Facility","",true);
		addUnit("Terran Physics Lab",50,50,600,0,0,"Terran Science Facility","Terran Science Facility","",true);
		addUnit("Terran Nuclear Silo",100,100,1200,0,0,"Terran Covert Ops","Terran Command Center","",true);
		addUnit("Terran Nuclear Missile",200,200,1500,8,0,"Terran Nuclear Silo","Terran Nuclear Silo");
		//upgrades/tech
		addUnit("Terran Stim Pack",100,100,1200,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran U-238 Shells",150,150,1500,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran Restoration",100,100,1200,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran Optical Flare",100,100,1200,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran Caduceus Reactor",150,150,2500,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran Siege Tech",150,150,1200,0,0,"Terran Machine Shop","Terran Machine Shop");
		addUnit("Terran Spider Mines",100,100,1200,0,0,"Terran Machine Shop","Terran Machine Shop");
		addUnit("Terran Ion Thrusters",100,100,1500,0,0,"Terran Machine Shop","Terran Machine Shop");
		addUnit("Terran Charon Boosters",100,100,2000,0,0,"Terran Armory","Terran Machine Shop");
		addUnit("Terran Cloaking Field",150,150,1500,0,0,"Terran Control Tower","Terran Control Tower");
		addUnit("Terran Apollo Reactor",200,200,2500,0,0,"Terran Control Tower","Terran Control Tower");
		addUnit("Terran EMP Shockwave",200,200,1800,0,0,"Terran Science Facility","Terran Science Facility");
		addUnit("Terran Irradiate",200,200,1200,0,0,"Terran Science Facility","Terran Science Facility");
		addUnit("Terran Titan Reactor",150,150,2500,0,0,"Terran Science Facility","Terran Science Facility");
		addUnit("Terran Personnel Cloaking",100,100,1200,0,0,"Terran Covert Ops","Terran Covert Ops");
		addUnit("Terran Lockdown",200,200,1500,0,0,"Terran Covert Ops","Terran Covert Ops");
		addUnit("Terran Ocular Implants",100,100,2500,0,0,"Terran Covert Ops","Terran Covert Ops");
		addUnit("Terran Moebius Reactor",150,150,2500,0,0,"Terran Covert Ops","Terran Covert Ops");
		addUnit("Terran Yamato Gun",100,100,1800,0,0,"Terran Physics Lab","Terran Physics Lab");
		addUnit("Terran Colossus Reactor",150,150,2500,0,0,"Terran Physics Lab","Terran Physics Lab");
		//numerical upgrades
		addUnit("Terran Infantry Weapons 1",100,100,4000,0,0,"Terran Engineering Bay","Terran Engineering Bay");
		addUnit("Terran Infantry Weapons 2",175,175,4480,0,0,"Terran Infantry Weapons 1","Terran Engineering Bay","Terran Science Facility");
		addUnit("Terran Infantry Weapons 3",250,250,4960,0,0,"Terran Infantry Weapons 2","Terran Engineering Bay","Terran Science Facility");
		addUnit("Terran Infantry Armor 1",100,100,4000,0,0,"Terran Engineering Bay","Terran Engineering Bay");
		addUnit("Terran Infantry Armor 2",175,175,4480,0,0,"Terran Infantry Armor 1","Terran Engineering Bay","Terran Science Facility");
		addUnit("Terran Infantry Armor 3",250,250,4960,0,0,"Terran Infantry Armor 2","Terran Engineering Bay","Terran Science Facility");
		addUnit("Terran Vehicle Weapons 1",100,100,4000,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran Vehicle Weapons 2",175,175,4480,0,0,"Terran Vehicle Weapons 1","Terran Armory","Terran Science Facility");
		addUnit("Terran Vehicle Weapons 3",250,250,4960,0,0,"Terran Vehicle Weapons 2","Terran Armory","Terran Science Facility");
		addUnit("Terran Vehicle Plating 1",100,100,4000,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran Vehicle Plating 2",175,175,4480,0,0,"Terran Vehicle Plating 1","Terran Armory","Terran Science Facility");
		addUnit("Terran Vehicle Plating 3",250,250,4960,0,0,"Terran Vehicle Plating 2","Terran Armory","Terran Science Facility");
		addUnit("Terran Ship Weapons 1",100,100,4000,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran Ship Weapons 2",175,175,4480,0,0,"Terran Ship Weapons 1","Terran Armory","Terran Science Facility");
		addUnit("Terran Ship Weapons 3",250,250,4960,0,0,"Terran Ship Weapons 2","Terran Armory","Terran Science Facility");
		addUnit("Terran Ship Plating 1",100,100,4000,0,0,"Terran Armory","Terran Armory");
		addUnit("Terran Ship Plating 2",175,175,4480,0,0,"Terran Ship Plating 1","Terran Armory","Terran Science Facility");
		addUnit("Terran Ship Plating 3",250,250,4960,0,0,"Terran Ship Plating 2","Terran Armory","Terran Science Facility");
	}
	if (race == 'z')
	{
		//economy buildings
		//addUnit("Zerg Drone",50,0,300,1,0,"Zerg Larva","Zerg Larva", false, false, true);
		//addUnit("Zerg Hatchery",300,0,1800,0,1,"Zerg Drone","Zerg Drone", false, false, true);
		//addUnit("Zerg Extractor",50,0,600,0,0,"Zerg Drone","Zerg Drone", false, false, true);
		////ground units
		//addUnit("Zerg Larva",50,0,300,1,0,"Zerg Hatchery","Zerg Hatchery");
		//addUnit("Zerg Zergling",50,0,300,1,0,"Zerg Spawning Pool","Zerg Larva", false, false, true);
		//addUnit("Zerg Hydralisk",50,0,300,1,0,"Zerg Hydralisk Den","Zerg Larva", false, false, true);
		//addUnit("Zerg Lurker",50,0,300,1,0,"Zerg Hydralisk Den","Zerg Hydralisk", false, false, true);
	}
}
