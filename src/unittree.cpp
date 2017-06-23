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

void UnitTree::addUnit(int id, string name, int mineralCost, int gasCost, int buildTime, int supplyCost, int supplyProvided,
	string prereq, string prereq2, string buildsFrom, bool isAddon, bool reqAddon, bool morph)
{
	Unit *newUnit = new Unit(id, name, mineralCost, gasCost, buildTime, supplyCost, supplyProvided,
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
		addUnit(1211,"Terran SCV",50,0,300,1,0,"Terran Command Center","Terran Command Center");
		addUnit(1111,"Terran Command Center",400,0,1800,0,10,"Terran SCV","Terran SCV");
		addUnit(1113,"Terran Refinery",100,0,600,0,0,"Terran Command Center","Terran SCV");
		//ground units
		addUnit(1212,"Terran Marine",50,0,360,1,0,"Terran Barracks","Terran Barracks");
		addUnit(1213,"Terran Firebat",50,25,360,1,0,"Terran Academy","Terran Barracks");
		addUnit(1214,"Terran Ghost",25,75,750,1,0,"Terran Covert Ops","Terran Barracks","Terran Academy");
		addUnit(1215,"Terran Medic",50,25,450,1,0,"Terran Academy","Terran Barracks");
		addUnit(1221,"Terran Vulture",75,0,450,2,0,"Terran Factory","Terran Factory");
		addUnit(1222,"Terran Goliath",100,50,600,2,0,"Terran Armory","Terran Factory");
		addUnit(1223,"Terran Siege Tank",150,100,750,2,0,"Terran Machine Shop","Terran Factory","",false,true);
		//air units
		addUnit(1231,"Terran Wraith",150,100,900,2,0,"Terran Starport","Terran Starport");
		addUnit(1232,"Terran Dropship",100,100,750,2,0,"Terran Control Tower","Terran Starport","",false,true);
		addUnit(1233,"Terran Valkyrie",250,125,750,3,0,"Terran Armory","Terran Starport","",false,true);
		addUnit(1234,"Terran Science Vessel",100,225,1200,2,0,"Terran Science Facility","Terran Starport","",false,true);
		addUnit(1235,"Terran Battlecruiser",50,0,2000,6,0,"Terran Physics Lab","Terran Starport","",false,true);
		//basic buildings
		addUnit(1112,"Terran Supply Depot",100,0,600,0,8,"Terran Command Center","Terran SCV");
		addUnit(1121,"Terran Barracks",150,0,1200,0,0,"Terran Command Center","Terran SCV");
		addUnit(1122,"Terran Engineering Bay",125,0,900,0,0,"Terran Command Center","Terran SCV");
		addUnit(1131,"Terran Academy",150,0,1200,0,0,"Terran Barracks","Terran SCV");
		addUnit(1132,"Terran Bunker",100,0,450,0,0,"Terran Barracks","Terran SCV");
		addUnit(1123,"Terran Missile Turret",75,0,450,0,0,"Terran Engineering Bay","Terran SCV");
		//advanced buildings
		addUnit(1114,"Terran Factory",200,100,1200,0,0,"Terran Barracks","Terran SCV");
		addUnit(1115,"Terran Armory",100,50,1200,0,0,"Terran Factory","Terran SCV");
		addUnit(1124,"Terran Starport",150,100,1050,0,0,"Terran Factory","Terran SCV");
		addUnit(1116,"Terran Science Facility",100,150,900,0,0,"Terran Starport","Terran SCV");
		//addons
		addUnit(1134,"Terran Comsat Station",50,50,600,0,0,"Terran Academy","Terran Command Center","",true);
		addUnit(1126,"Terran Machine Shop",50,50,600,0,0,"Terran Factory","Terran Factory","",true);
		addUnit(1127,"Terran Control Tower",50,50,600,0,0,"Terran Starport","Terran Starport","",true);
		addUnit(1137,"Terran Covert Ops",50,50,600,0,0,"Terran Science Facility","Terran Science Facility","",true);
		addUnit(1136,"Terran Physics Lab",50,50,600,0,0,"Terran Science Facility","Terran Science Facility","",true);
		addUnit(1135,"Terran Nuclear Silo",100,100,1200,0,0,"Terran Covert Ops","Terran Command Center","",true);
		addUnit(1217,"Terran Nuclear Missile",200,200,1500,8,0,"Terran Nuclear Silo","Terran Nuclear Silo");
		//upgrades/tech
		addUnit(1311,"Terran U-238 Shells",150,150,1500,0,0,"Terran Academy","Terran Academy");
		addUnit(1312,"Terran Stim Pack",100,100,1200,0,0,"Terran Academy","Terran Academy");
		addUnit(1313,"Terran Restoration",100,100,1200,0,0,"Terran Academy","Terran Academy");
		addUnit(1314,"Terran Optical Flare",100,100,1200,0,0,"Terran Academy","Terran Academy");
		addUnit(1315,"Terran Caduceus Reactor",150,150,2500,0,0,"Terran Academy","Terran Academy");
		addUnit(1321,"Terran Ion Thrusters",100,100,1500,0,0,"Terran Machine Shop","Terran Machine Shop");
		addUnit(1322,"Terran Spider Mines",100,100,1200,0,0,"Terran Machine Shop","Terran Machine Shop");
		addUnit(1323,"Terran Siege Tech",150,150,1200,0,0,"Terran Machine Shop","Terran Machine Shop");
		addUnit(1324,"Terran Charon Boosters",100,100,2000,0,0,"Terran Armory","Terran Machine Shop");
		addUnit(1316,"Terran Cloaking Field",150,150,1500,0,0,"Terran Control Tower","Terran Control Tower");
		addUnit(1317,"Terran Apollo Reactor",200,200,2500,0,0,"Terran Control Tower","Terran Control Tower");
		addUnit(1331,"Terran EMP Shockwave",200,200,1800,0,0,"Terran Science Facility","Terran Science Facility");
		addUnit(1332,"Terran Irradiate",200,200,1200,0,0,"Terran Science Facility","Terran Science Facility");
		addUnit(1333,"Terran Titan Reactor",150,150,2500,0,0,"Terran Science Facility","Terran Science Facility");
		addUnit(1334,"Terran Lockdown",200,200,1500,0,0,"Terran Covert Ops","Terran Covert Ops");
		addUnit(1335,"Terran Personnel Cloaking",100,100,1200,0,0,"Terran Covert Ops","Terran Covert Ops");
		addUnit(1336,"Terran Ocular Implants",100,100,2500,0,0,"Terran Covert Ops","Terran Covert Ops");
		addUnit(1337,"Terran Moebius Reactor",150,150,2500,0,0,"Terran Covert Ops","Terran Covert Ops");
		addUnit(1326,"Terran Yamato Gun",100,100,1800,0,0,"Terran Physics Lab","Terran Physics Lab");
		addUnit(1327,"Terran Colossus Reactor",150,150,2500,0,0,"Terran Physics Lab","Terran Physics Lab");
		//numerical upgrades
		addUnit(1411,"Terran Infantry Weapons 1",100,100,4000,0,0,"Terran Engineering Bay","Terran Engineering Bay");
		addUnit(1421,"Terran Infantry Weapons 2",175,175,4480,0,0,"Terran Infantry Weapons 1","Terran Engineering Bay","Terran Science Facility");
		addUnit(1431,"Terran Infantry Weapons 3",250,250,4960,0,0,"Terran Infantry Weapons 2","Terran Engineering Bay","Terran Science Facility");
		addUnit(1412,"Terran Infantry Armor 1",100,100,4000,0,0,"Terran Engineering Bay","Terran Engineering Bay");
		addUnit(1422,"Terran Infantry Armor 2",175,175,4480,0,0,"Terran Infantry Armor 1","Terran Engineering Bay","Terran Science Facility");
		addUnit(1432,"Terran Infantry Armor 3",250,250,4960,0,0,"Terran Infantry Armor 2","Terran Engineering Bay","Terran Science Facility");
		addUnit(1413,"Terran Vehicle Weapons 1",100,100,4000,0,0,"Terran Armory","Terran Armory");
		addUnit(1423,"Terran Vehicle Weapons 2",175,175,4480,0,0,"Terran Vehicle Weapons 1","Terran Armory","Terran Science Facility");
		addUnit(1433,"Terran Vehicle Weapons 3",250,250,4960,0,0,"Terran Vehicle Weapons 2","Terran Armory","Terran Science Facility");
		addUnit(1414,"Terran Vehicle Plating 1",100,100,4000,0,0,"Terran Armory","Terran Armory");
		addUnit(1424,"Terran Vehicle Plating 2",175,175,4480,0,0,"Terran Vehicle Plating 1","Terran Armory","Terran Science Facility");
		addUnit(1434,"Terran Vehicle Plating 3",250,250,4960,0,0,"Terran Vehicle Plating 2","Terran Armory","Terran Science Facility");
		addUnit(1415,"Terran Ship Weapons 1",100,100,4000,0,0,"Terran Armory","Terran Armory");
		addUnit(1425,"Terran Ship Weapons 2",175,175,4480,0,0,"Terran Ship Weapons 1","Terran Armory","Terran Science Facility");
		addUnit(1435,"Terran Ship Weapons 3",250,250,4960,0,0,"Terran Ship Weapons 2","Terran Armory","Terran Science Facility");
		addUnit(1416,"Terran Ship Plating 1",100,100,4000,0,0,"Terran Armory","Terran Armory");
		addUnit(1426,"Terran Ship Plating 2",175,175,4480,0,0,"Terran Ship Plating 1","Terran Armory","Terran Science Facility");
		addUnit(1436,"Terran Ship Plating 3",250,250,4960,0,0,"Terran Ship Plating 2","Terran Armory","Terran Science Facility");
	}
	if (race == 'p')
	{
		//economy
		addUnit(999,"Protoss Probe",50,0,300,1,0,"Protoss Nexus","Protoss Nexus");
		addUnit(999,"Protoss Nexus",400,0,1800,0,9,"Protoss Probe","Protoss Probe");
		addUnit(999,"Protoss Assimilator",100,0,600,0,0,"Protoss Nexus","Protoss Probe");
		//ground units
		addUnit(999,"Protoss Zealot",100,0,600,2,0,"Protoss Gateway","Protoss Gateway");
		addUnit(999,"Protoss Dragoon",125,50,750,2,0,"Protoss Cybernetics Core","Protoss Gateway");
		addUnit(999,"Protoss High Templar",50,150,750,2,0,"Protoss Templar Archives","Protoss Gateway");
		addUnit(999,"Protoss Dark Templar",125,100,750,2,0,"Protoss Templar Archives","Protoss Gateway");
		addUnit(999,"Protoss Archon",0,0,300,0,0,"Protoss High Templar","Protoss High Templar");
		addUnit(999,"Protoss Dark Archon",0,0,300,0,0,"Protoss Dark Templar","Protoss Dark Templar");
		addUnit(999,"Protoss Reaver",200,100,1050,4,0,"Protoss Robotics Support Bay","Protoss Robotics Facility");
		addUnit(999,"Protoss Scarab",15,0,105,0,0,"Protoss Reaver","Protoss Reaver");
		//air units
		addUnit(999,"Protoss Scout",275,125,1200,3,0,"Protoss Stargate","Protoss Stargate");
		addUnit(999,"Protoss Corsair",150,100,600,2,0,"Protoss Stargate","Protoss Stargate");
		addUnit(999,"Protoss Arbiter",100,350,2400,4,0,"Protoss Arbiter Tribunal","Protoss Stargate");
		addUnit(999,"Protoss Carrier",350,200,2100,6,0,"Protoss Fleet Beacon","Protoss Stargate");
		addUnit(999,"Protoss Interceptor",25,0,300,0,0,"Protoss Carrier","Protoss Carrier");
		addUnit(999,"Protoss Observer",25,75,600,1,0,"Protoss Observatory","Protoss Robotics Facility");
		addUnit(999,"Protoss Shuttle",200,0,900,2,0,"Protoss Robotics Facility","Protoss Robotics Facility");
		//basic buildings
		addUnit(999,"Protoss Pylon",100,0,450,0,8,"Protoss Probe","Protoss Probe");
		addUnit(999,"Protoss Gateway",150,0,900,0,0,"Protoss Nexus","Protoss Probe", "Protoss Pylon");
		addUnit(999,"Protoss Forge",150,0,600,0,0,"Protoss Nexus","Protoss Probe");
		addUnit(999,"Protoss Photon Cannon",150,0,750,0,0,"Protoss Forge","Protoss Probe");
		addUnit(999,"Protoss Cybernetics Core",200,0,900,0,0,"Protoss Gateway","Protoss Probe");
		addUnit(999,"Protoss Shield Battery",100,0,450,0,0,"Protoss Gateway","Protoss Probe");
		//advanced buildings
		addUnit(999,"Protoss Robotics Facility",200,200,1200,0,0,"Protoss Cybernetics Core","Protoss Probe");
		addUnit(999,"Protoss Robotics Support Bay",150,100,450,0,0,"Protoss Robotics Facility","Protoss Probe");
		addUnit(999,"Protoss Observatory",50,100,450,0,0,"Protoss Robotics Facility","Protoss Probe");
		addUnit(999,"Protoss Stargate",150,150,1050,0,0,"Protoss Cybernetics Core","Protoss Probe");
		addUnit(999,"Protoss Fleet Beacon",300,200,900,0,0,"Protoss Stargate","Protoss Probe");
		addUnit(999,"Protoss Arbiter Tribunal",200,150,900,0,0,"Protoss Stargate","Protoss Probe","Protoss Templar Archives");
		addUnit(999,"Protoss Citadel Of Adun",150,100,900,0,0,"Protoss Cybernetics Core","Protoss Probe");
		addUnit(999,"Protoss Templar Archives",150,200,900,0,0,"Protoss Citadel Of Adun","Protoss Probe");
		//upgrades/tech
		addUnit(999,"Protoss Singularity Charge",150,150,2500,0,0,"Protoss Cybernetics Core","Protoss Cybernetics Core");
		addUnit(999,"Protoss Leg Enhancements",150,150,2000,0,0,"Protoss Citadel Of Adun","Protoss Citadel Of Adun");
		addUnit(999,"Protoss Scarab Damage",200,200,2500,0,0,"Protoss Robotics Support Bay","Protoss Robotics Support Bay");
		addUnit(999,"Protoss Reaver Capacity",200,200,2500,0,0,"Protoss Robotics Support Bay","Protoss Robotics Support Bay");
		addUnit(999,"Protoss Gravitic Drive",200,200,2500,0,0,"Protoss Robotics Support Bay","Protoss Robotics Support Bay");
		addUnit(999,"Protoss Sensor Array",150,150,2000,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit(999,"Protoss Gravitic Boosters",150,150,2000,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit(999,"Protoss Apial Sensors",100,100,2500,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit(999,"Protoss Gravitic Thrusters",200,200,2500,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit(999,"Protoss Carrier Capacity",100,100,1500,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit(999,"Protoss Disruption Web",200,200,1200,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit(999,"Protoss Argus Jewel",100,100,2500,0,0,"Protoss Fleet Beacon","Protoss Fleet Beacon");
		addUnit(999,"Protoss Recall",150,150,1800,0,0,"Protoss Arbiter Tribunal","Protoss Arbiter Tribunal");
		addUnit(999,"Protoss Stasis Field",150,150,1500,0,0,"Protoss Arbiter Tribunal","Protoss Arbiter Tribunal");
		addUnit(999,"Protoss Khaydarin Core",150,150,2500,0,0,"Protoss Arbiter Tribunal","Protoss Arbiter Tribunal");
		addUnit(999,"Protoss Psionic Storm",200,200,1800,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit(999,"Protoss Hallucination",150,150,1200,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit(999,"Protoss Khaydarin Amulet",150,150,2500,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit(999,"Protoss Maelstrom",100,100,1500,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit(999,"Protoss Mind Control",200,200,1800,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		addUnit(999,"Protoss Argus Talisman",150,150,2500,0,0,"Protoss Templar Archives","Protoss Templar Archives");
		//numerical upgrades
		addUnit(999,"Protoss Ground Weapons 1",100,100,4000,0,0,"Protoss Forge","Protoss Forge");
		addUnit(999,"Protoss Ground Weapons 2",175,175,4480,0,0,"Protoss Ground Weapons 1","Protoss Forge","Protoss Templar Archives");
		addUnit(999,"Protoss Ground Weapons 3",250,250,4960,0,0,"Protoss Ground Weapons 2","Protoss Forge","Protoss Templar Archives");
		addUnit(999,"Protoss Ground Armor 1",100,100,4000,0,0,"Protoss Forge","Protoss Forge");
		addUnit(999,"Protoss Ground Armor 2",175,175,4480,0,0,"Protoss Ground Armor 1","Protoss Forge","Protoss Templar Archives");
		addUnit(999,"Protoss Ground Armor 3",250,250,4960,0,0,"Protoss Ground Armor 2","Protoss Forge","Protoss Templar Archives");
		addUnit(999,"Protoss Plasma Shields 1",200,200,4000,0,0,"Protoss Forge","Protoss Forge");
		addUnit(999,"Protoss Plasma Shields 2",300,300,4480,0,0,"Protoss Plasma Shields 1","Protoss Forge","Protoss Cybernetics Core");
		addUnit(999,"Protoss Plasma Shields 3",400,400,4960,0,0,"Protoss Plasma Shields 2","Protoss Forge","Protoss Cybernetics Core");
		addUnit(999,"Protoss Air Weapons 1",100,100,4000,0,0,"Protoss Cybernetics Core","Protoss Cybernetics Core");
		addUnit(999,"Protoss Air Weapons 2",175,175,4480,0,0,"Protoss Air Weapons 1","Protoss Cybernetics Core","Protoss Fleet Beacon");
		addUnit(999,"Protoss Air Weapons 3",250,250,4960,0,0,"Protoss Air Weapons 2","Protoss Cybernetics Core","Protoss Fleet Beacon");
		addUnit(999,"Protoss Air Armor 1",100,100,4000,0,0,"Protoss Cybernetics Core","Protoss Cybernetics Core");
		addUnit(999,"Protoss Air Armor 2",175,175,4480,0,0,"Protoss Air Armor 1","Protoss Cybernetics Core","Protoss Fleet Beacon");
		addUnit(999,"Protoss Air Armor 3",250,250,4960,0,0,"Protoss Air Armor 2","Protoss Cybernetics Core","Protoss Fleet Beacon");
	}
	if (race == 'z')
	{
		//economy buildings
		addUnit(999,"Zerg Drone",50,0,300,1,0,"Zerg Larva","Zerg Larva","",false,false,true);
		addUnit(999,"Zerg Hatchery",300,0,1800,0,1,"Zerg Drone","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Extractor",50,0,600,0,0,"Zerg Hatchery","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Larva Spawner",10000,10000,0,0,0,"Zerg Hatchery","Zerg Hatchery");
		//ground units
		addUnit(999,"Zerg Larva",0,0,342,0,0,"Zerg Larva Spawner","Zerg Larva Spawner");
		addUnit(999,"Zerg Zergling",50,0,420,1,0,"Zerg Spawning Pool","Zerg Larva","",false,false,true);
		addUnit(999,"Zerg Hydralisk",75,25,420,1,0,"Zerg Hydralisk Den","Zerg Larva","",false,false,true);
		addUnit(999,"Zerg Lurker",50,100,600,2,0,"Zerg Lurker Aspect","Zerg Hydralisk","",false,false,true);
		addUnit(999,"Zerg Ultralisk",200,200,900,4,0,"Zerg Ultralisk Cavern","Zerg Larva","",false,false,true);
		addUnit(999,"Zerg Defiler",50,150,750,2,0,"Zerg Defiler Mound","Zerg Larva","",false,false,true);
		//air units
		addUnit(999,"Zerg Overlord",100,0,600,0,8,"Zerg Larva","Zerg Larva","",false,false,true);
		addUnit(999,"Zerg Mutalisk",100,100,600,2,0,"Zerg Spire","Zerg Larva","",false,false,true);
		addUnit(999,"Zerg Scourge",25,75,450,1,0,"Zerg Spire","Zerg Larva","",false,false,true);
		addUnit(999,"Zerg Queen",100,100,750,2,0,"Zerg Queen's Nest","Zerg Larva","",false,false,true);
		addUnit(999,"Zerg Guardian",50,100,600,2,0,"Zerg Greater Spire","Zerg Mutalisk","",false,false,true);
		addUnit(999,"Zerg Devourer",150,50,600,2,0,"Zerg Greater Spire","Zerg Mutalisk","",false,false,true);
		//basic buildings
		addUnit(999,"Zerg Lair",150,100,1500,0,0,"Zerg Spawning Pool","Zerg Hatchery","",true);
		addUnit(999,"Zerg Hive",200,150,1800,0,0,"Zerg Queen's Nest","Zerg Lair","",true);
		addUnit(999,"Zerg Spawning Pool",200,0,1200,0,0,"Zerg Hatchery","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Evolution Chamber",75,0,600,0,0,"Zerg Hatchery","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Hydralisk Den",100,50,600,0,0,"Zerg Spawning Pool","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Creep Colony",75,0,300,0,0,"Zerg Hatchery","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Sunken Colony",50,0,300,0,0,"Zerg Spawning Pool","Zerg Creep Colony","",false,false,true);
		addUnit(999,"Zerg Spore Colony",50,0,300,0,0,"Zerg Evolution Chamber","Zerg Creep Colony","",false,false,true);
		//advanced buildings
		addUnit(999,"Zerg Spire",200,150,1800,0,0,"Zerg Lair","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Greater Spire",100,150,1800,0,0,"Zerg Hive","Zerg Spire","",true);
		addUnit(999,"Zerg Queen's Nest",150,100,900,0,0,"Zerg Lair","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Ultralisk Cavern",150,200,1200,0,0,"Zerg Hive","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Defiler Mound",100,100,900,0,0,"Zerg Hive","Zerg Drone","",false,false,true);
		addUnit(999,"Zerg Nydus Canal",150,0,600,0,0,"Zerg Hive","Zerg Drone","",false,false,true);
		//upgrades/tech
		addUnit(999,"Zerg Burrowing",100,100,1200,0,0,"Zerg Hatchery","Zerg Hatchery");
		addUnit(999,"Zerg Ventral Sacs",200,200,2400,0,0,"Zerg Lair","Zerg Hatchery");
		addUnit(999,"Zerg Antennae",150,150,2000,0,0,"Zerg Lair","Zerg Hatchery");
		addUnit(999,"Zerg Pneumatized Carapace",150,150,2000,0,0,"Zerg Lair","Zerg Hatchery");
		addUnit(999,"Zerg Metabolic Boost",100,100,1500,0,0,"Zerg Spawning Pool","Zerg Spawning Pool");
		addUnit(999,"Zerg Adrenal Glands",200,200,1500,0,0,"Zerg Hive","Zerg Spawning Pool");
		addUnit(999,"Zerg Muscular Augments",150,150,1500,0,0,"Zerg Hydralisk Den","Zerg Hydralisk Den");
		addUnit(999,"Zerg Grooved Spines",150,150,1500,0,0,"Zerg Hydralisk Den","Zerg Hydralisk Den");
		addUnit(999,"Zerg Lurker Aspect",200,200,1800,0,0,"Zerg Lair","Zerg Hydralisk Den");
		addUnit(999,"Zerg Ensnare",100,100,1200,0,0,"Zerg Queen's Nest","Zerg Queen's Nest");
		addUnit(999,"Zerg Spawn Broodling",150,150,1200,0,0,"Zerg Queen's Nest","Zerg Queen's Nest");
		addUnit(999,"Zerg Gamete Meiosis",100,100,2500,0,0,"Zerg Queen's Nest","Zerg Queen's Nest");
		addUnit(999,"Zerg Anabolic Synthesis",200,200,2000,0,0,"Zerg Ultralisk Cavern","Zerg Ultralisk Cavern");
		addUnit(999,"Zerg Chitinous Plating",150,150,2000,0,0,"Zerg Ultralisk Cavern","Zerg Ultralisk Cavern");
		addUnit(999,"Zerg Consume",100,100,1500,0,0,"Zerg Defiler Mound","Zerg Defiler Mound");
		addUnit(999,"Zerg Plague",200,200,1500,0,0,"Zerg Defiler Mound","Zerg Defiler Mound");
		addUnit(999,"Zerg Metasynaptic Node",150,150,2500,0,0,"Zerg Defiler Mound","Zerg Defiler Mound");
		//numerical upgrades
		addUnit(999,"Zerg Melee Attacks 1",100,100,4000,0,0,"Zerg Evolution Chamber","Zerg Evolution Chamber");
		addUnit(999,"Zerg Melee Attacks 2",150,150,4480,0,0,"Zerg Melee Attacks 1","Zerg Evolution Chamber","Zerg Lair");
		addUnit(999,"Zerg Melee Attacks 3",200,200,4960,0,0,"Zerg Melee Attacks 2","Zerg Evolution Chamber","Zerg Hive");
		addUnit(999,"Zerg Missile Attacks 1",100,100,4000,0,0,"Zerg Evolution Chamber","Zerg Evolution Chamber");
		addUnit(999,"Zerg Missile Attacks 2",150,150,4480,0,0,"Zerg Missile Attacks 1","Zerg Evolution Chamber","Zerg Lair");
		addUnit(999,"Zerg Missile Attacks 3",200,200,4960,0,0,"Zerg Missile Attacks 2","Zerg Evolution Chamber","Zerg Hive");
		addUnit(999,"Zerg Carapace 1",150,150,4000,0,0,"Zerg Evolution Chamber","Zerg Evolution Chamber");
		addUnit(999,"Zerg Carapace 2",225,225,4480,0,0,"Zerg Carapace 1","Zerg Evolution Chamber","Zerg Lair");
		addUnit(999,"Zerg Carapace 3",300,300,4960,0,0,"Zerg Carapace 2","Zerg Evolution Chamber","Zerg Hive");
		addUnit(999,"Zerg Flyer Attacks 1",100,100,4000,0,0,"Zerg Spire","Zerg Spire");
		addUnit(999,"Zerg Flyer Attacks 2",175,175,4480,0,0,"Zerg Flyer Attacks 1","Zerg Spire","Zerg Lair");
		addUnit(999,"Zerg Flyer Attacks 3",250,250,4960,0,0,"Zerg Flyer Attacks 2","Zerg Spire","Zerg Hive");
		addUnit(999,"Zerg Flyer Carapace 1",150,150,4000,0,0,"Zerg Spire","Zerg Spire");
		addUnit(999,"Zerg Flyer Carapace 2",225,225,4480,0,0,"Zerg Flyer Carapace 1","Zerg Spire","Zerg Lair");
		addUnit(999,"Zerg Flyer Carapace 3",300,300,4960,0,0,"Zerg Flyer Carapace 2","Zerg Spire","Zerg Hive");
	}
}
