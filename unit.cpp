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
            "Terran Ship Plating 3", 250, 250, 4960 }
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
std::string Unit::get_name(UnitName u) { return unit_data[u].name; }
int Unit::get_min(UnitName u) { return unit_data[u].min; }
int Unit::get_gas(UnitName u) { return unit_data[u].gas; }
int Unit::get_sup(UnitName u) { return unit_data[u].sup; }
int Unit::get_time(UnitName u) {
    int extra_time = 0;
    int WARP_TIME = 70;
    int MORPH_TIME = 18;
    if (u >= Protoss_Nexus && u <= Protoss_Templar_Archives)
        extra_time = WARP_TIME;
    if (u >= Zerg_Drone && u <= Zerg_Greater_Spire)
        extra_time = MORPH_TIME;
    return unit_data[u].time + extra_time;
}
int Unit::get_sup_max(UnitName u) { return unit_data[u].sup_max; }
UnitName Unit::get_builder(UnitName u) { return unit_data[u].builder; }
