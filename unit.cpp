#include "unit.h"

namespace {
    struct UnitCost {
        UnitCost(Unit::UnitName u, std::string n, int m, int g, int t, int s = 0, int sm = 0)
            : un{u}, name{n}, min{m}, gas{g}, time{t}, sup{s}, sup_max{sm}
        { }

        Unit::UnitName un;
        std::string name;
        int min, gas, time, sup, sup_max;
    };

    std::vector<UnitCost> unit_costs {
        { Unit::Terran_SCV, "Terran SCV", 50, 0, 300, 1 },
        { Unit::Terran_Marine, "Terran Marine", 50, 0, 360, 1 },
	    { Unit::Terran_Firebat, "Terran Firebat", 50, 25, 360, 1 },
	    { Unit::Terran_Ghost, "Terran Ghost", 25, 75, 750, 1 },
	    { Unit::Terran_Medic, "Terran Medic", 50, 25, 450, 1 },
	    { Unit::Terran_Vulture, "Terran Vulture", 75, 0, 450, 2 },
	    { Unit::Terran_Goliath, "Terran Goliath", 100, 50, 600, 2 },
	    { Unit::Terran_Siege_Tank, "Terran Siege Tank", 150, 100, 750, 2 },
	    { Unit::Terran_Wraith, "Terran Wraith", 150, 100, 900, 2 },
	    { Unit::Terran_Dropship, "Terran Dropship", 100, 100, 750, 2 },
	    { Unit::Terran_Valkyrie, "Terran Valkyrie", 250, 125, 750, 3 },
	    { Unit::Terran_Science_Vessel, "Terran Science Vessel", 100, 225, 1200, 2 },
	    { Unit::Terran_Battlecruiser, "Terran Battlecruiser", 400, 300, 2000, 6 },
	    { Unit::Terran_Command_Center, "Terran Command Center", 400, 0, 1800, 0, 10 },
	    { Unit::Terran_Supply_Depot, "Terran Supply Depot", 100, 0, 600, 0, 8 },
	    { Unit::Terran_Refinery, "Terran Refinery", 100, 0, 600 },
	    { Unit::Terran_Barracks, "Terran Barracks", 150, 0, 1200 },
	    { Unit::Terran_Engineering_Bay, "Terran Engineering Bay", 125, 0, 900 },
	    { Unit::Terran_Missile_Turret, "Terran Missile Turret", 75, 0, 450 },
	    { Unit::Terran_Academy, "Terran Academy", 150, 0, 1200 },
	    { Unit::Terran_Bunker, "Terran Bunker", 100, 0, 450 },
	    { Unit::Terran_Factory, "Terran Factory", 200, 100, 1200 },
	    { Unit::Terran_Armory, "Terran Armory", 100, 50, 1200 },
	    { Unit::Terran_Science_Facility, "Terran Science Facility", 100, 150, 900 },
	    { Unit::Terran_Starport, "Terran Starport", 150, 100, 1050 },
	    { Unit::Terran_Machine_Shop, "Terran Machine Shop", 50, 50, 600 },
	    { Unit::Terran_Control_Tower, "Terran Control Tower", 50, 50, 600 },
	    { Unit::Terran_Comsat_Station, "Terran Comsat Station", 50, 50, 600 },
	    { Unit::Terran_Nuclear_Silo, "Terran Nuclear Silo", 100, 100, 1200 },
	    { Unit::Terran_Physics_Lab, "Terran Physics Lab", 50, 50, 600 },
	    { Unit::Terran_Covert_Ops, "Terran Covert Ops", 50, 50, 600 },
	    { Unit::Terran_Nuclear_Missile, "Terran Nuclear Missile", 200, 200, 1500, 8 },
	    { Unit::Terran_U238_Shells, "Terran U-238 Shells", 150, 150, 1500 },
	    { Unit::Terran_Stim_Pack, "Terran Stim Pack", 100, 100, 1200 },
	    { Unit::Terran_Restoration, "Terran Restoration", 100, 100, 1200 },
	    { Unit::Terran_Optical_Flare, "Terran Optical Flare", 100, 100, 1200 },
	    { Unit::Terran_Caduceus_Reactor, "Terran Caduceus Reactor", 150, 150, 2500 },
	    { Unit::Terran_Ion_Thrusters, "Terran Ion Thrusters", 100, 100, 1500 },
	    { Unit::Terran_Spider_Mines, "Terran Spider Mines", 100, 100, 1200 },
	    { Unit::Terran_Siege_Tech, "Terran Siege Tech", 150, 150, 1200 },
	    { Unit::Terran_Charon_Boosters, "Terran Charon Boosters", 100, 100, 2000 },
	    { Unit::Terran_Cloaking_Field, "Terran Cloaking Field", 150, 150, 1500 },
	    { Unit::Terran_Apollo_Reactor, "Terran Apollo Reactor", 200, 200, 2500 },
	    { Unit::Terran_EMP_Shockwave, "Terran EMP Shockwave", 200, 200, 1800 },
	    { Unit::Terran_Irradiate, "Terran Irradiate", 200, 200, 1200 },
	    { Unit::Terran_Titan_Reactor, "Terran Titan Reactor", 150, 150, 2500 },
	    { Unit::Terran_Lockdown, "Terran Lockdown", 200, 200, 1500 },
	    { Unit::Terran_Personnel_Cloaking, "Terran Personnel Cloaking", 100, 100, 1200 },
	    { Unit::Terran_Ocular_Implants, "Terran Ocular Implants", 100, 100, 2500 },
	    { Unit::Terran_Moebius_Reactor, "Terran Moebius Reactor", 150, 150, 2500 },
	    { Unit::Terran_Yamato_Gun, "Terran Yamato Gun", 100, 100, 1800 },
	    { Unit::Terran_Colossus_Reactor, "Terran Colossus Reactor", 150, 150, 2500 },
	    { Unit::Terran_Infantry_Weapons_1, "Terran Infantry Weapons 1", 100, 100, 4000 },
	    { Unit::Terran_Infantry_Weapons_2, "Terran Infantry Weapons 2", 175, 175, 4480 },
	    { Unit::Terran_Infantry_Weapons_3, "Terran Infantry Weapons 3", 250, 250, 4960 },
	    { Unit::Terran_Infantry_Armor_1, "Terran Infantry Armor 1", 100, 100, 4000 },
	    { Unit::Terran_Infantry_Armor_2, "Terran Infantry Armor 2", 175, 175, 4480 },
	    { Unit::Terran_Infantry_Armor_3, "Terran Infantry Armor 3", 250, 250, 4960 },
	    { Unit::Terran_Vehicle_Weapons_1, "Terran Vehicle Weapons 1", 100, 100, 4000 },
	    { Unit::Terran_Vehicle_Weapons_2, "Terran Vehicle Weapons 2", 175, 175, 4480 },
	    { Unit::Terran_Vehicle_Weapons_3, "Terran Vehicle Weapons 3", 250, 250, 4960 },
	    { Unit::Terran_Vehicle_Plating_1, "Terran Vehicle Plating 1", 100, 100, 4000 },
	    { Unit::Terran_Vehicle_Plating_2, "Terran Vehicle Plating 2", 175, 175, 4480 },
	    { Unit::Terran_Vehicle_Plating_3, "Terran Vehicle Plating 3", 250, 250, 4960 },
	    { Unit::Terran_Ship_Weapons_1, "Terran Ship Weapons 1", 100, 100, 4000 },
	    { Unit::Terran_Ship_Weapons_2, "Terran Ship Weapons 2", 175, 175, 4480 },
	    { Unit::Terran_Ship_Weapons_3, "Terran Ship Weapons 3", 250, 250, 4960 },
	    { Unit::Terran_Ship_Plating_1, "Terran Ship Plating 1", 100, 100, 4000 },
	    { Unit::Terran_Ship_Plating_2, "Terran Ship Plating 2", 175, 175, 4480 },
	    { Unit::Terran_Ship_Plating_3, "Terran Ship Plating 3", 250, 250, 4960 }
    };

