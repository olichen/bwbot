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
	clear();
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
		addUnit("Terran Stim Pack",100,100,1200,0,0,"Terran Academy","Terran Academy");
		addUnit("Terran U-238 Shells",150,150,1500,0,0,"Terran Academy","Terran Academy");
		addUnit("Terran Restoration",100,100,1200,0,0,"Terran Academy","Terran Academy");
		addUnit("Terran Optical Flare",100,100,1200,0,0,"Terran Academy","Terran Academy");
		addUnit("Terran Caduceus Reactor",150,150,2500,0,0,"Terran Academy","Terran Academy");
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
	if (race == 'p')
	{
		//economy
		addUnit("Protoss Probe",50,0,300,1,0,"Protoss Nexus","Protoss Nexus");
		addUnit("Protoss Nexus",400,0,1800,0,9,"Protoss Probe","Protoss Probe");
		addUnit("Protoss Assimilator",100,0,600,0,0,"Protoss Nexus","Protoss Probe");
		//ground units
		addUnit("Protoss Zealot",100,0,600,2,0,"Protoss Gateway","Protoss Gateway");
		addUnit("Protoss Dragoon",125,50,750,2,0,"Protoss Cybernetics Core","Protoss Gateway");
		addUnit("Protoss High Templar",50,150,750,2,0,"Protoss Templar Archives","Protoss Gateway");
		addUnit("Protoss Dark Templar",125,100,750,2,0,"Protoss Templar Archives","Protoss Gateway");
		addUnit("Protoss Archon",0,0,300,0,0,"Protoss High Templar","Protoss High Templar");
		addUnit("Protoss Dark Archon",0,0,300,0,0,"Protoss Dark Templar","Protoss Dark Templar");
		addUnit("Protoss Reaver",200,100,1050,4,0,"Protoss Robotics Support Bay","Protoss Robotics Facility");
		addUnit("Protoss Scarab",15,0,105,0,0,"Protoss Reaver","Protoss Reaver");
		//air units
		addUnit("Protoss Scout",275,125,1200,3,0,"Protoss Stargate","Protoss Stargate");
		addUnit("Protoss Corsair",150,100,600,2,0,"Protoss Stargate","Protoss Stargate");
		addUnit("Protoss Arbiter",100,350,2400,4,0,"Protoss Arbiter Tribunal","Protoss Stargate");
		addUnit("Protoss Carrier",350,200,2100,6,0,"Protoss Fleet Beacon","Protoss Stargate");
		addUnit("Protoss Interceptor",25,0,300,3,0,"Protoss Carrier","Protoss Carrier");
		addUnit("Protoss Observer",25,75,600,1,0,"Protoss Observatory","Protoss Robotics Facility");
		addUnit("Protoss Shuttle",200,0,900,2,0,"Protoss Robotics Facility","Protoss Robotics Facility");
		//basic buildings
		addUnit("Protoss Pylon",100,0,450,0,8,"Protoss Probe","Protoss Probe");
		addUnit("Protoss Gateway",150,0,900,0,0,"Protoss Nexus","Protoss Probe", "Protoss Pylon");
		addUnit("Protoss Forge",150,0,600,0,0,"Protoss Nexus","Protoss Probe");
		addUnit("Protoss Photon Cannon",150,0,750,0,0,"Protoss Forge","Protoss Probe");
		addUnit("Protoss Cybernetics Core",200,0,900,0,0,"Protoss Gateway","Protoss Probe");
		addUnit("Protoss Shield Battery",100,0,450,0,0,"Protoss Gateway","Protoss Probe");
		//advanced buildings
		addUnit("Protoss Robotics Facility",200,200,1200,0,0,"Protoss Cybernetics Core","Protoss Probe");
		addUnit("Protoss Robotics Support Bay",150,100,450,0,0,"Protoss Robotics Facility","Protoss Probe");
		addUnit("Protoss Observatory",50,100,450,0,0,"Protoss Robotics Facility","Protoss Probe");
		addUnit("Protoss Stargate",150,150,1050,0,0,"Protoss Cybernetics Core","Protoss Probe");
		addUnit("Protoss Fleet Beacon",300,200,900,0,0,"Protoss Stargate","Protoss Probe");
		addUnit("Protoss Arbiter Tribunal",200,150,900,0,0,"Protoss Stargate","Protoss Probe","Protoss Templar Archives");
		addUnit("Protoss Citadel Of Adun",150,100,900,0,0,"Protoss Cybernetics Core","Protoss Probe");
		addUnit("Protoss Templar Archives",150,200,900,0,0,"Protoss Citadel Of Adun","Protoss Probe");
		//upgrades/tech
		addUnit("Protoss Singularity Charge",150,150,2500,0,0,"Protoss Cybernetics Core","Protoss Cybernetics Core");
		addUnit("Protoss Leg Enhancements",150,150,2000,0,0,"Protoss Citadel Of Adun","Protoss Citadel Of Adun");
		addUnit("Protoss Scarab Damage",200,200,2500,0,0,"Protoss Robotics Support Bay","Protoss Robotics Support Bay");
		addUnit("Protoss Reaver Capacity",200,200,2500,0,0,"Protoss Robotics Support Bay","Protoss Robotics Support Bay");
		addUnit("Protoss Gravitic Drive",200,200,2500,0,0,"Protoss Robotics Support Bay","Protoss Robotics Support Bay");
		addUnit("Protoss Sensor Array",150,150,2000,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit("Protoss Gravitic Boosters",150,150,2000,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit("Protoss Apial Sensors",100,100,2500,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit("Protoss Gravitic Thrusters",200,200,2500,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit("Protoss Carrier Capacity",100,100,1500,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit("Protoss Disruption Web",200,200,1200,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit("Protoss Argus Jewel",100,100,2500,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit("Protoss Recall",150,150,1800,0,0,"Protoss Arbiter Tribunal","Protoss Arbiter Tribunal");
		addUnit("Protoss Stasis Field",150,150,1500,0,0,"Protoss Arbiter Tribunal","Protoss Arbiter Tribunal");
		addUnit("Protoss Khaydarin Core",150,150,2500,0,0,"Protoss Arbiter Tribunal","Protoss Arbiter Tribunal");
		addUnit("Protoss Psionic Storm",200,200,1800,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit("Protoss Hallucination",150,150,1200,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit("Protoss Khaydarin Amulet",150,150,2500,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit("Protoss Maelstrom",100,100,1500,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit("Protoss Mind Control",200,200,1800,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit("Protoss Argus Talisman",150,150,2500,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		//numerical upgrades
		addUnit("Protoss Ground Weapons 1",100,100,4000,0,0,"Protoss Forge","Protoss Forge");
		addUnit("Protoss Ground Weapons 2",175,175,4480,0,0,"Protoss Ground Weapons 1","Protoss Forge","Protoss Templar Archives");
		addUnit("Protoss Ground Weapons 3",250,250,4960,0,0,"Protoss Ground Weapons 2","Protoss Forge","Protoss Templar Archives");
		addUnit("Protoss Ground Armor 1",100,100,4000,0,0,"Protoss Forge","Protoss Forge");
		addUnit("Protoss Ground Armor 2",175,175,4480,0,0,"Protoss Ground Armor 1","Protoss Forge","Protoss Templar Archives");
		addUnit("Protoss Ground Armor 3",250,250,4960,0,0,"Protoss Ground Armor 2","Protoss Forge","Protoss Templar Archives");
		addUnit("Protoss Plasma Shields 1",200,200,4000,0,0,"Protoss Forge","Protoss Forge");
		addUnit("Protoss Plasma Shields 2",300,300,4480,0,0,"Protoss Plasma Shields 1","Protoss Forge","Protoss Cybernetics Core");
		addUnit("Protoss Plasma Shields 3",400,400,4960,0,0,"Protoss Plasma Shields 2","Protoss Forge","Protoss Cybernetics Core");
		addUnit("Protoss Air Weapons 1",100,100,4000,0,0,"Protoss Cybernetics Core","Protoss Cybernetics Core");
		addUnit("Protoss Air Weapons 2",175,175,4480,0,0,"Protoss Air Weapons 1","Protoss Cybernetics Core","Protoss Fleet Beacon");
		addUnit("Protoss Air Weapons 3",250,250,4960,0,0,"Protoss Air Weapons 2","Protoss Cybernetics Core","Protoss Fleet Beacon");
		addUnit("Protoss Air Armor 1",100,100,4000,0,0,"Protoss Cybernetics Core","Protoss Cybernetics Core");
		addUnit("Protoss Air Armor 2",175,175,4480,0,0,"Protoss Air Armor 1","Protoss Cybernetics Core","Protoss Fleet Beacon");
		addUnit("Protoss Air Armor 3",250,250,4960,0,0,"Protoss Air Armor 2","Protoss Cybernetics Core","Protoss Fleet Beacon");
	}
	if (race == 'z')
	{
		//economy buildings
		addUnit("Zerg Drone",50,0,300,1,0,"Zerg Larva","Zerg Larva","",false,false,true);
		addUnit("Zerg Hatchery",300,0,1800,0,1,"Zerg Drone","Zerg Drone","",false,false,true);
		addUnit("Zerg Extractor",50,0,600,0,0,"Zerg Hatchery","Zerg Drone","",false,false,true);
		addUnit("Zerg Larva Spawner",0,0,0,0,0,"Zerg Hatchery","Zerg Hatchery");
		//ground units
		addUnit("Zerg Larva",0,0,342,0,0,"Zerg Larva Spawner","Zerg Larva Spawner");
		addUnit("Zerg Zergling",50,0,420,1,0,"Zerg Spawning Pool","Zerg Larva","",false,false,true);
		addUnit("Zerg Hydralisk",75,25,420,1,0,"Zerg Hydralisk Den","Zerg Larva","",false,false,true);
		addUnit("Zerg Lurker",50,100,600,2,0,"Zerg Lurker Aspect","Zerg Hydralisk","",false,false,true);
		addUnit("Zerg Ultralisk",200,200,900,4,0,"Zerg Ultralisk Cavern","Zerg Larva","",false,false,true);
		addUnit("Zerg Defiler",50,150,750,2,0,"Zerg Defiler Mound","Zerg Larva","",false,false,true);
		//air units
		addUnit("Zerg Overlord",100,0,600,0,8,"Zerg Larva","Zerg Larva","",false,false,true);
		addUnit("Zerg Mutalisk",100,100,600,2,0,"Zerg Spire","Zerg Larva","",false,false,true);
		addUnit("Zerg Scourge",25,75,450,1,0,"Zerg Spire","Zerg Larva","",false,false,true);
		addUnit("Zerg Queen",100,100,750,2,0,"Zerg Queen's Nest","Zerg Larva","",false,false,true);
		addUnit("Zerg Guardian",50,100,600,2,0,"Zerg Greater Spire","Zerg Mutalisk","",false,false,true);
		addUnit("Zerg Devourer",150,50,600,2,0,"Zerg Greater Spire","Zerg Mutalisk","",false,false,true);
		//basic buildings
		addUnit("Zerg Lair",150,100,1500,0,1,"Zerg Spawning Pool","Zerg Hatchery","",true);
		addUnit("Zerg Hive",200,150,1800,0,1,"Zerg Queen's Nest","Zerg Lair","",true);
		addUnit("Zerg Spawning Pool",200,0,1200,0,0,"Zerg Hatchery","Zerg Drone","",false,false,true);
		addUnit("Zerg Evolution Chamber",75,0,600,0,0,"Zerg Hatchery","Zerg Drone","",false,false,true);
		addUnit("Zerg Hydralisk Den",100,50,600,0,0,"Zerg Spawning Pool","Zerg Drone","",false,false,true);
		addUnit("Zerg Creep Colony",75,0,300,0,0,"Zerg Hatchery","Zerg Drone","",false,false,true);
		addUnit("Zerg Sunken Colony",50,0,300,0,0,"Zerg Spawning Pool","Zerg Creep Colony","",false,false,true);
		addUnit("Zerg Spore Colony",50,0,300,0,0,"Zerg Evolution Chamber","Zerg Creep Colony","",false,false,true);
		//advanced buildings
		addUnit("Zerg Spire",200,150,1800,0,0,"Zerg Lair","Zerg Drone","",false,false,true);
		addUnit("Zerg Greater Spire",100,150,1800,0,0,"Zerg Hive","Zerg Spire","",true);
		addUnit("Zerg Queen's Nest",150,100,900,0,0,"Zerg Lair","Zerg Drone","",false,false,true);
		addUnit("Zerg Ultralisk Cavern",150,200,1200,0,0,"Zerg Hive","Zerg Drone","",false,false,true);
		addUnit("Zerg Defiler Mound",100,100,900,0,0,"Zerg Hive","Zerg Drone","",false,false,true);
		addUnit("Zerg Nydus Canal",150,0,600,0,0,"Zerg Hive","Zerg Drone","",false,false,true);
		//upgrades/tech
		addUnit("Zerg Burrowing",100,100,1200,0,0,"Zerg Hatchery","Zerg Hatchery");
		addUnit("Zerg Ventral Sacs",200,200,2400,0,0,"Zerg Lair","Zerg Hatchery");
		addUnit("Zerg Antennae",150,150,2000,0,0,"Zerg Lair","Zerg Hatchery");
		addUnit("Zerg Pneumatized Carapace",150,150,2000,0,0,"Zerg Lair","Zerg Hatchery");
		addUnit("Zerg Metabolic Boost",100,100,1500,0,0,"Zerg Spawning Pool","Zerg Spawning Pool");
		addUnit("Zerg Adrenal Glands",200,200,1500,0,0,"Zerg Hive","Zerg Spawning Pool");
		addUnit("Zerg Muscular Augments",150,150,1500,0,0,"Zerg Hydralisk Den","Zerg Hydralisk Den");
		addUnit("Zerg Grooved Spines",150,150,1500,0,0,"Zerg Hydralisk Den","Zerg Hydralisk Den");
		addUnit("Zerg Lurker Aspect",200,200,1800,0,0,"Zerg Lair","Zerg Hydralisk Den");
		addUnit("Zerg Ensnare",100,100,1200,0,0,"Zerg Queen's Nest","Zerg Queen's Nest");
		addUnit("Zerg Spawn Broodling",150,150,1200,0,0,"Zerg Queen's Nest","Zerg Queen's Nest");
		addUnit("Zerg Gamete Meiosis",100,100,2500,0,0,"Zerg Queen's Nest","Zerg Queen's Nest");
		addUnit("Zerg Anabolic Synthesis",200,200,2000,0,0,"Zerg Ultralisk Cavern","Zerg Ultralisk Cavern");
		addUnit("Zerg Chitinous Plating",150,150,2000,0,0,"Zerg Ultralisk Cavern","Zerg Ultralisk Cavern");
		addUnit("Zerg Consume",100,100,1500,0,0,"Zerg Defiler Mound","Zerg Defiler Mound");
		addUnit("Zerg Plague",200,200,1500,0,0,"Zerg Defiler Mound","Zerg Defiler Mound");
		addUnit("Zerg Metasynaptic Node",150,150,2500,0,0,"Zerg Defiler Mound","Zerg Defiler Mound");
		//numerical upgrades
		addUnit("Zerg Melee Attacks 1",100,100,4000,0,0,"Zerg Evolution Chamber","Zerg Evolution Chamber");
		addUnit("Zerg Melee Attacks 2",150,150,4480,0,0,"Zerg Melee Attacks 1","Zerg Evolution Chamber","Zerg Lair");
		addUnit("Zerg Melee Attacks 3",200,200,4960,0,0,"Zerg Melee Attacks 2","Zerg Evolution Chamber","Zerg Hive");
		addUnit("Zerg Missile Attacks 1",100,100,4000,0,0,"Zerg Evolution Chamber","Zerg Evolution Chamber");
		addUnit("Zerg Missile Attacks 2",150,150,4480,0,0,"Zerg Missile Attacks 1","Zerg Evolution Chamber","Zerg Lair");
		addUnit("Zerg Missile Attacks 3",200,200,4960,0,0,"Zerg Missile Attacks 2","Zerg Evolution Chamber","Zerg Hive");
		addUnit("Zerg Carapace 1",150,150,4000,0,0,"Zerg Evolution Chamber","Zerg Evolution Chamber");
		addUnit("Zerg Carapace 2",225,225,4480,0,0,"Zerg Carapace 1","Zerg Evolution Chamber","Zerg Lair");
		addUnit("Zerg Carapace 3",300,300,4960,0,0,"Zerg Carapace 2","Zerg Evolution Chamber","Zerg Hive");
		addUnit("Zerg Flyer Attacks 1",100,100,4000,0,0,"Zerg Spire","Zerg Spire");
		addUnit("Zerg Flyer Attacks 2",175,175,4480,0,0,"Zerg Flyer Attacks 1","Zerg Spire","Zerg Lair");
		addUnit("Zerg Flyer Attacks 3",250,250,4960,0,0,"Zerg Flyer Attacks 2","Zerg Spire","Zerg Hive");
		addUnit("Zerg Flyer Carapace 1",150,150,4000,0,0,"Zerg Spire","Zerg Spire");
		addUnit("Zerg Flyer Carapace 2",225,225,4480,0,0,"Zerg Flyer Carapace 1","Zerg Spire","Zerg Lair");
		addUnit("Zerg Flyer Carapace 3",300,300,4960,0,0,"Zerg Flyer Carapace 2","Zerg Spire","Zerg Hive");
	}
}
