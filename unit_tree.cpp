#include "unit_tree.h"

UnitTree::UnitTree() {
    build[Unit::Terran_SCV] = Unit::Terran_Command_Center;
    build[Unit::Terran_Marine] = Unit::Terran_Barracks;
    build[Unit::Terran_Firebat] = Unit::Terran_Barracks;
    build[Unit::Terran_Ghost] = Unit::Terran_Barracks;
    build[Unit::Terran_Medic] = Unit::Terran_Barracks;
    build[Unit::Terran_Vulture] = Unit::Terran_Factory;
    build[Unit::Terran_Goliath] = Unit::Terran_Factory;
    build[Unit::Terran_Siege_Tank] = Unit::Terran_Factory;
    build[Unit::Terran_Wraith] = Unit::Terran_Starport;
    build[Unit::Terran_Dropship] = Unit::Terran_Starport;
    build[Unit::Terran_Valkyrie] = Unit::Terran_Starport;
    build[Unit::Terran_Science_Vessel] = Unit::Terran_Starport;
    build[Unit::Terran_Battlecruiser] = Unit::Terran_Starport;
    build[Unit::Terran_Command_Center] = Unit::Terran_SCV;
    build[Unit::Terran_Supply_Depot] = Unit::Terran_SCV;
    build[Unit::Terran_Refinery] = Unit::Terran_SCV;
    build[Unit::Terran_Barracks] = Unit::Terran_SCV;
    build[Unit::Terran_Engineering_Bay] = Unit::Terran_SCV;
    build[Unit::Terran_Missile_Turret] = Unit::Terran_SCV;
    build[Unit::Terran_Academy] = Unit::Terran_SCV;
    build[Unit::Terran_Bunker] = Unit::Terran_SCV;
    build[Unit::Terran_Factory] = Unit::Terran_SCV;
    build[Unit::Terran_Armory] = Unit::Terran_SCV;
    build[Unit::Terran_Science_Facility] = Unit::Terran_SCV;
    build[Unit::Terran_Starport] = Unit::Terran_SCV;
	build[Unit::Terran_Machine_Shop] = Unit::Terran_Factory;
	build[Unit::Terran_Control_Tower] = Unit::Terran_Starport;
	build[Unit::Terran_Comsat_Station] = Unit::Terran_Command_Center;
	build[Unit::Terran_Nuclear_Silo] = Unit::Terran_Command_Center;
	build[Unit::Terran_Physics_Lab] = Unit::Terran_Science_Facility;
	build[Unit::Terran_Covert_Ops] = Unit::Terran_Science_Facility;
	build[Unit::Terran_Nuclear_Missile] = Unit::Terran_Nuclear_Silo;
	build[Unit::Terran_U238_Shells] = Unit::Terran_Academy;
	build[Unit::Terran_Stim_Pack] = Unit::Terran_Academy;
	build[Unit::Terran_Restoration] = Unit::Terran_Academy;
	build[Unit::Terran_Optical_Flare] = Unit::Terran_Academy;
	build[Unit::Terran_Caduceus_Reactor] = Unit::Terran_Academy;
	build[Unit::Terran_Ion_Thrusters] = Unit::Terran_Machine_Shop;
	build[Unit::Terran_Spider_Mines] = Unit::Terran_Machine_Shop;
	build[Unit::Terran_Siege_Tech] = Unit::Terran_Machine_Shop;
	build[Unit::Terran_Charon_Boosters] = Unit::Terran_Machine_Shop;
	build[Unit::Terran_Cloaking_Field] = Unit::Terran_Control_Tower;
	build[Unit::Terran_Apollo_Reactor] = Unit::Terran_Control_Tower;
	build[Unit::Terran_EMP_Shockwave] = Unit::Terran_Science_Facility;
	build[Unit::Terran_Irradiate] = Unit::Terran_Science_Facility;
	build[Unit::Terran_Titan_Reactor] = Unit::Terran_Science_Facility;
	build[Unit::Terran_Lockdown] = Unit::Terran_Covert_Ops;
	build[Unit::Terran_Personnel_Cloaking] = Unit::Terran_Covert_Ops;
	build[Unit::Terran_Ocular_Implants] = Unit::Terran_Covert_Ops;
	build[Unit::Terran_Moebius_Reactor] = Unit::Terran_Covert_Ops;
	build[Unit::Terran_Yamato_Gun] = Unit::Terran_Physics_Lab;
	build[Unit::Terran_Colossus_Reactor] = Unit::Terran_Physics_Lab;
	build[Unit::Terran_Infantry_Weapons_1] = Unit::Terran_Engineering_Bay;
	build[Unit::Terran_Infantry_Weapons_2] = Unit::Terran_Engineering_Bay;
	build[Unit::Terran_Infantry_Weapons_3] = Unit::Terran_Engineering_Bay;
	build[Unit::Terran_Infantry_Armor_1] = Unit::Terran_Engineering_Bay;
	build[Unit::Terran_Infantry_Armor_2] = Unit::Terran_Engineering_Bay;
	build[Unit::Terran_Infantry_Armor_3] = Unit::Terran_Engineering_Bay;
	build[Unit::Terran_Vehicle_Weapons_1] = Unit::Terran_Armory;
	build[Unit::Terran_Vehicle_Weapons_2] = Unit::Terran_Armory;
	build[Unit::Terran_Vehicle_Weapons_3] = Unit::Terran_Armory;
	build[Unit::Terran_Vehicle_Plating_1] = Unit::Terran_Armory;
	build[Unit::Terran_Vehicle_Plating_2] = Unit::Terran_Armory;
	build[Unit::Terran_Vehicle_Plating_3] = Unit::Terran_Armory;
	build[Unit::Terran_Ship_Weapons_1] = Unit::Terran_Armory;
	build[Unit::Terran_Ship_Weapons_2] = Unit::Terran_Armory;
	build[Unit::Terran_Ship_Weapons_3] = Unit::Terran_Armory;
	build[Unit::Terran_Ship_Plating_1] = Unit::Terran_Armory;
	build[Unit::Terran_Ship_Plating_2] = Unit::Terran_Armory;
	build[Unit::Terran_Ship_Plating_3] = Unit::Terran_Armory;

    prereq.emplace(Unit::Terran_SCV, Unit::Terran_Command_Center);
    prereq.emplace(Unit::Terran_Marine, Unit::Terran_Barracks);
    prereq.emplace(Unit::Terran_Firebat, Unit::Terran_Academy);
    prereq.emplace(Unit::Terran_Ghost, Unit::Terran_Academy);
    prereq.emplace(Unit::Terran_Ghost, Unit::Terran_Covert_Ops);
    prereq.emplace(Unit::Terran_Medic, Unit::Terran_Academy);
    prereq.emplace(Unit::Terran_Vulture, Unit::Terran_Factory);
    prereq.emplace(Unit::Terran_Goliath, Unit::Terran_Armory);
    prereq.emplace(Unit::Terran_Siege_Tank, Unit::Terran_Machine_Shop);
    prereq.emplace(Unit::Terran_Wraith, Unit::Terran_Starport);
    prereq.emplace(Unit::Terran_Dropship, Unit::Terran_Control_Tower);
    prereq.emplace(Unit::Terran_Valkyrie, Unit::Terran_Armory);
    prereq.emplace(Unit::Terran_Valkyrie, Unit::Terran_Control_Tower);
    prereq.emplace(Unit::Terran_Science_Vessel, Unit::Terran_Science_Facility);
    prereq.emplace(Unit::Terran_Science_Vessel, Unit::Terran_Control_Tower);
    prereq.emplace(Unit::Terran_Battlecruiser, Unit::Terran_Physics_Lab);
    prereq.emplace(Unit::Terran_Battlecruiser, Unit::Terran_Control_Tower);
    prereq.emplace(Unit::Terran_Command_Center, Unit::Terran_SCV);
    prereq.emplace(Unit::Terran_Supply_Depot, Unit::Terran_SCV);
    prereq.emplace(Unit::Terran_Refinery, Unit::Terran_SCV);
    prereq.emplace(Unit::Terran_Barracks, Unit::Terran_Command_Center);
    prereq.emplace(Unit::Terran_Engineering_Bay, Unit::Terran_Command_Center);
    prereq.emplace(Unit::Terran_Missile_Turret, Unit::Terran_Engineering_Bay);
    prereq.emplace(Unit::Terran_Academy, Unit::Terran_Barracks);
    prereq.emplace(Unit::Terran_Bunker, Unit::Terran_Barracks);
    prereq.emplace(Unit::Terran_Factory, Unit::Terran_Barracks);
    prereq.emplace(Unit::Terran_Armory, Unit::Terran_Factory);
    prereq.emplace(Unit::Terran_Science_Facility, Unit::Terran_Starport);
    prereq.emplace(Unit::Terran_Starport, Unit::Terran_Factory);
	prereq.emplace(Unit::Terran_Machine_Shop, Unit::Terran_Factory);
	prereq.emplace(Unit::Terran_Control_Tower, Unit::Terran_Starport);
	prereq.emplace(Unit::Terran_Comsat_Station, Unit::Terran_Academy);
	prereq.emplace(Unit::Terran_Nuclear_Silo, Unit::Terran_Covert_Ops);
	prereq.emplace(Unit::Terran_Physics_Lab, Unit::Terran_Science_Facility);
	prereq.emplace(Unit::Terran_Covert_Ops, Unit::Terran_Science_Facility);
	prereq.emplace(Unit::Terran_Nuclear_Missile, Unit::Terran_Covert_Ops);
	prereq.emplace(Unit::Terran_U238_Shells, Unit::Terran_Academy);
	prereq.emplace(Unit::Terran_Stim_Pack, Unit::Terran_Academy);
	prereq.emplace(Unit::Terran_Restoration, Unit::Terran_Academy);
	prereq.emplace(Unit::Terran_Optical_Flare, Unit::Terran_Academy);
	prereq.emplace(Unit::Terran_Caduceus_Reactor, Unit::Terran_Academy);
	prereq.emplace(Unit::Terran_Ion_Thrusters, Unit::Terran_Machine_Shop);
	prereq.emplace(Unit::Terran_Spider_Mines, Unit::Terran_Machine_Shop);
	prereq.emplace(Unit::Terran_Siege_Tech, Unit::Terran_Machine_Shop);
	prereq.emplace(Unit::Terran_Charon_Boosters, Unit::Terran_Machine_Shop);
	prereq.emplace(Unit::Terran_Cloaking_Field, Unit::Terran_Control_Tower);
	prereq.emplace(Unit::Terran_Apollo_Reactor, Unit::Terran_Control_Tower);
	prereq.emplace(Unit::Terran_EMP_Shockwave, Unit::Terran_Science_Facility);
	prereq.emplace(Unit::Terran_Irradiate, Unit::Terran_Science_Facility);
	prereq.emplace(Unit::Terran_Titan_Reactor, Unit::Terran_Science_Facility);
	prereq.emplace(Unit::Terran_Lockdown, Unit::Terran_Covert_Ops);
	prereq.emplace(Unit::Terran_Personnel_Cloaking, Unit::Terran_Covert_Ops);
	prereq.emplace(Unit::Terran_Ocular_Implants, Unit::Terran_Covert_Ops);
	prereq.emplace(Unit::Terran_Moebius_Reactor, Unit::Terran_Covert_Ops);
	prereq.emplace(Unit::Terran_Yamato_Gun, Unit::Terran_Physics_Lab);
	prereq.emplace(Unit::Terran_Colossus_Reactor, Unit::Terran_Physics_Lab);
	prereq.emplace(Unit::Terran_Infantry_Weapons_1, Unit::Terran_Engineering_Bay);
	prereq.emplace(Unit::Terran_Infantry_Weapons_2, Unit::Terran_Infantry_Weapons_1);
	prereq.emplace(Unit::Terran_Infantry_Weapons_3, Unit::Terran_Infantry_Weapons_2);
	prereq.emplace(Unit::Terran_Infantry_Armor_1, Unit::Terran_Engineering_Bay);
	prereq.emplace(Unit::Terran_Infantry_Armor_2, Unit::Terran_Infantry_Armor_1);
	prereq.emplace(Unit::Terran_Infantry_Armor_3, Unit::Terran_Infantry_Armor_2);
	prereq.emplace(Unit::Terran_Vehicle_Weapons_1, Unit::Terran_Armory);
	prereq.emplace(Unit::Terran_Vehicle_Weapons_2, Unit::Terran_Vehicle_Weapons_1);
	prereq.emplace(Unit::Terran_Vehicle_Weapons_3, Unit::Terran_Vehicle_Weapons_2);
	prereq.emplace(Unit::Terran_Vehicle_Plating_1, Unit::Terran_Armory);
	prereq.emplace(Unit::Terran_Vehicle_Plating_2, Unit::Terran_Vehicle_Plating_1);
	prereq.emplace(Unit::Terran_Vehicle_Plating_3, Unit::Terran_Vehicle_Plating_2);
	prereq.emplace(Unit::Terran_Ship_Weapons_1, Unit::Terran_Armory);
	prereq.emplace(Unit::Terran_Ship_Weapons_2, Unit::Terran_Ship_Weapons_1);
	prereq.emplace(Unit::Terran_Ship_Weapons_3, Unit::Terran_Ship_Weapons_2);
	prereq.emplace(Unit::Terran_Ship_Plating_1, Unit::Terran_Armory);
	prereq.emplace(Unit::Terran_Ship_Plating_2, Unit::Terran_Ship_Plating_1);
	prereq.emplace(Unit::Terran_Ship_Plating_3, Unit::Terran_Ship_Plating_2);
}

bool UnitTree::is_addon(Unit u) {
    return (u >= Unit::Terran_Machine_Shop && u <= Unit::Terran_Covert_Ops);
}

bool UnitTree::req_addon(Unit u) {
    return ((u == Unit::Terran_Siege_Tank)
            || (u >= Unit::Terran_Dropship && u <= Unit::Terran_Battlecruiser));
}

bool UnitTree::is_upgrade(Unit u) {
    return (u >= Unit::Terran_U238_Shells && u <= Unit::Terran_Ship_Plating_3);
}