    std::vector <Unit::UnitName> unit_builder {
        Unit::Terran_Command_Center, // Unit::Terran_SCV
        Unit::Terran_Barracks, // Unit::Terran_Marine
        Unit::Terran_Barracks, // Unit::Terran_Firebat
        Unit::Terran_Barracks, // Unit::Terran_Ghost
        Unit::Terran_Barracks, // Unit::Terran_Medic
        Unit::Terran_Factory, // Unit::Terran_Vulture
        Unit::Terran_Factory, // Unit::Terran_Goliath
        Unit::Terran_Factory, // Unit::Terran_Siege_Tank
        Unit::Terran_Starport, // Unit::Terran_Wraith
        Unit::Terran_Starport, // Unit::Terran_Dropship
        Unit::Terran_Starport, // Unit::Terran_Valkyrie
        Unit::Terran_Starport, // Unit::Terran_Science_Vessel
        Unit::Terran_Starport, // Unit::Terran_Battlecruiser
        Unit::Terran_SCV, // Unit::Terran_Command_Center
        Unit::Terran_SCV, // Unit::Terran_Supply_Depot
        Unit::Terran_SCV, // Unit::Terran_Refinery
        Unit::Terran_SCV, // Unit::Terran_Barracks
        Unit::Terran_SCV, // Unit::Terran_Engineering_Bay
        Unit::Terran_SCV, // Unit::Terran_Missile_Turret
        Unit::Terran_SCV, // Unit::Terran_Academy
        Unit::Terran_SCV, // Unit::Terran_Bunker
        Unit::Terran_SCV, // Unit::Terran_Factory
        Unit::Terran_SCV, // Unit::Terran_Armory
        Unit::Terran_SCV, // Unit::Terran_Science_Facility
        Unit::Terran_SCV, // Unit::Terran_Starport
        Unit::Terran_Factory, // Unit::Terran_Machine_Shop
        Unit::Terran_Starport, // Unit::Terran_Control_Tower
        Unit::Terran_Command_Center, // Unit::Terran_Comsat_Station
        Unit::Terran_Command_Center, // Unit::Terran_Nuclear_Silo
        Unit::Terran_Science_Facility, // Unit::Terran_Physics_Lab
        Unit::Terran_Science_Facility, // Unit::Terran_Covert_Ops
        Unit::Terran_Nuclear_Silo, // Unit::Terran_Nuclear_Missile
        Unit::Terran_Academy, // Unit::Terran_U238_Shells
        Unit::Terran_Academy, // Unit::Terran_Stim_Pack
        Unit::Terran_Academy, // Unit::Terran_Restoration
        Unit::Terran_Academy, // Unit::Terran_Optical_Flare
        Unit::Terran_Academy, // Unit::Terran_Caduceus_Reactor
        Unit::Terran_Machine_Shop, // Unit::Terran_Ion_Thrusters
        Unit::Terran_Machine_Shop, // Unit::Terran_Spider_Mines
        Unit::Terran_Machine_Shop, // Unit::Terran_Siege_Tech
        Unit::Terran_Machine_Shop, // Unit::Terran_Charon_Boosters
        Unit::Terran_Control_Tower, // Unit::Terran_Cloaking_Field
        Unit::Terran_Control_Tower, // Unit::Terran_Apollo_Reactor
        Unit::Terran_Science_Facility, // Unit::Terran_EMP_Shockwave
        Unit::Terran_Science_Facility, // Unit::Terran_Irradiate
        Unit::Terran_Science_Facility, // Unit::Terran_Titan_Reactor
        Unit::Terran_Covert_Ops, // Unit::Terran_Lockdown
        Unit::Terran_Covert_Ops, // Unit::Terran_Personnel_Cloaking
        Unit::Terran_Covert_Ops, // Unit::Terran_Ocular_Implants
        Unit::Terran_Covert_Ops, // Unit::Terran_Moebius_Reactor
        Unit::Terran_Physics_Lab, // Unit::Terran_Yamato_Gun
        Unit::Terran_Physics_Lab, // Unit::Terran_Colossus_Reactor
        Unit::Terran_Engineering_Bay, // Unit::Terran_Infantry_Weapons_1
        Unit::Terran_Engineering_Bay, // Unit::Terran_Infantry_Weapons_2
        Unit::Terran_Engineering_Bay, // Unit::Terran_Infantry_Weapons_3
        Unit::Terran_Engineering_Bay, // Unit::Terran_Infantry_Armor_1
        Unit::Terran_Engineering_Bay, // Unit::Terran_Infantry_Armor_2
        Unit::Terran_Engineering_Bay, // Unit::Terran_Infantry_Armor_3
        Unit::Terran_Armory, // Unit::Terran_Vehicle_Weapons_1
        Unit::Terran_Armory, // Unit::Terran_Vehicle_Weapons_2
        Unit::Terran_Armory, // Unit::Terran_Vehicle_Weapons_3
        Unit::Terran_Armory, // Unit::Terran_Vehicle_Plating_1
        Unit::Terran_Armory, // Unit::Terran_Vehicle_Plating_2
        Unit::Terran_Armory, // Unit::Terran_Vehicle_Plating_3
        Unit::Terran_Armory, // Unit::Terran_Ship_Weapons_1
        Unit::Terran_Armory, // Unit::Terran_Ship_Weapons_2
        Unit::Terran_Armory, // Unit::Terran_Ship_Weapons_3
        Unit::Terran_Armory, // Unit::Terran_Ship_Plating_1
        Unit::Terran_Armory, // Unit::Terran_Ship_Plating_2
        Unit::Terran_Armory // Unit::Terran_Ship_Plating_3
    };

