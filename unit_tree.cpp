#include "unit_tree.h"

UnitTree::UnitTree() {
    build[UnitName::Terran_SCV] = UnitName::Terran_Command_Center;
    build[UnitName::Terran_Marine] = UnitName::Terran_Barracks;
    build[UnitName::Terran_Firebat] = UnitName::Terran_Barracks;
    build[UnitName::Terran_Ghost] = UnitName::Terran_Barracks;
    build[UnitName::Terran_Medic] = UnitName::Terran_Barracks;
    build[UnitName::Terran_Vulture] = UnitName::Terran_Factory;
    build[UnitName::Terran_Goliath] = UnitName::Terran_Factory;
    build[UnitName::Terran_Siege_Tank] = UnitName::Terran_Factory;
    build[UnitName::Terran_Wraith] = UnitName::Terran_Starport;
    build[UnitName::Terran_Dropship] = UnitName::Terran_Starport;
    build[UnitName::Terran_Valkyrie] = UnitName::Terran_Starport;
    build[UnitName::Terran_Science_Vessel] = UnitName::Terran_Starport;
    build[UnitName::Terran_Battlecruiser] = UnitName::Terran_Starport;
    build[UnitName::Terran_Command_Center] = UnitName::Terran_SCV;
    build[UnitName::Terran_Supply_Depot] = UnitName::Terran_SCV;
    build[UnitName::Terran_Refinery] = UnitName::Terran_SCV;
    build[UnitName::Terran_Barracks] = UnitName::Terran_SCV;
    build[UnitName::Terran_Engineering_Bay] = UnitName::Terran_SCV;
    build[UnitName::Terran_Missile_Turret] = UnitName::Terran_SCV;
    build[UnitName::Terran_Academy] = UnitName::Terran_SCV;
    build[UnitName::Terran_Bunker] = UnitName::Terran_SCV;
    build[UnitName::Terran_Factory] = UnitName::Terran_SCV;
    build[UnitName::Terran_Armory] = UnitName::Terran_SCV;
    build[UnitName::Terran_Science_Facility] = UnitName::Terran_SCV;
    build[UnitName::Terran_Starport] = UnitName::Terran_SCV;
	build[UnitName::Terran_Machine_Shop] = UnitName::Terran_Factory;
	build[UnitName::Terran_Control_Tower] = UnitName::Terran_Starport;
	build[UnitName::Terran_Comsat_Station] = UnitName::Terran_Command_Center;
	build[UnitName::Terran_Nuclear_Silo] = UnitName::Terran_Command_Center;
	build[UnitName::Terran_Physics_Lab] = UnitName::Terran_Science_Facility;
	build[UnitName::Terran_Covert_Ops] = UnitName::Terran_Science_Facility;
	build[UnitName::Terran_Nuclear_Missile] = UnitName::Terran_Nuclear_Silo;
	build[UnitName::Terran_U238_Shells] = UnitName::Terran_Academy;
	build[UnitName::Terran_Stim_Pack] = UnitName::Terran_Academy;
	build[UnitName::Terran_Restoration] = UnitName::Terran_Academy;
	build[UnitName::Terran_Optical_Flare] = UnitName::Terran_Academy;
	build[UnitName::Terran_Caduceus_Reactor] = UnitName::Terran_Academy;
	build[UnitName::Terran_Ion_Thrusters] = UnitName::Terran_Machine_Shop;
	build[UnitName::Terran_Spider_Mines] = UnitName::Terran_Machine_Shop;
	build[UnitName::Terran_Siege_Tech] = UnitName::Terran_Machine_Shop;
	build[UnitName::Terran_Charon_Boosters] = UnitName::Terran_Machine_Shop;
	build[UnitName::Terran_Cloaking_Field] = UnitName::Terran_Control_Tower;
	build[UnitName::Terran_Apollo_Reactor] = UnitName::Terran_Control_Tower;
	build[UnitName::Terran_EMP_Shockwave] = UnitName::Terran_Science_Facility;
	build[UnitName::Terran_Irradiate] = UnitName::Terran_Science_Facility;
	build[UnitName::Terran_Titan_Reactor] = UnitName::Terran_Science_Facility;
	build[UnitName::Terran_Lockdown] = UnitName::Terran_Covert_Ops;
	build[UnitName::Terran_Personnel_Cloaking] = UnitName::Terran_Covert_Ops;
	build[UnitName::Terran_Ocular_Implants] = UnitName::Terran_Covert_Ops;
	build[UnitName::Terran_Moebius_Reactor] = UnitName::Terran_Covert_Ops;
	build[UnitName::Terran_Yamato_Gun] = UnitName::Terran_Physics_Lab;
	build[UnitName::Terran_Colossus_Reactor] = UnitName::Terran_Physics_Lab;
	build[UnitName::Terran_Infantry_Weapons_1] = UnitName::Terran_Engineering_Bay;
	build[UnitName::Terran_Infantry_Weapons_2] = UnitName::Terran_Engineering_Bay;
	build[UnitName::Terran_Infantry_Weapons_3] = UnitName::Terran_Engineering_Bay;
	build[UnitName::Terran_Infantry_Armor_1] = UnitName::Terran_Engineering_Bay;
	build[UnitName::Terran_Infantry_Armor_2] = UnitName::Terran_Engineering_Bay;
	build[UnitName::Terran_Infantry_Armor_3] = UnitName::Terran_Engineering_Bay;
	build[UnitName::Terran_Vehicle_Weapons_1] = UnitName::Terran_Armory;
	build[UnitName::Terran_Vehicle_Weapons_2] = UnitName::Terran_Armory;
	build[UnitName::Terran_Vehicle_Weapons_3] = UnitName::Terran_Armory;
	build[UnitName::Terran_Vehicle_Plating_1] = UnitName::Terran_Armory;
	build[UnitName::Terran_Vehicle_Plating_2] = UnitName::Terran_Armory;
	build[UnitName::Terran_Vehicle_Plating_3] = UnitName::Terran_Armory;
	build[UnitName::Terran_Ship_Weapons_1] = UnitName::Terran_Armory;
	build[UnitName::Terran_Ship_Weapons_2] = UnitName::Terran_Armory;
	build[UnitName::Terran_Ship_Weapons_3] = UnitName::Terran_Armory;
	build[UnitName::Terran_Ship_Plating_1] = UnitName::Terran_Armory;
	build[UnitName::Terran_Ship_Plating_2] = UnitName::Terran_Armory;
	build[UnitName::Terran_Ship_Plating_3] = UnitName::Terran_Armory;
}

