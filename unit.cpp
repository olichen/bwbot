#include "unit.h"
using namespace Unit;

namespace {
    struct UnitData {
        UnitData(UnitName u, UnitName b, std::vector<UnitName> p,
                std::string n, int m, int g, int t, int s = 0, int sm = 0)
            : un{u}, builder{b}, prereq{p}, name{n}, min{m}, gas{g}, time{t}, sup{s}, sup_max{sm}
        { }

        UnitName un, builder;
        std::vector<UnitName> prereq;
        std::string name;
        int min, gas, time, sup, sup_max;
    };

    std::vector<UnitData> unit_data {
        { Terran_SCV, Terran_Command_Center, {},
            "Terran SCV", 50, 0, 300, 1 },
        { Terran_Marine, Terran_Barracks, {},
            "Terran Marine", 50, 0, 360, 1 },
	    { Terran_Firebat, Terran_Barracks, { Terran_Academy },
            "Terran Firebat", 50, 25, 360, 1 },
	    { Terran_Ghost, Terran_Barracks, { Terran_Academy, Terran_Covert_Ops },
            "Terran Ghost", 25, 75, 750, 1 },
	    { Terran_Medic, Terran_Barracks, { Terran_Academy },
            "Terran Medic", 50, 25, 450, 1 },
        { Terran_Vulture, Terran_Factory, {},
            "Terran Vulture", 75, 0, 450, 2 },
        { Terran_Goliath, Terran_Factory, { Terran_Armory },
            "Terran Goliath", 100, 50, 600, 2 },
        { Terran_Siege_Tank, Terran_Factory, { Terran_Machine_Shop },
            "Terran Siege Tank", 150, 100, 750, 2 },
        { Terran_Wraith, Terran_Starport, {},
            "Terran Wraith", 150, 100, 900, 2 },
        { Terran_Dropship, Terran_Starport, { Terran_Control_Tower },
            "Terran Dropship", 100, 100, 750, 2 },
        { Terran_Valkyrie, Terran_Starport, { Terran_Armory, Terran_Machine_Shop },
            "Terran Valkyrie", 250, 125, 750, 3 },
        { Terran_Science_Vessel, Terran_Starport, { Terran_Science_Facility },
            "Terran Science Vessel", 100, 225, 1200, 2 },
        { Terran_Battlecruiser, Terran_Starport, { Terran_Physics_Lab, Terran_Control_Tower },
            "Terran Battlecruiser", 400, 300, 2000, 6 },
        { Terran_Command_Center, Terran_SCV, {},
            "Terran Command Center", 400, 0, 1800, 0, 10 },
        { Terran_Supply_Depot, Terran_SCV, {},
            "Terran Supply Depot", 100, 0, 600, 0, 8 },
        { Terran_Refinery, Terran_SCV, {},
            "Terran Refinery", 100, 0, 600 },
        { Terran_Barracks, Terran_SCV, {},
            "Terran Barracks", 150, 0, 1200 },
        { Terran_Engineering_Bay, Terran_SCV, {},
            "Terran Engineering Bay", 125, 0, 900 },
        { Terran_Missile_Turret, Terran_SCV, { Terran_Engineering_Bay },
            "Terran Missile Turret", 75, 0, 450 },
        { Terran_Academy, Terran_SCV, { Terran_Barracks },
            "Terran Academy", 150, 0, 1200 },
        { Terran_Bunker, Terran_SCV, { Terran_Barracks },
            "Terran Bunker", 100, 0, 450 },
        { Terran_Factory, Terran_SCV, { Terran_Barracks },
            "Terran Factory", 200, 100, 1200 },
        { Terran_Armory, Terran_SCV, { Terran_Factory },
            "Terran Armory", 100, 50, 1200 },
        { Terran_Science_Facility, Terran_SCV, { Terran_Starport },
            "Terran Science Facility", 100, 150, 900 },
        { Terran_Starport, Terran_SCV, { Terran_Factory },
            "Terran Starport", 150, 100, 1050 },
        { Terran_Machine_Shop, Terran_Factory, {},
            "Terran Machine Shop", 50, 50, 600 },
        { Terran_Control_Tower, Terran_Starport, {},
            "Terran Control Tower", 50, 50, 600 },
        { Terran_Comsat_Station, Terran_Command_Center, { Terran_Academy },
            "Terran Comsat Station", 50, 50, 600 },
        { Terran_Nuclear_Silo, Terran_Command_Center, { Terran_Covert_Ops },
            "Terran Nuclear Silo", 100, 100, 1200 },
        { Terran_Physics_Lab, Terran_Science_Facility, {},
            "Terran Physics Lab", 50, 50, 600 },
        { Terran_Covert_Ops, Terran_Science_Facility, {},
            "Terran Covert Ops", 50, 50, 600 },
        { Terran_Nuclear_Missile, Terran_Nuclear_Silo, {},
            "Terran Nuclear Missile", 200, 200, 1500, 8 },
        { Terran_U238_Shells, Terran_Academy, {},
            "Terran U-238 Shells", 150, 150, 1500 },
        { Terran_Stim_Pack, Terran_Academy, {},
            "Terran Stim Pack", 100, 100, 1200 },
        { Terran_Restoration, Terran_Academy, {},
            "Terran Restoration", 100, 100, 1200 },
        { Terran_Optical_Flare, Terran_Academy, {},
            "Terran Optical Flare", 100, 100, 1200 },
        { Terran_Caduceus_Reactor, Terran_Academy, {},
            "Terran Caduceus Reactor", 150, 150, 2500 },
        { Terran_Ion_Thrusters, Terran_Machine_Shop, {},
            "Terran Ion Thrusters", 100, 100, 1500 },
        { Terran_Spider_Mines, Terran_Machine_Shop, {},
            "Terran Spider Mines", 100, 100, 1200 },
        { Terran_Siege_Tech, Terran_Machine_Shop, {},
            "Terran Siege Tech", 150, 150, 1200 },
        { Terran_Charon_Boosters, Terran_Machine_Shop, { Terran_Armory },
            "Terran Charon Boosters", 100, 100, 2000 },
        { Terran_Cloaking_Field, Terran_Control_Tower, {},
            "Terran Cloaking Field", 150, 150, 1500 },
        { Terran_Apollo_Reactor, Terran_Control_Tower, {},
            "Terran Apollo Reactor", 200, 200, 2500 },
        { Terran_EMP_Shockwave, Terran_Science_Facility, {},
            "Terran EMP Shockwave", 200, 200, 1800 },
        { Terran_Irradiate, Terran_Science_Facility, {},
            "Terran Irradiate", 200, 200, 1200 },
        { Terran_Titan_Reactor, Terran_Science_Facility, {},
            "Terran Titan Reactor", 150, 150, 2500 },
        { Terran_Lockdown, Terran_Covert_Ops, {},
            "Terran Lockdown", 200, 200, 1500 },
        { Terran_Personnel_Cloaking, Terran_Covert_Ops, {},
            "Terran Personnel Cloaking", 100, 100, 1200 },
        { Terran_Ocular_Implants, Terran_Covert_Ops, {},
            "Terran Ocular Implants", 100, 100, 2500 },
        { Terran_Moebius_Reactor, Terran_Covert_Ops, {},
            "Terran Moebius Reactor", 150, 150, 2500 },
        { Terran_Yamato_Gun, Terran_Physics_Lab, {},
            "Terran Yamato Gun", 100, 100, 1800 },
        { Terran_Colossus_Reactor, Terran_Physics_Lab, {},
            "Terran Colossus Reactor", 150, 150, 2500 },
        { Terran_Infantry_Weapons_1, Terran_Engineering_Bay, {},
            "Terran Infantry Weapons 1", 100, 100, 4000 },
        { Terran_Infantry_Weapons_2, Terran_Engineering_Bay, { Terran_Science_Facility, Terran_Infantry_Weapons_1 },
            "Terran Infantry Weapons 2", 175, 175, 4480 },
        { Terran_Infantry_Weapons_3, Terran_Engineering_Bay, { Terran_Infantry_Weapons_2 },
            "Terran Infantry Weapons 3", 250, 250, 4960 },
        { Terran_Infantry_Armor_1, Terran_Engineering_Bay, {},
            "Terran Infantry Armor 1", 100, 100, 4000 },
        { Terran_Infantry_Armor_2, Terran_Engineering_Bay, { Terran_Science_Facility, Terran_Infantry_Armor_1 },
            "Terran Infantry Armor 2", 175, 175, 4480 },
        { Terran_Infantry_Armor_3, Terran_Engineering_Bay, { Terran_Infantry_Armor_2 },
            "Terran Infantry Armor 3", 250, 250, 4960 },
        { Terran_Vehicle_Weapons_1, Terran_Armory, {},
            "Terran Vehicle Weapons 1", 100, 100, 4000 },
        { Terran_Vehicle_Weapons_2, Terran_Armory, { Terran_Science_Facility, Terran_Vehicle_Weapons_1 },
            "Terran Vehicle Weapons 2", 175, 175, 4480 },
        { Terran_Vehicle_Weapons_3, Terran_Armory, { Terran_Vehicle_Weapons_2 },
            "Terran Vehicle Weapons 3", 250, 250, 4960 },
        { Terran_Vehicle_Plating_1, Terran_Armory, {},
            "Terran Vehicle Plating 1", 100, 100, 4000 },
        { Terran_Vehicle_Plating_2, Terran_Armory, { Terran_Science_Facility, Terran_Vehicle_Plating_1 },
            "Terran Vehicle Plating 2", 175, 175, 4480 },
        { Terran_Vehicle_Plating_3, Terran_Armory, { Terran_Vehicle_Plating_2 },
            "Terran Vehicle Plating 3", 250, 250, 4960 },
        { Terran_Ship_Weapons_1, Terran_Armory, {},
            "Terran Ship Weapons 1", 100, 100, 4000 },
        { Terran_Ship_Weapons_2, Terran_Armory, { Terran_Science_Facility, Terran_Ship_Weapons_1 },
            "Terran Ship Weapons 2", 175, 175, 4480 },
        { Terran_Ship_Weapons_3, Terran_Armory,{ Terran_Ship_Weapons_2 },
            "Terran Ship Weapons 3", 250, 250, 4960 },
        { Terran_Ship_Plating_1, Terran_Armory, {},
            "Terran Ship Plating 1", 100, 100, 4000 },
        { Terran_Ship_Plating_2, Terran_Armory, { Terran_Science_Facility, Terran_Ship_Plating_1 },
            "Terran Ship Plating 2", 175, 175, 4480 },
        { Terran_Ship_Plating_3, Terran_Armory, { Terran_Ship_Plating_2 },
            "Terran Ship Plating 3", 250, 250, 4960 },
        { Protoss_Probe, Protoss_Nexus, {},
            "Protoss Probe", 50, 0, 300, 1 },
        { Protoss_Zealot, Protoss_Gateway, {},
            "Protoss Zealot", 100, 0, 600, 2 },
        { Protoss_Dragoon, Protoss_Gateway, { Protoss_Cybernetics_Core },
            "Protoss Dragoon", 125, 50, 750, 2 },
        { Protoss_High_Templar, Protoss_Gateway, { Protoss_Templar_Archives },
            "Protoss High Templar", 50, 150, 750, 2 },
        { Protoss_Dark_Templar, Protoss_Gateway, { Protoss_Templar_Archives },
            "Protoss Dark Templar", 125, 100, 750, 2 },
        { Protoss_Archon, Protoss_High_Templar, {},
            "Protoss Archon", 0, 0, 300 },
        { Protoss_Dark_Archon, Protoss_Dark_Templar, {},
            "Protoss Dark Archon", 0, 0, 300 },
        { Protoss_Scout, Protoss_Stargate, {},
            "Protoss Scout", 275, 125, 1200, 3 },
        { Protoss_Corsair, Protoss_Stargate, {},
            "Protoss Corsair", 150, 100, 600, 2 },
        { Protoss_Arbiter, Protoss_Stargate, { Protoss_Arbiter_Tribunal },
            "Protoss Arbiter", 100, 350, 2400, 4 },
        { Protoss_Carrier, Protoss_Stargate, { Protoss_Fleet_Beacon },
            "Protoss Carrier", 350, 200, 2100, 6 },
        { Protoss_Shuttle, Protoss_Robotics_Facility, {},
            "Protoss Shuttle", 200, 0, 900, 2 },
        { Protoss_Observer, Protoss_Robotics_Facility, { Protoss_Observatory },
            "Protoss Observer", 25, 75, 600, 1 },
        { Protoss_Reaver, Protoss_Robotics_Facility, { Protoss_Robotics_Support_Bay },
            "Protoss Reaver", 200, 100, 1050, 4 },
        { Protoss_Interceptor, Protoss_Carrier, {},
            "Protoss Interceptor", 25, 0, 300 },
        { Protoss_Scarab, Protoss_Reaver, {},
            "Protoss Scarab", 15, 0, 105 },
        { Protoss_Nexus, Protoss_Probe, {},
            "Protoss Nexus", 400, 0, 1800, 0, 9 },
        { Protoss_Pylon, Protoss_Probe, {},
            "Protoss Pylon", 100, 0, 450, 0, 8 },
        { Protoss_Assimilator, Protoss_Probe, {},
            "Protoss Assimilator", 100, 0, 600 },
        { Protoss_Gateway, Protoss_Probe, { Protoss_Pylon },
            "Protoss Gateway", 150, 0, 900 },
        { Protoss_Forge, Protoss_Probe, { Protoss_Pylon },
            "Protoss Forge", 150, 0, 600 },
        { Protoss_Photon_Cannon, Protoss_Probe, { Protoss_Forge },
            "Protoss Photon Cannon", 150, 0, 750 },
        { Protoss_Cybernetics_Core, Protoss_Probe, { Protoss_Gateway },
            "Protoss Cybernetics Core", 200, 0, 900 },
        { Protoss_Shield_Battery, Protoss_Probe, { Protoss_Gateway },
            "Protoss Shield Battery", 100, 0, 450 },
        { Protoss_Robotics_Facility, Protoss_Probe, { Protoss_Cybernetics_Core },
            "Protoss Robotics Facility", 200, 200, 1200 },
        { Protoss_Robotics_Support_Bay, Protoss_Probe, { Protoss_Robotics_Facility },
            "Protoss Robotics Support Bay", 150, 100, 450 },
        { Protoss_Observatory, Protoss_Probe, { Protoss_Robotics_Facility },
            "Protoss Observatory", 50, 100, 450 },
        { Protoss_Stargate, Protoss_Probe, { Protoss_Cybernetics_Core },
            "Protoss Stargate", 150, 150, 1050 },
        { Protoss_Fleet_Beacon, Protoss_Probe, { Protoss_Stargate },
            "Protoss Fleet Beacon", 300, 200, 900 },
        { Protoss_Arbiter_Tribunal, Protoss_Probe, { Protoss_Stargate, Protoss_Templar_Archives },
            "Protoss Arbiter Tribunal", 200, 150, 900 },
        { Protoss_Citadel_Of_Adun, Protoss_Probe, { Protoss_Cybernetics_Core },
            "Protoss Citadel Of Adun", 150, 100, 900 },
        { Protoss_Templar_Archives, Protoss_Probe, { Protoss_Citadel_Of_Adun },
            "Protoss Templar Archives", 150, 200, 900 },
        { Protoss_Singularity_Charge, Protoss_Cybernetics_Core, {},
            "Protoss Singularity Charge", 150, 150, 2500 },
        { Protoss_Leg_Enhancements, Protoss_Citadel_Of_Adun, {},
            "Protoss Leg Enhancements", 150, 150, 2000 },
        { Protoss_Scarab_Damage, Protoss_Robotics_Support_Bay, {},
            "Protoss Scarab Damage", 200, 200, 2500 },
        { Protoss_Reaver_Capacity, Protoss_Robotics_Support_Bay, {},
            "Protoss Reaver Capacity", 200, 200, 2500 },
        { Protoss_Gravitic_Drive, Protoss_Robotics_Support_Bay, {},
            "Protoss Gravitic Drive", 200, 200, 2500 },
        { Protoss_Sensor_Array, Protoss_Fleet_Beacon, {},
            "Protoss Sensor Array", 150, 150, 2000 },
        { Protoss_Gravitic_Boosters, Protoss_Fleet_Beacon, {},
            "Protoss Gravitic Boosters", 150, 150, 2000 },
        { Protoss_Psionic_Storm, Protoss_Templar_Archives, {},
            "Protoss Psionic Storm", 200, 200, 1800 },
        { Protoss_Hallucination, Protoss_Templar_Archives, {},
            "Protoss Hallucination", 150, 150, 1200 },
        { Protoss_Khaydarin_Amulet, Protoss_Templar_Archives, {},
            "Protoss Khaydarin Amulet", 150, 150, 2500 },
        { Protoss_Maelstrom, Protoss_Templar_Archives, {},
            "Protoss Maelstrom", 100, 100, 1500 },
        { Protoss_Mind_Control, Protoss_Templar_Archives, {},
            "Protoss Mind Control", 200, 200, 1800 },
        { Protoss_Argus_Talisman, Protoss_Templar_Archives, {},
            "Protoss Argus Talisman", 150, 150, 2500 },
        { Protoss_Apial_Sensors, Protoss_Fleet_Beacon, {},
            "Protoss Apial Sensors", 100, 100, 2500 },
        { Protoss_Gravitic_Thrusters, Protoss_Fleet_Beacon, {},
            "Protoss Gravitic Thrusters", 200, 200, 2500 },
        { Protoss_Carrier_Capacity, Protoss_Fleet_Beacon, {},
            "Protoss Carrier Capacity", 100, 100, 1500 },
        { Protoss_Disruption_Web, Protoss_Fleet_Beacon, {},
            "Protoss Disruption Web", 200, 200, 1200 },
        { Protoss_Argus_Jewel, Protoss_Fleet_Beacon, {},
            "Protoss Argus Jewel", 100, 100, 2500 },
        { Protoss_Recall, Protoss_Arbiter_Tribunal, {},
            "Protoss Recall", 150, 150, 1800 },
        { Protoss_Stasis_Field, Protoss_Arbiter_Tribunal, {},
            "Protoss Stasis Field", 150, 150, 1500 },
        { Protoss_Khaydarin_Core, Protoss_Arbiter_Tribunal, {},
            "Protoss Khaydarin Core", 150, 150, 2500 },
        { Protoss_Ground_Weapons_1, Protoss_Forge, {},
            "Protoss Ground Weapons 1", 100, 100, 4000 },
        { Protoss_Ground_Weapons_2, Protoss_Forge, { Protoss_Ground_Weapons_1, Protoss_Templar_Archives },
            "Protoss Ground Weapons 2", 175, 175, 4480 },
        { Protoss_Ground_Weapons_3, Protoss_Forge, { Protoss_Ground_Weapons_2 },
            "Protoss Ground Weapons 3", 250, 250, 4960 },
        { Protoss_Ground_Armor_1, Protoss_Forge, {},
            "Protoss Ground Armor 1", 100, 100, 4000 },
        { Protoss_Ground_Armor_2, Protoss_Forge, { Protoss_Ground_Armor_1, Protoss_Templar_Archives },
            "Protoss Ground Armor 2", 175, 175, 4480 },
        { Protoss_Ground_Armor_3, Protoss_Forge, { Protoss_Ground_Armor_2 },
            "Protoss Ground Armor 3", 250, 250, 4960 },
        { Protoss_Plasma_Shields_1, Protoss_Forge, {},
            "Protoss Plasma Shields 1", 200, 200, 4000 },
        { Protoss_Plasma_Shields_2, Protoss_Forge, { Protoss_Plasma_Shields_1, Protoss_Cybernetics_Core },
            "Protoss Plasma Shields 2", 300, 300, 4480 },
        { Protoss_Plasma_Shields_3, Protoss_Forge, { Protoss_Plasma_Shields_2 },
            "Protoss Plasma Shields 3", 400, 400, 4960 },
        { Protoss_Air_Weapons_1, Protoss_Cybernetics_Core, {},
            "Protoss Air Weapons 1", 100, 100, 4000 },
        { Protoss_Air_Weapons_2, Protoss_Cybernetics_Core, { Protoss_Air_Weapons_1, Protoss_Fleet_Beacon },
            "Protoss Air Weapons 2", 175, 175, 4480 },
        { Protoss_Air_Weapons_3, Protoss_Cybernetics_Core, { Protoss_Air_Weapons_2 },
            "Protoss Air Weapons 3", 250, 250, 4960 },
        { Protoss_Air_Armor_1, Protoss_Cybernetics_Core, {},
            "Protoss Air Armor 1", 100, 100, 4000 },
        { Protoss_Air_Armor_2, Protoss_Cybernetics_Core, { Protoss_Air_Armor_1, Protoss_Fleet_Beacon },
            "Protoss Air Armor 2", 175, 175, 4480 },
        { Protoss_Air_Armor_3, Protoss_Cybernetics_Core, { Protoss_Air_Armor_2 },
            "Protoss Air Armor 3", 250, 250, 4960 },
        { Zerg_Drone, Zerg_Larva, {},
            "Zerg Drone", 50, 0, 300, 1 },
        { Zerg_Larva, UNIT_NULL, {},
            "Zerg Larva", 0, 0, 342 },
        { Zerg_Zergling, Zerg_Larva, { Zerg_Spawning_Pool },
            "Zerg Zergling", 50, 0, 420, 1 },
        { Zerg_Hydralisk, Zerg_Larva, { Zerg_Hydralisk_Den },
            "Zerg Hydralisk", 75, 25, 420, 1 },
        { Zerg_Lurker, Zerg_Hydralisk, { Zerg_Lurker_Aspect },
            "Zerg Lurker", 50, 100, 600, 2 },
        { Zerg_Ultralisk, Zerg_Larva, { Zerg_Ultralisk_Cavern },
            "Zerg Ultralisk", 200, 200, 900, 4 },
        { Zerg_Defiler, Zerg_Larva, { Zerg_Defiler_Mound },
            "Zerg Defiler", 50, 150, 750, 2 },
        { Zerg_Overlord, Zerg_Larva, {},
            "Zerg Overlord", 100, 0, 600, 0, 8 },
        { Zerg_Mutalisk, Zerg_Larva, { Zerg_Spire },
            "Zerg Mutalisk", 100, 100, 600, 2 },
        { Zerg_Scourge, Zerg_Larva, { Zerg_Spire },
            "Zerg Scourge", 25, 75, 450, 1 },
        { Zerg_Queen, Zerg_Larva, { Zerg_Queens_Nest },
            "Zerg Queen", 100, 100, 750, 2 },
        { Zerg_Guardian, Zerg_Mutalisk, { Zerg_Greater_Spire },
            "Zerg Guardian", 50, 100, 600, 2 },
        { Zerg_Devourer, Zerg_Mutalisk, { Zerg_Greater_Spire },
            "Zerg Devourer", 150, 50, 600, 2 },
        { Zerg_Hatchery, Zerg_Drone, {},
            "Zerg Hatchery", 300, 0, 1800, 0, 1 },
        { Zerg_Extractor, Zerg_Drone, {},
            "Zerg Extractor", 50, 0, 600 },
        { Zerg_Spawning_Pool, Zerg_Drone, {},
            "Zerg Spawning Pool", 200, 0, 1200 },
        { Zerg_Evolution_Chamber, Zerg_Drone, {},
            "Zerg Evolution Chamber", 75, 0, 600 },
        { Zerg_Hydralisk_Den, Zerg_Drone, { Zerg_Spawning_Pool },
            "Zerg Hydralisk Den", 100, 50, 600 },
        { Zerg_Creep_Colony, Zerg_Drone, { Zerg_Hatchery },
            "Zerg Creep Colony", 75, 0, 300 },
        { Zerg_Sunken_Colony, Zerg_Creep_Colony, { Zerg_Spawning_Pool },
            "Zerg Sunken Colony", 50, 0, 300 },
        { Zerg_Spore_Colony, Zerg_Creep_Colony, { Zerg_Evolution_Chamber },
            "Zerg Spore Colony", 50, 0, 300 },
        { Zerg_Lair, Zerg_Hatchery, { Zerg_Spawning_Pool },
            "Zerg Lair", 150, 100, 1500, 0, 1 },
        { Zerg_Hive, Zerg_Lair, { Zerg_Queens_Nest },
            "Zerg Hive", 200, 150, 1800, 0, 1 },
        { Zerg_Spire, Zerg_Drone, { Zerg_Lair },
            "Zerg Spire", 200, 150, 1800 },
        { Zerg_Queens_Nest, Zerg_Drone, { Zerg_Lair },
            "Zerg Queen's Nest", 150, 100, 900 },
        { Zerg_Nydus_Canal, Zerg_Drone, { Zerg_Hive },
            "Zerg Nydus Canal", 150, 0, 600 },
        { Zerg_Ultralisk_Cavern, Zerg_Drone, { Zerg_Hive },
            "Zerg Ultralisk Cavern", 150, 200, 1200 },
        { Zerg_Defiler_Mound, Zerg_Drone, { Zerg_Hive },
            "Zerg Defiler Mound", 100, 100, 900 },
        { Zerg_Greater_Spire, Zerg_Spire, { Zerg_Hive },
            "Zerg Greater Spire", 100, 150, 1800 },
        { Zerg_Burrowing, Zerg_Hatchery, {},
            "Zerg Burrowing", 100, 100, 1200 },
        { Zerg_Ventral_Sacs, Zerg_Lair, {},
            "Zerg Ventral Sacs", 200, 200, 2400 },
        { Zerg_Antennae, Zerg_Lair, {},
            "Zerg Antennae", 150, 150, 2000 },
        { Zerg_Pneumatized_Carapace, Zerg_Lair, {},
            "Zerg Pneumatized Carapace", 150, 150, 2000 },
        { Zerg_Metabolic_Boost, Zerg_Spawning_Pool, {},
            "Zerg Metabolic Boost", 100, 100, 1500 },
        { Zerg_Adrenal_Glands, Zerg_Spawning_Pool, { Zerg_Hive },
            "Zerg Adrenal Glands", 200, 200, 1500 },
        { Zerg_Muscular_Augments, Zerg_Hydralisk_Den, {},
            "Zerg Muscular Augments", 150, 150, 1500 },
        { Zerg_Grooved_Spines, Zerg_Hydralisk_Den, {},
            "Zerg Grooved Spines", 150, 150, 1500 },
        { Zerg_Lurker_Aspect, Zerg_Hydralisk_Den, { Zerg_Lair },
            "Zerg Lurker Aspect", 200, 200, 1800 },
        { Zerg_Spawn_Broodling, Zerg_Queens_Nest, {},
            "Zerg Spawn Broodling", 150, 150, 1200 },
        { Zerg_Ensnare, Zerg_Queens_Nest, {},
            "Zerg Ensnare", 100, 100, 1200 },
        { Zerg_Gamete_Meiosis, Zerg_Queens_Nest, {},
            "Zerg Gamete Meiosis", 100, 100, 2500 },
        { Zerg_Anabolic_Synthesis, Zerg_Ultralisk_Cavern, {},
            "Zerg Anabolic Synthesis", 200, 200, 2000 },
        { Zerg_Chitinous_Plating, Zerg_Ultralisk_Cavern, {},
            "Zerg Chitinous Plating", 150, 150, 2000 },
        { Zerg_Plague, Zerg_Defiler_Mound, {},
            "Zerg Plague", 200, 200, 1500 },
        { Zerg_Consume, Zerg_Defiler_Mound, {},
            "Zerg Consume", 100, 100, 1500 },
        { Zerg_Metasynaptic_Node, Zerg_Defiler_Mound, {},
            "Zerg Metasynaptic Node", 150, 150, 2500 },
        { Zerg_Melee_Attacks_1, Zerg_Evolution_Chamber, {},
            "Zerg Melee Attacks 1", 100, 100, 4000 },
        { Zerg_Melee_Attacks_2, Zerg_Evolution_Chamber, { Zerg_Melee_Attacks_1, Zerg_Lair },
            "Zerg Melee Attacks 2", 150, 150, 4480 },
        { Zerg_Melee_Attacks_3, Zerg_Evolution_Chamber, { Zerg_Melee_Attacks_2, Zerg_Hive },
            "Zerg Melee Attacks 3", 200, 200, 4960 },
        { Zerg_Missile_Attacks_1, Zerg_Evolution_Chamber, {},
            "Zerg Missile Attacks 1", 100, 100, 4000 },
        { Zerg_Missile_Attacks_2, Zerg_Evolution_Chamber, { Zerg_Missile_Attacks_1, Zerg_Lair },
            "Zerg Missile Attacks 2", 150, 150, 4480 },
        { Zerg_Missile_Attacks_3, Zerg_Evolution_Chamber, { Zerg_Missile_Attacks_2, Zerg_Hive },
            "Zerg Missile Attacks 3", 200, 200, 4960 },
        { Zerg_Carapace_1, Zerg_Evolution_Chamber, {},
            "Zerg Carapace 1", 150, 150, 4000 },
        { Zerg_Carapace_2, Zerg_Evolution_Chamber, { Zerg_Carapace_1, Zerg_Lair },
            "Zerg Carapace 2", 225, 225, 4480 },
        { Zerg_Carapace_3, Zerg_Evolution_Chamber, { Zerg_Carapace_2, Zerg_Hive },
            "Zerg Carapace 3", 300, 300, 4960 },
        { Zerg_Flyer_Attacks_1, Zerg_Spire, {},
            "Zerg Flyer Attacks 1", 100, 100, 4000 },
        { Zerg_Flyer_Attacks_2, Zerg_Spire, { Zerg_Flyer_Attacks_1, Zerg_Lair },
            "Zerg Flyer Attacks 2", 175, 175, 4480 },
        { Zerg_Flyer_Attacks_3, Zerg_Spire, { Zerg_Flyer_Attacks_2, Zerg_Hive },
            "Zerg Flyer Attacks 3", 250, 250, 4960 },
        { Zerg_Flyer_Carapace_1, Zerg_Spire, {},
            "Zerg Flyer Carapace 1", 150, 150, 4000 },
        { Zerg_Flyer_Carapace_2, Zerg_Spire, { Zerg_Flyer_Carapace_1, Zerg_Lair },
            "Zerg Flyer Carapace 2", 225, 225, 4480 },
        { Zerg_Flyer_Carapace_3, Zerg_Spire, { Zerg_Flyer_Carapace_2, Zerg_Hive },
            "Zerg Flyer Carapace 3", 300, 300, 4960 }
    };
}

