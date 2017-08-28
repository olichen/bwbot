#include "unitdata.h"

UnitName UnitData::getUnitIdFromName(string name) const {
	for(int i=0; i<UnitName::UNIT_TOTAL; i++)
		if(unitStatsList[i].name == name)
			return (UnitName)i;
	throw UnitNotFound();
}

UnitStatBlock UnitData::getUnitFromId(UnitName unitname) const {
	if(unitname >= UnitName::UNIT_TOTAL)
		throw UnitNotFound();
	return unitStatsList[unitname];
}

UnitStatBlock UnitData::getRaceWorker(char race) const {
	return getUnitForRace(race, &UnitStatBlock::isWorker);
}

UnitStatBlock UnitData::getRaceExpansion(char race) const {
	return getUnitForRace(race, &UnitStatBlock::isExpansion);
}

UnitStatBlock UnitData::getRaceGas(char race) const {
	return getUnitForRace(race, &UnitStatBlock::isGas);
}

UnitStatBlock UnitData::getUnitForRace(char race, bool (UnitStatBlock::*function)()) const {
	for (UnitStatBlock unit : unitStatsList)
		if(unit.race == race && (unit.*function)())
			return unit;
	throw UnitNotFound();
}

// initialize all units in an array; no code below this point
UnitData::UnitData()
	: unitStatsList {
		{ 't', "Terran SCV",
			50,0,300,1,0,
			{UnitName::Terran_Command_Center,UnitName::UNIT_NULL},UnitName::Terran_Command_Center,
			false, false,
			false, false, true,
			'u' },
		{ 't', "Terran Marine",
			50,0,360,1,0,
			{UnitName::Terran_Barracks,UnitName::UNIT_NULL},UnitName::Terran_Barracks,
			false, false,
			false, false, false,
			'u' },
		{ 't', "Terran Firebat",
			50,25,360,1,0,
			{UnitName::Terran_Academy,UnitName::UNIT_NULL},UnitName::Terran_Barracks,
			false, false,
			false, false, false,
			'u' },
		{ 't', "Terran Ghost",
			25,75,750,1,0,
			{UnitName::Terran_Covert_Ops,UnitName::Terran_Barracks},Terran_Academy,
			false, false,
			false, false, false,
			'u' },
		{ 't', "Terran Medic",
			50,25,450,1,0,
			{UnitName::Terran_Academy,UnitName::UNIT_NULL},UnitName::Terran_Barracks,
			false, false,
			false, false, false,
			'u' },
		{ 't', "Terran Vulture",
			75,0,450,2,0,
			{UnitName::Terran_Factory,UnitName::UNIT_NULL},UnitName::Terran_Factory,
			false, false,
			false, false, false,
			'u' },
		{ 't', "Terran Goliath",
			100,50,600,2,0,
			{UnitName::Terran_Armory,UnitName::UNIT_NULL},UnitName::Terran_Factory,
			false, false,
			false, false, false,
			'u' },
		{ 't', "Terran Siege Tank",
			150,100,750,2,0,
			{UnitName::Terran_Machine_Shop,UnitName::UNIT_NULL},UnitName::Terran_Factory,
			true, false,
			false, false, false,
			'u' },
		{ 't', "Terran Wraith",
			150,100,900,2,0,
			{UnitName::Terran_Starport,UnitName::UNIT_NULL},UnitName::Terran_Starport,
			false, false,
			false, false, false,
			'u' },
		{ 't', "Terran Dropship",
			100,100,750,2,0,
			{UnitName::Terran_Control_Tower,UnitName::UNIT_NULL},UnitName::Terran_Starport,
			true, false,
			false, false, false,
			'u' },
		{ 't', "Terran Valkyrie",
			250,125,750,3,0,
			{UnitName::Terran_Control_Tower, UnitName::Terran_Armory},UnitName::Terran_Starport,
			true, false,
			false, false, false,
			'u' },
		{ 't', "Terran Science Vessel",
			100,225,1200,2,0,
			{UnitName::Terran_Science_Facility,UnitName::UNIT_NULL},UnitName::Terran_Starport,
			true, false,
			false, false, false,
			'u' },
		{ 't', "Terran Battlecruiser",
			50,0,'p', 6,0,
			{UnitName::Terran_Control_Tower, UnitName::Terran_Physics_Lab},UnitName::Terran_Starport,
			true, false,
			false, false, false,
			'u' },
		{ 't', "Terran Command Center",
			400,0,1800,0,10,
			{UnitName::Terran_SCV,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			true, false, false,
			'b' },
		{ 't', "Terran Supply Depot",
			100,0,600,0,8,
			{UnitName::Terran_Command_Center,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Refinery",
			100,0,600,0,0,
			{UnitName::Terran_Command_Center,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, true, false,
			'b' },
		{ 't', "Terran Barracks",
			150,0,1200,0,0,
			{UnitName::Terran_Command_Center,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Engineering Bay",
			125,0,900,0,0,
			{UnitName::Terran_Command_Center,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Missile Turret",
			75,0,450,0,0,
			{UnitName::Terran_Engineering_Bay,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Academy",
			150,0,1200,0,0,
			{UnitName::Terran_Barracks,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Bunker",
			100,0,450,0,0,
			{UnitName::Terran_Barracks,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Factory",
			200,100,1200,0,0,
			{UnitName::Terran_Barracks,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Armory",
			100,50,1200,0,0,
			{UnitName::Terran_Factory,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Science Facility",
			100,150,900,0,0,
			{UnitName::Terran_Starport,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Starport",
			150,100,1050,0,0,
			{UnitName::Terran_Factory,UnitName::UNIT_NULL},UnitName::Terran_SCV,
			false, false,
			false, false, false,
			'b' },
		{ 't', "Terran Machine Shop",
			50,50,600,0,0,
			{UnitName::Terran_Factory,UnitName::UNIT_NULL},UnitName::Terran_Factory,
			false, false,
			false, false, false,
			'a' },
		{ 't', "Terran Control Tower",
			50,50,600,0,0,
			{UnitName::Terran_Starport,UnitName::UNIT_NULL},UnitName::Terran_Starport,
			false, false,
			false, false, false,
			'a' },
		{ 't', "Terran Comsat Station",
			50,50,600,0,0,
			{UnitName::Terran_Academy,UnitName::UNIT_NULL},UnitName::Terran_Command_Center,
			false, false,
			false, false, false,
			'a' },
		{ 't', "Terran Nuclear Silo",
			100,100,1200,0,0,
			{UnitName::Terran_Covert_Ops,UnitName::UNIT_NULL},UnitName::Terran_Command_Center,
			false, false,
			false, false, false,
			'a' },
		{ 't', "Terran Physics Lab",
			50,50,600,0,0,
			{UnitName::Terran_Science_Facility,UnitName::UNIT_NULL},UnitName::Terran_Science_Facility,
			false, false,
			false, false, false,
			'a' },
		{ 't', "Terran Covert Ops",
			50,50,600,0,0,
			{UnitName::Terran_Science_Facility,UnitName::UNIT_NULL},UnitName::Terran_Science_Facility,
			false, false,
			false, false, false,
			'a' },
		{ 't', "Terran Nuclear Missile",
			200,200,1500,8,0,
			{UnitName::Terran_Nuclear_Silo,UnitName::UNIT_NULL},UnitName::Terran_Nuclear_Silo,
			false, false,
			false, false, false,
			'a' },
		{ 't', "Terran U-238 Shells",
			150,150,1500,0,0,
			{UnitName::Terran_Academy,UnitName::UNIT_NULL},UnitName::Terran_Academy,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Stim Pack",
			100,100,1200,0,0,
			{UnitName::Terran_Academy,UnitName::UNIT_NULL},UnitName::Terran_Academy,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Restoration",
			100,100,1200,0,0,
			{UnitName::Terran_Academy,UnitName::UNIT_NULL},UnitName::Terran_Academy,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Optical Flare",
			100,100,1200,0,0,
			{UnitName::Terran_Academy,UnitName::UNIT_NULL},UnitName::Terran_Academy,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Caduceus Reactor",
			150,150,'r', 0,0,
			{UnitName::Terran_Academy,UnitName::UNIT_NULL},UnitName::Terran_Academy,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Ion Thrusters",
			100,100,1500,0,0,
			{UnitName::Terran_Machine_Shop,UnitName::UNIT_NULL},UnitName::Terran_Machine_Shop,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Spider Mines",
			100,100,1200,0,0,
			{UnitName::Terran_Machine_Shop,UnitName::UNIT_NULL},UnitName::Terran_Machine_Shop,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Siege Tech",
			150,150,1200,0,0,
			{UnitName::Terran_Machine_Shop,UnitName::UNIT_NULL},UnitName::Terran_Machine_Shop,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Charon Boosters",
			100,100,'r', 0,0,
			{UnitName::Terran_Armory,UnitName::UNIT_NULL},UnitName::Terran_Machine_Shop,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Cloaking Field",
			150,150,1500,0,0,
			{UnitName::Terran_Control_Tower,UnitName::UNIT_NULL},UnitName::Terran_Control_Tower,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Apollo Reactor",
			200,200,'r', 0,0,
			{UnitName::Terran_Control_Tower,UnitName::UNIT_NULL},UnitName::Terran_Control_Tower,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran EMP Shockwave",
			200,200,1800,0,0,
			{UnitName::Terran_Science_Facility,UnitName::UNIT_NULL},UnitName::Terran_Science_Facility,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Irradiate",
			200,200,1200,0,0,
			{UnitName::Terran_Science_Facility,UnitName::UNIT_NULL},UnitName::Terran_Science_Facility,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Titan Reactor",
			150,150,'r', 0,0,
			{UnitName::Terran_Science_Facility,UnitName::UNIT_NULL},UnitName::Terran_Science_Facility,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Lockdown",
			200,200,1500,0,0,
			{UnitName::Terran_Covert_Ops,UnitName::UNIT_NULL},UnitName::Terran_Covert_Ops,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Personnel Cloaking",
			100,100,1200,0,0,
			{UnitName::Terran_Covert_Ops,UnitName::UNIT_NULL},UnitName::Terran_Covert_Ops,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Ocular Implants",
			100,100,'r', 0,0,
			{UnitName::Terran_Covert_Ops,UnitName::UNIT_NULL},UnitName::Terran_Covert_Ops,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Moebius Reactor",
			150,150,'r', 0,0,
			{UnitName::Terran_Covert_Ops,UnitName::UNIT_NULL},UnitName::Terran_Covert_Ops,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Yamato Gun",
			100,100,1800,0,0,
			{UnitName::Terran_Physics_Lab,UnitName::UNIT_NULL},UnitName::Terran_Physics_Lab,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Colossus Reactor",
			150,150,'r', 0,0,
			{UnitName::Terran_Physics_Lab,UnitName::UNIT_NULL},UnitName::Terran_Physics_Lab,
			false, false,
			false, false, false,
			'r' },
		{ 't', "Terran Infantry Weapons 1",
			100,100,4000,0,0,
			{UnitName::Terran_Engineering_Bay,UnitName::UNIT_NULL},UnitName::Terran_Engineering_Bay,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Infantry Weapons 2",
			175,175,4480,0,0,
			{UnitName::Terran_Infantry_Weapons_1, UnitName::Terran_Science_Facility},UnitName::Terran_Engineering_Bay,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Infantry Weapons 3",
			250,250,4960,0,0,
			{UnitName::Terran_Infantry_Weapons_2, UnitName::Terran_Science_Facility},UnitName::Terran_Engineering_Bay,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Infantry Armor 1",
			100,100,4000,0,0,
			{UnitName::Terran_Engineering_Bay,UnitName::UNIT_NULL},UnitName::Terran_Engineering_Bay,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Infantry Armor 2",
			175,175,4480,0,0,
			{UnitName::Terran_Infantry_Armor_1,UnitName::Terran_Science_Facility},UnitName::Terran_Engineering_Bay,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Infantry Armor 3",
			250,250,4960,0,0,
			{UnitName::Terran_Infantry_Armor_2,UnitName::Terran_Science_Facility},UnitName::Terran_Engineering_Bay,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Vehicle Weapons 1",
			100,100,4000,0,0,
			{UnitName::Terran_Armory,UnitName::UNIT_NULL},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Vehicle Weapons 2",
			175,175,4480,0,0,
			{UnitName::Terran_Vehicle_Weapons_1,UnitName::Terran_Science_Facility},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Vehicle Weapons 3",
			250,250,4960,0,0,
			{UnitName::Terran_Vehicle_Weapons_2,UnitName::Terran_Science_Facility},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Vehicle Plating 1",
			100,100,4000,0,0,
			{UnitName::Terran_Armory,UnitName::UNIT_NULL},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Vehicle Plating 2",
			175,175,4480,0,0,
			{UnitName::Terran_Vehicle_Plating_1,UnitName::Terran_Science_Facility},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Vehicle Plating 3",
			250,250,4960,0,0,
			{UnitName::Terran_Vehicle_Plating_2,UnitName::Terran_Science_Facility},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Ship Weapons 1",
			100,100,4000,0,0,
			{UnitName::Terran_Armory,UnitName::UNIT_NULL},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Ship Weapons 2",
			175,175,4480,0,0,
			{UnitName::Terran_Ship_Weapons_1,UnitName::Terran_Science_Facility},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Ship Weapons 3",
			250,250,4960,0,0,
			{UnitName::Terran_Ship_Weapons_2,UnitName::Terran_Science_Facility},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Ship Plating 1",
			100,100,4000,0,0,
			{UnitName::Terran_Armory,UnitName::UNIT_NULL},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Ship Plating 2",
			175,175,4480,0,0,
			{UnitName::Terran_Ship_Plating_1,UnitName::Terran_Science_Facility},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 't', "Terran Ship Plating 3",
			250,250,4960,0,0,
			{UnitName::Terran_Ship_Plating_2,UnitName::Terran_Science_Facility},UnitName::Terran_Armory,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Probe",
			50,0,300,1,0,
			{UnitName::Protoss_Nexus,UnitName::UNIT_NULL},UnitName::Protoss_Nexus,
			false, false,
			false, false, true,
			'u' },
		{ 'p', "Protoss Zealot",
			100,0,600,2,0,
			{UnitName::Protoss_Gateway,UnitName::UNIT_NULL},UnitName::Protoss_Gateway,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Dragoon",
			125,50,750,2,0,
			{UnitName::Protoss_Cybernetics_Core,UnitName::UNIT_NULL},UnitName::Protoss_Gateway,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss High Templar",
			50,150,750,2,0,
			{UnitName::Protoss_Templar_Archives,UnitName::UNIT_NULL},UnitName::Protoss_Gateway,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Dark Templar",
			125,100,750,2,0,
			{UnitName::Protoss_Templar_Archives,UnitName::UNIT_NULL},UnitName::Protoss_Gateway,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Archon",
			0,0,300,0,0,
			{UnitName::Protoss_High_Templar,UnitName::UNIT_NULL},UnitName::Protoss_High_Templar,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Dark Archon",
			0,0,300,0,0,
			{UnitName::Protoss_Dark_Templar,UnitName::UNIT_NULL},UnitName::Protoss_Dark_Templar,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Reaver",
			200,100,1050,4,0,
			{UnitName::Protoss_Robotics_Support_Bay,UnitName::UNIT_NULL},UnitName::Protoss_Robotics_Facility,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Scarab",
			15,0,105,0,0,
			{UnitName::Protoss_Reaver,UnitName::UNIT_NULL},UnitName::Protoss_Reaver,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Scout",
			275,125,1200,3,0,
			{UnitName::Protoss_Stargate,UnitName::UNIT_NULL},UnitName::Protoss_Stargate,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Corsair",
			150,100,600,2,0,
			{UnitName::Protoss_Stargate,UnitName::UNIT_NULL},UnitName::Protoss_Stargate,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Arbiter",
			100,350,2400,4,0,
			{UnitName::Protoss_Arbiter_Tribunal,UnitName::UNIT_NULL},UnitName::Protoss_Stargate,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Carrier",
			350,200,2100,6,0,
			{UnitName::Protoss_Fleet_Beacon,UnitName::UNIT_NULL},UnitName::Protoss_Stargate,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Interceptor",
			25,0,300,0,0,
			{UnitName::Protoss_Carrier,UnitName::UNIT_NULL},UnitName::Protoss_Carrier,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Observer",
			25,75,600,1,0,
			{UnitName::Protoss_Observatory,UnitName::UNIT_NULL},UnitName::Protoss_Robotics_Facility,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Shuttle",
			200,0,900,2,0,
			{UnitName::Protoss_Robotics_Facility,UnitName::UNIT_NULL},UnitName::Protoss_Robotics_Facility,
			false, false,
			false, false, false,
			'u' },
		{ 'p', "Protoss Nexus",
			400,0,1800,0,9,
			{UnitName::Protoss_Probe,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			true, false, false,
			'b' },
		{ 'p', "Protoss Pylon",
			100,0,450,0,8,
			{UnitName::Protoss_Probe,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Assimilator",
			100,0,600,0,0,
			{UnitName::Protoss_Nexus,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, true, false,
			'b' },
		{ 'p', "Protoss Gateway",
			150,0,900,0,0,
			{UnitName::Protoss_Nexus,UnitName::Protoss_Pylon},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Forge",
			150,0,600,0,0,
			{UnitName::Protoss_Nexus,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Photon Cannon",
			150,0,750,0,0,
			{UnitName::Protoss_Forge,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Cybernetics Core",
			200,0,900,0,0,
			{UnitName::Protoss_Gateway,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Shield Battery",
			100,0,450,0,0,
			{UnitName::Protoss_Gateway,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Robotics Facility",
			200,200,1200,0,0,
			{UnitName::Protoss_Cybernetics_Core,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Robotics Support Bay",
			150,100,450,0,0,
			{UnitName::Protoss_Robotics_Facility,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Observatory",
			50,100,450,0,0,
			{UnitName::Protoss_Robotics_Facility,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Stargate",
			150,150,1050,0,0,
			{UnitName::Protoss_Cybernetics_Core,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Fleet Beacon",
			300,200,900,0,0,
			{UnitName::Protoss_Stargate,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Arbiter Tribunal",
			200,150,900,0,0,
			{UnitName::Protoss_Stargate,UnitName::Protoss_Templar_Archives},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Citadel Of Adun",
			150,100,900,0,0,
			{UnitName::Protoss_Cybernetics_Core,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Templar Archives",
			150,200,900,0,0,
			{UnitName::Protoss_Citadel_Of_Adun,UnitName::UNIT_NULL},UnitName::Protoss_Probe,
			false, false,
			false, false, false,
			'b' },
		{ 'p', "Protoss Singularity Charge",
			150,150,2500,0,0,
			{UnitName::Protoss_Cybernetics_Core,UnitName::UNIT_NULL},UnitName::Protoss_Cybernetics_Core,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Leg Enhancements",
			150,150,2000,0,0,
			{UnitName::Protoss_Citadel_Of_Adun,UnitName::UNIT_NULL},UnitName::Protoss_Citadel_Of_Adun,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Scarab Damage",
			200,200,2500,0,0,
			{UnitName::Protoss_Robotics_Support_Bay,UnitName::UNIT_NULL},UnitName::Protoss_Robotics_Support_Bay,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Reaver Capacity",
			200,200,2500,0,0,
			{UnitName::Protoss_Robotics_Support_Bay,UnitName::UNIT_NULL},UnitName::Protoss_Robotics_Support_Bay,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Gravitic Drive",
			200,200,2500,0,0,
			{UnitName::Protoss_Robotics_Support_Bay,UnitName::UNIT_NULL},UnitName::Protoss_Robotics_Support_Bay,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Sensor Array",
			150,150,2000,0,0,
			{UnitName::Protoss_Fleet_Beacon,UnitName::UNIT_NULL},UnitName::Protoss_Fleet_Beacon,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Gravitic Boosters",
			150,150,2000,0,0,
			{UnitName::Protoss_Fleet_Beacon,UnitName::UNIT_NULL},UnitName::Protoss_Fleet_Beacon,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Psionic Storm",
			200,200,1800,0,0,
			{UnitName::Protoss_Templar_Archives,UnitName::UNIT_NULL},UnitName::Protoss_Templar_Archives,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Hallucination",
			150,150,1200,0,0,
			{UnitName::Protoss_Templar_Archives,UnitName::UNIT_NULL},UnitName::Protoss_Templar_Archives,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Khaydarin Amulet",
			150,150,2500,0,0,
			{UnitName::Protoss_Templar_Archives,UnitName::UNIT_NULL},UnitName::Protoss_Templar_Archives,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Maelstrom",
			100,100,1500,0,0,
			{UnitName::Protoss_Templar_Archives,UnitName::UNIT_NULL},UnitName::Protoss_Templar_Archives,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Mind Control",
			200,200,1800,0,0,
			{UnitName::Protoss_Templar_Archives,UnitName::UNIT_NULL},UnitName::Protoss_Templar_Archives,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Argus Talisman",
			150,150,2500,0,0,
			{UnitName::Protoss_Templar_Archives,UnitName::UNIT_NULL},UnitName::Protoss_Templar_Archives,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Apial Sensors",
			100,100,2500,0,0,
			{UnitName::Protoss_Fleet_Beacon,UnitName::UNIT_NULL},UnitName::Protoss_Fleet_Beacon,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Gravitic Thrusters",
			200,200,2500,0,0,
			{UnitName::Protoss_Fleet_Beacon,UnitName::UNIT_NULL},UnitName::Protoss_Fleet_Beacon,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Carrier Capacity",
			100,100,1500,0,0,
			{UnitName::Protoss_Fleet_Beacon,UnitName::UNIT_NULL},UnitName::Protoss_Fleet_Beacon,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Disruption Web",
			200,200,1200,0,0,
			{UnitName::Protoss_Fleet_Beacon,UnitName::UNIT_NULL},UnitName::Protoss_Fleet_Beacon,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Argus Jewel",
			100,100,2500,0,0,
			{UnitName::Protoss_Fleet_Beacon,UnitName::UNIT_NULL},UnitName::Protoss_Fleet_Beacon,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Recall",
			150,150,1800,0,0,
			{UnitName::Protoss_Arbiter_Tribunal,UnitName::UNIT_NULL},UnitName::Protoss_Arbiter_Tribunal,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Stasis Field",
			150,150,1500,0,0,
			{UnitName::Protoss_Arbiter_Tribunal,UnitName::UNIT_NULL},UnitName::Protoss_Arbiter_Tribunal,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Khaydarin Core",
			150,150,2500,0,0,
			{UnitName::Protoss_Arbiter_Tribunal,UnitName::UNIT_NULL},UnitName::Protoss_Arbiter_Tribunal,
			false, false,
			false, false, false,
			'r' },
		{ 'p', "Protoss Ground Weapons 1",
			100,100,4000,0,0,
			{UnitName::Protoss_Forge,UnitName::UNIT_NULL},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Ground Weapons 2",
			175,175,4480,0,0,
			{UnitName::Protoss_Ground_Weapons_1,UnitName::Protoss_Templar_Archives},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Ground Weapons 3",
			250,250,4960,0,0,
			{UnitName::Protoss_Ground_Weapons_2,UnitName::Protoss_Templar_Archives},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Ground Armor 1",
			100,100,4000,0,0,
			{UnitName::Protoss_Forge,UnitName::UNIT_NULL},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Ground Armor 2",
			175,175,4480,0,0,
			{UnitName::Protoss_Ground_Armor_1,UnitName::Protoss_Templar_Archives},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Ground Armor 3",
			250,250,4960,0,0,
			{UnitName::Protoss_Ground_Armor_2,UnitName::Protoss_Templar_Archives},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Plasma Shields 1",
			200,200,4000,0,0,
			{UnitName::Protoss_Forge,UnitName::UNIT_NULL},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Plasma Shields 2",
			300,300,4480,0,0,
			{UnitName::Protoss_Plasma_Shields_1,UnitName::Protoss_Cybernetics_Core},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Plasma Shields 3",
			400,400,4960,0,0,
			{UnitName::Protoss_Plasma_Shields_2,UnitName::Protoss_Cybernetics_Core},UnitName::Protoss_Forge,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Air Weapons 1",
			100,100,4000,0,0,
			{UnitName::Protoss_Cybernetics_Core,UnitName::UNIT_NULL},UnitName::Protoss_Cybernetics_Core,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Air Weapons 2",
			175,175,4480,0,0,
			{UnitName::Protoss_Air_Weapons_1,UnitName::Protoss_Fleet_Beacon},UnitName::Protoss_Cybernetics_Core,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Air Weapons 3",
			250,250,4960,0,0,
			{UnitName::Protoss_Air_Weapons_2,UnitName::Protoss_Fleet_Beacon},UnitName::Protoss_Cybernetics_Core,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Air Armor 1",
			100,100,4000,0,0,
			{UnitName::Protoss_Cybernetics_Core,UnitName::UNIT_NULL},UnitName::Protoss_Cybernetics_Core,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Air Armor 2",
			175,175,4480,0,0,
			{UnitName::Protoss_Air_Armor_1,UnitName::Protoss_Fleet_Beacon},UnitName::Protoss_Cybernetics_Core,
			false, false,
			false, false, false,
			'n' },
		{ 'p', "Protoss Air Armor 3",
			250,250,4960,0,0,
			{UnitName::Protoss_Air_Armor_2,UnitName::Protoss_Fleet_Beacon},UnitName::Protoss_Cybernetics_Core,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Drone",
			50,0,300,1,0,
			{UnitName::Zerg_Larva,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, true,
			'u' },
		{ 'z', "Zerg Larva",
			0,0,342,0,0,
			{UnitName::UNIT_NULL,UnitName::UNIT_NULL},UnitName::UNIT_NULL,
			false, false,
			false, false, false,
			'u' },
		{ 'z', "Zerg Zergling",
			50,0,420,1,0,
			{UnitName::Zerg_Spawning_Pool,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Hydralisk",
			75,25,420,1,0,
			{UnitName::Zerg_Hydralisk_Den,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Lurker",
			50,100,600,2,0,
			{UnitName::Zerg_Lurker_Aspect,UnitName::UNIT_NULL},UnitName::Zerg_Hydralisk,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Ultralisk",
			200,200,900,4,0,
			{UnitName::Zerg_Ultralisk_Cavern,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Defiler",
			50,150,750,2,0,
			{UnitName::Zerg_Defiler_Mound,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Overlord",
			100,0,600,0,8,
			{UnitName::Zerg_Larva,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Mutalisk",
			100,100,600,2,0,
			{UnitName::Zerg_Spire,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Scourge",
			25,75,450,1,0,
			{UnitName::Zerg_Spire,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Queen",
			100,100,750,2,0,
			{UnitName::Zerg_Queens_Nest,UnitName::UNIT_NULL},UnitName::Zerg_Larva,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Guardian",
			50,100,600,2,0,
			{UnitName::Zerg_Greater_Spire,UnitName::UNIT_NULL},UnitName::Zerg_Mutalisk,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Devourer",
			150,50,600,2,0,
			{UnitName::Zerg_Greater_Spire,UnitName::UNIT_NULL},UnitName::Zerg_Mutalisk,
			false, true,
			false, false, false,
			'u' },
		{ 'z', "Zerg Hatchery",
			300,0,1800,0,1,
			{UnitName::Zerg_Drone,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			true, false, false,
			'b' },
		{ 'z', "Zerg Extractor",
			50,0,600,0,0,
			{UnitName::Zerg_Hatchery,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, true, false,
			'b' },
		{ 'z', "Zerg Spawning Pool",
			200,0,1200,0,0,
			{UnitName::Zerg_Hatchery,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Evolution Chamber",
			75,0,600,0,0,
			{UnitName::Zerg_Hatchery,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Hydralisk Den",
			100,50,600,0,0,
			{UnitName::Zerg_Spawning_Pool,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Creep Colony",
			75,0,300,0,0,
			{UnitName::Zerg_Hatchery,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Sunken Colony",
			50,0,300,0,0,
			{UnitName::Zerg_Spawning_Pool,UnitName::UNIT_NULL},UnitName::Zerg_Creep_Colony,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Spore Colony",
			50,0,300,0,0,
			{UnitName::Zerg_Evolution_Chamber,UnitName::UNIT_NULL},UnitName::Zerg_Creep_Colony,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Lair",
			150,100,1500,0,1,
			{UnitName::Zerg_Spawning_Pool,UnitName::UNIT_NULL},UnitName::Zerg_Hatchery,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Hive",
			200,150,1800,0,1,
			{UnitName::Zerg_Queens_Nest,UnitName::UNIT_NULL},UnitName::Zerg_Lair,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Spire",
			200,150,1800,0,0,
			{UnitName::Zerg_Lair,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Queen's Nest",
			150,100,900,0,0,
			{UnitName::Zerg_Lair,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Nydus Canal",
			150,0,600,0,0,
			{UnitName::Zerg_Hive,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Ultralisk Cavern",
			150,200,1200,0,0,
			{UnitName::Zerg_Hive,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Defiler Mound",
			100,100,900,0,0,
			{UnitName::Zerg_Hive,UnitName::UNIT_NULL},UnitName::Zerg_Drone,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Greater Spire",
			100,150,1800,0,0,
			{UnitName::Zerg_Hive,UnitName::UNIT_NULL},UnitName::Zerg_Spire,
			false, true,
			false, false, false,
			'b' },
		{ 'z', "Zerg Burrowing",
			100,100,1200,0,0,
			{UnitName::Zerg_Hatchery,UnitName::UNIT_NULL},UnitName::Zerg_Hatchery,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Ventral Sacs",
			200,200,'p', 0,0,
			{UnitName::Zerg_Lair,UnitName::UNIT_NULL},UnitName::Zerg_Hatchery,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Antennae",
			150,150,'p', 0,0,
			{UnitName::Zerg_Lair,UnitName::UNIT_NULL},UnitName::Zerg_Hatchery,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Pneumatized Carapace",
			150,150,'p', 0,0,
			{UnitName::Zerg_Lair,UnitName::UNIT_NULL},UnitName::Zerg_Hatchery,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Metabolic Boost",
			100,100,1500,0,0,
			{UnitName::Zerg_Spawning_Pool,UnitName::UNIT_NULL},UnitName::Zerg_Spawning_Pool,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Adrenal Glands",
			200,200,1500,0,0,
			{UnitName::Zerg_Hive,UnitName::UNIT_NULL},UnitName::Zerg_Spawning_Pool,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Muscular Augments",
			150,150,1500,0,0,
			{UnitName::Zerg_Hydralisk_Den,UnitName::UNIT_NULL},UnitName::Zerg_Hydralisk_Den,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Grooved Spines",
			150,150,1500,0,0,
			{UnitName::Zerg_Hydralisk_Den,UnitName::UNIT_NULL},UnitName::Zerg_Hydralisk_Den,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Lurker Aspect",
			200,200,1800,0,0,
			{UnitName::Zerg_Lair,UnitName::UNIT_NULL},UnitName::Zerg_Hydralisk_Den,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Spawn Broodling",
			150,150,1200,0,0,
			{UnitName::Zerg_Queens_Nest,UnitName::UNIT_NULL},UnitName::Zerg_Queens_Nest,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Ensnare",
			100,100,1200,0,0,
			{UnitName::Zerg_Queens_Nest,UnitName::UNIT_NULL},UnitName::Zerg_Queens_Nest,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Gamete Meiosis",
			100,100,'p', 0,0,
			{UnitName::Zerg_Queens_Nest,UnitName::UNIT_NULL},UnitName::Zerg_Queens_Nest,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Anabolic Synthesis",
			200,200,'p', 0,0,
			{UnitName::Zerg_Ultralisk_Cavern,UnitName::UNIT_NULL},UnitName::Zerg_Ultralisk_Cavern,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Chitinous Plating",
			150,150,'p', 0,0,
			{UnitName::Zerg_Ultralisk_Cavern,UnitName::UNIT_NULL},UnitName::Zerg_Ultralisk_Cavern,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Plague",
			200,200,1500,0,0,
			{UnitName::Zerg_Defiler_Mound,UnitName::UNIT_NULL},UnitName::Zerg_Defiler_Mound,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Consume",
			100,100,1500,0,0,
			{UnitName::Zerg_Defiler_Mound,UnitName::UNIT_NULL},UnitName::Zerg_Defiler_Mound,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Metasynaptic Node",
			150,150,'p', 0,0,
			{UnitName::Zerg_Defiler_Mound,UnitName::UNIT_NULL},UnitName::Zerg_Defiler_Mound,
			false, false,
			false, false, false,
			'r' },
		{ 'z', "Zerg Melee Attacks 1",
			100,100,4000,0,0,
			{UnitName::Zerg_Evolution_Chamber,UnitName::UNIT_NULL},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Melee Attacks 2",
			150,150,4480,0,0,
			{UnitName::Zerg_Melee_Attacks_1,UnitName::Zerg_Lair},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Melee Attacks 3",
			200,200,4960,0,0,
			{UnitName::Zerg_Melee_Attacks_2,UnitName::Zerg_Hive},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Missile Attacks 1",
			100,100,4000,0,0,
			{UnitName::Zerg_Evolution_Chamber,UnitName::UNIT_NULL},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Missile Attacks 2",
			150,150,4480,0,0,
			{UnitName::Zerg_Missile_Attacks_1,UnitName::Zerg_Lair},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Missile Attacks 3",
			200,200,4960,0,0,
			{UnitName::Zerg_Missile_Attacks_2,UnitName::Zerg_Hive},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Carapace 1",
			150,150,4000,0,0,
			{UnitName::Zerg_Evolution_Chamber,UnitName::UNIT_NULL},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Carapace 2",
			225,225,4480,0,0,
			{UnitName::Zerg_Carapace_1,UnitName::Zerg_Lair},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Carapace 3",
			300,300,4960,0,0,
			{UnitName::Zerg_Carapace_2,UnitName::Zerg_Hive},UnitName::Zerg_Evolution_Chamber,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Flyer Attacks 1",
			100,100,4000,0,0,
			{UnitName::Zerg_Spire,UnitName::UNIT_NULL},UnitName::Zerg_Spire,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Flyer Attacks 2",
			175,175,4480,0,0,
			{UnitName::Zerg_Flyer_Attacks_1,UnitName::Zerg_Lair},UnitName::Zerg_Spire,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Flyer Attacks 3",
			250,250,4960,0,0,
			{UnitName::Zerg_Flyer_Attacks_2,UnitName::Zerg_Hive},UnitName::Zerg_Spire,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Flyer Carapace 1",
			150,150,4000,0,0,
			{UnitName::Zerg_Spire,UnitName::UNIT_NULL},UnitName::Zerg_Spire,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Flyer Carapace 2",
			225,225,4480,0,0,
			{UnitName::Zerg_Flyer_Carapace_1,UnitName::Zerg_Lair},UnitName::Zerg_Spire,
			false, false,
			false, false, false,
			'n' },
		{ 'z', "Zerg Flyer Carapace 3",
			300,300,4960,0,0,
			{UnitName::Zerg_Flyer_Carapace_2,UnitName::Zerg_Hive},UnitName::Zerg_Spire,
			false, false,
			false, false, false,
			'n' }
	}
{
	//
}
