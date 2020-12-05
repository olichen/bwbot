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
}

#include <iostream>
#include <iomanip>
#include "unit_stats.h"

int main() {
    UnitTree ut;
    UnitStats us;
    for (int i=0; i <= (int)UnitName::Terran_Starport; i++) {
        UnitName u = (UnitName) i;
        cout << setw(23) <<us[u].get_name() << ' ' << us[ut[u]].get_name() << endl;
    }
    return 0;
}