bool UnitTree::is_addon(UnitName u) {
    return (u >= UnitName::Terran_Machine_Shop && u <= UnitName::Terran_Covert_Ops);
}

bool UnitTree::req_addon(UnitName u) {
    return ((u == UnitName::Terran_Siege_Tank)
            || (u >= UnitName::Terran_Dropship && u <= UnitName::Terran_Battlecruiser));
}

bool UnitTree::is_upgrade(UnitName u) {
    return (u >= UnitName::Terran_U238_Shells && u <= UnitName::Terran_Ship_Plating_3);
}

// DEBUG below

#include <iostream>
#include <iomanip>
#include "unit_stats.h"

int unit_tree_test() {
    UnitTree ut;
    UnitStats us;
    for (int i=0; i <= (int)UnitName::Terran_Ship_Plating_3; i++) {
        UnitName u = (UnitName) i;
        cout << setw(25) << us[u].get_name() << ' ' << us[ut.get_builder(u)].get_name();
        if (ut.is_addon(u)) cout << " a";
        if (ut.req_addon(u)) cout << " r";
        if (ut.is_upgrade(u)) cout << " u";
        cout << endl;
    }
    UnitStats ul;
    for (int i=0; i <= (int)UnitName::Terran_Ship_Plating_3; i++) {
        Unit &u = ul[(UnitName)i];
        cout << setw(25) << u.get_name() << setw(4) << u.get_min() << setw(4) << u.get_gas();
        cout << setw(5) << u.get_time() << setw(2) << u.get_sup() << setw(3) << u.get_sup_max() << endl;
    }
    return 0;
}