    std::multimap <Unit::UnitName, Unit::UnitName> unit_prereq {
        { Unit::Terran_SCV, Unit::Terran_Command_Center },
        { Unit::Terran_Marine, Unit::Terran_Barracks },
        { Unit::Terran_Firebat, Unit::Terran_Academy },
        { Unit::Terran_Ghost, Unit::Terran_Academy },
        { Unit::Terran_Ghost, Unit::Terran_Covert_Ops },
        { Unit::Terran_Medic, Unit::Terran_Academy },
        { Unit::Terran_Vulture, Unit::Terran_Factory },
        { Unit::Terran_Goliath, Unit::Terran_Armory },
        { Unit::Terran_Siege_Tank, Unit::Terran_Machine_Shop },
        { Unit::Terran_Wraith, Unit::Terran_Starport },
        { Unit::Terran_Dropship, Unit::Terran_Control_Tower },
        { Unit::Terran_Valkyrie, Unit::Terran_Armory },
        { Unit::Terran_Valkyrie, Unit::Terran_Control_Tower },
        { Unit::Terran_Science_Vessel, Unit::Terran_Science_Facility },
        { Unit::Terran_Science_Vessel, Unit::Terran_Control_Tower },
        { Unit::Terran_Battlecruiser, Unit::Terran_Physics_Lab },
        { Unit::Terran_Battlecruiser, Unit::Terran_Control_Tower },
        { Unit::Terran_Command_Center, Unit::Terran_SCV },
        { Unit::Terran_Supply_Depot, Unit::Terran_SCV },
        { Unit::Terran_Refinery, Unit::Terran_SCV },
        { Unit::Terran_Barracks, Unit::Terran_Command_Center },
        { Unit::Terran_Engineering_Bay, Unit::Terran_Command_Center },
        { Unit::Terran_Missile_Turret, Unit::Terran_Engineering_Bay },
        { Unit::Terran_Academy, Unit::Terran_Barracks },
        { Unit::Terran_Bunker, Unit::Terran_Barracks },
        { Unit::Terran_Factory, Unit::Terran_Barracks },
        { Unit::Terran_Armory, Unit::Terran_Factory },
        { Unit::Terran_Science_Facility, Unit::Terran_Starport },
        { Unit::Terran_Starport, Unit::Terran_Factory },
	    { Unit::Terran_Machine_Shop, Unit::Terran_Factory },
	    { Unit::Terran_Control_Tower, Unit::Terran_Starport },
	    { Unit::Terran_Comsat_Station, Unit::Terran_Academy },
	    { Unit::Terran_Nuclear_Silo, Unit::Terran_Covert_Ops },
	    { Unit::Terran_Physics_Lab, Unit::Terran_Science_Facility },
	    { Unit::Terran_Covert_Ops, Unit::Terran_Science_Facility },
	    { Unit::Terran_Nuclear_Missile, Unit::Terran_Covert_Ops },
	    { Unit::Terran_U238_Shells, Unit::Terran_Academy },
	    { Unit::Terran_Stim_Pack, Unit::Terran_Academy },
	    { Unit::Terran_Restoration, Unit::Terran_Academy },
	    { Unit::Terran_Optical_Flare, Unit::Terran_Academy },
	    { Unit::Terran_Caduceus_Reactor, Unit::Terran_Academy },
	    { Unit::Terran_Ion_Thrusters, Unit::Terran_Machine_Shop },
	    { Unit::Terran_Spider_Mines, Unit::Terran_Machine_Shop },
	    { Unit::Terran_Siege_Tech, Unit::Terran_Machine_Shop },
	    { Unit::Terran_Charon_Boosters, Unit::Terran_Machine_Shop },
	    { Unit::Terran_Cloaking_Field, Unit::Terran_Control_Tower },
	    { Unit::Terran_Apollo_Reactor, Unit::Terran_Control_Tower },
	    { Unit::Terran_EMP_Shockwave, Unit::Terran_Science_Facility },
	    { Unit::Terran_Irradiate, Unit::Terran_Science_Facility },
	    { Unit::Terran_Titan_Reactor, Unit::Terran_Science_Facility },
	    { Unit::Terran_Lockdown, Unit::Terran_Covert_Ops },
	    { Unit::Terran_Personnel_Cloaking, Unit::Terran_Covert_Ops },
	    { Unit::Terran_Ocular_Implants, Unit::Terran_Covert_Ops },
	    { Unit::Terran_Moebius_Reactor, Unit::Terran_Covert_Ops },
	    { Unit::Terran_Yamato_Gun, Unit::Terran_Physics_Lab },
	    { Unit::Terran_Colossus_Reactor, Unit::Terran_Physics_Lab },
	    { Unit::Terran_Infantry_Weapons_1, Unit::Terran_Engineering_Bay },
	    { Unit::Terran_Infantry_Weapons_2, Unit::Terran_Infantry_Weapons_1 },
	    { Unit::Terran_Infantry_Weapons_3, Unit::Terran_Infantry_Weapons_2 },
	    { Unit::Terran_Infantry_Armor_1, Unit::Terran_Engineering_Bay },
	    { Unit::Terran_Infantry_Armor_2, Unit::Terran_Infantry_Armor_1 },
	    { Unit::Terran_Infantry_Armor_3, Unit::Terran_Infantry_Armor_2 },
	    { Unit::Terran_Vehicle_Weapons_1, Unit::Terran_Armory },
	    { Unit::Terran_Vehicle_Weapons_2, Unit::Terran_Vehicle_Weapons_1 },
	    { Unit::Terran_Vehicle_Weapons_3, Unit::Terran_Vehicle_Weapons_2 },
	    { Unit::Terran_Vehicle_Plating_1, Unit::Terran_Armory },
	    { Unit::Terran_Vehicle_Plating_2, Unit::Terran_Vehicle_Plating_1 },
	    { Unit::Terran_Vehicle_Plating_3, Unit::Terran_Vehicle_Plating_2 },
	    { Unit::Terran_Ship_Weapons_1, Unit::Terran_Armory },
	    { Unit::Terran_Ship_Weapons_2, Unit::Terran_Ship_Weapons_1 },
	    { Unit::Terran_Ship_Weapons_3, Unit::Terran_Ship_Weapons_2 },
	    { Unit::Terran_Ship_Plating_1, Unit::Terran_Armory },
	    { Unit::Terran_Ship_Plating_2, Unit::Terran_Ship_Plating_1 },
	    { Unit::Terran_Ship_Plating_3, Unit::Terran_Ship_Plating_2 }
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

bool Unit::is_upgrade(UnitName u) {
    return (u >= Terran_U238_Shells && u <= Terran_Ship_Plating_3);
}

bool Unit::is_action(UnitName u) { return u > UNIT_NULL; }
std::string Unit::get_name(UnitName u) { return unit_costs[u].name; }
int Unit::get_min(UnitName u) { return unit_costs[u].min; }
int Unit::get_gas(UnitName u) { return unit_costs[u].gas; }
int Unit::get_sup(UnitName u) { return unit_costs[u].sup; }
int Unit::get_time(UnitName u) {
    int extra_time = 0;
    int WARP_TIME = 70;
    int MORPH_TIME = 18;
    if (u >= Protoss_Nexus && u <= Protoss_Templar_Archives)
        extra_time = WARP_TIME;
    if (u >= Zerg_Drone && u <= Zerg_Greater_Spire)
        extra_time = MORPH_TIME;
    return unit_costs[u].time;
}
int Unit::get_sup_max(UnitName u) { return unit_costs[u].sup_max; }
Unit::UnitName Unit::get_builder(UnitName u) { return unit_builder[u]; }