bool Unit::is_worker(UnitName u) {
    return u == Terran_SCV || u == Protoss_Probe || u == Zerg_Drone;
}
bool Unit::is_gas(UnitName u) {
    return u == Terran_Refinery || u == Protoss_Assimilator || u == Zerg_Extractor;
}
bool Unit::is_addon(UnitName u) {
    return u >= Terran_Machine_Shop && u <= Terran_Covert_Ops;
}
bool Unit::req_addon(UnitName u) {
    return (u == Terran_Siege_Tank) || (u >= Terran_Dropship && u <= Terran_Battlecruiser);
}
UnitName Unit::get_addon(UnitName u) {
    switch (u) {
        case Terran_Factory:
            return Terran_Machine_Shop;
        case Terran_Starport:
            return Terran_Control_Tower;
    }
    throw "no addon";
}
UnitName Unit::get_addon_parent(UnitName u) {
    switch (u) {
        case Terran_Machine_Shop:
            return Terran_Factory;
        case Terran_Control_Tower:
            return Terran_Starport;
        case Terran_Comsat_Station:
        case Terran_Nuclear_Silo:
            return Terran_Command_Center;
        case Terran_Physics_Lab:
        case Terran_Covert_Ops:
            return Terran_Science_Facility;
    }
    throw "no addon parent";
}
UnitName Unit::get_addon_sibling(UnitName u) {
    switch (u) {
        case Terran_Comsat_Station:
            return Terran_Nuclear_Silo;
        case Terran_Nuclear_Silo:
            return Terran_Comsat_Station;
        case Terran_Physics_Lab:
            return Terran_Covert_Ops;
        case Terran_Covert_Ops:
            return Terran_Physics_Lab;
        case Terran_Machine_Shop:
        case Terran_Control_Tower:
            return UNIT_NULL;
    }
    throw "no addon sibling";
}
bool Unit::is_upgrade(UnitName u) {
    return (u >= Terran_U238_Shells && u <= Terran_Ship_Plating_3)
        || (u >= Protoss_Singularity_Charge && u <= Protoss_Air_Armor_3)
        || (u >= Zerg_Burrowing && u <= Zerg_Flyer_Carapace_3);
}
bool Unit::is_action(UnitName u) {
    return u > UNIT_NULL;
}
bool Unit::is_warp(UnitName u) {
    return u >= Protoss_Nexus && u <= Protoss_Templar_Archives;
}
bool Unit::is_morph(UnitName u) {
    return u >= Zerg_Drone && u <= Zerg_Greater_Spire;
}

std::string Unit::get_name(UnitName u) { return unit_data[u].name; }
UnitName Unit::get_builder(UnitName u) { return unit_data[u].builder; }
std::vector<UnitName> Unit::get_prereq(UnitName u) { return unit_data[u].prereq; }
int Unit::get_min(UnitName u) { return unit_data[u].min; }
int Unit::get_gas(UnitName u) { return unit_data[u].gas; }
int Unit::get_sup(UnitName u) { return unit_data[u].sup; }
int Unit::get_sup_max(UnitName u) { return unit_data[u].sup_max; }
int Unit::get_time(UnitName u) {
    int extra_time = 0;
    int WARP_TIME = 70;
    int MORPH_TIME = 18;
    if (is_warp(u))
        extra_time = WARP_TIME;
    if (is_morph(u))
        extra_time = MORPH_TIME;
    return unit_data[u].time + extra_time;
}
