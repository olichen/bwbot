#include "unit_stats.h"

UnitStats::UnitStats() {
    units.emplace_back(UnitName::Terran_SCV, "Terran SCV", 50, 0, 300, 1);
    units.emplace_back(UnitName::Terran_Marine, "Terran Marine", 50, 0, 360, 1);
	units.emplace_back(UnitName::Terran_Firebat, "Terran Firebat", 50, 25, 360, 1);
	units.emplace_back(UnitName::Terran_Ghost, "Terran Ghost", 25, 75, 750, 1);
	units.emplace_back(UnitName::Terran_Medic, "Terran Medic", 50, 25, 450, 1);
	units.emplace_back(UnitName::Terran_Vulture, "Terran Vulture", 75, 0, 450, 2);
	units.emplace_back(UnitName::Terran_Goliath, "Terran Goliath", 100, 50, 600, 2);
	units.emplace_back(UnitName::Terran_Siege_Tank, "Terran Siege Tank", 150, 100, 750, 2);
	units.emplace_back(UnitName::Terran_Wraith, "Terran Wraith", 150, 100, 900, 2);
	units.emplace_back(UnitName::Terran_Dropship, "Terran Dropship", 100, 100, 750, 2);
	units.emplace_back(UnitName::Terran_Valkyrie, "Terran Valkyrie", 250, 125, 750, 3);
	units.emplace_back(UnitName::Terran_Science_Vessel, "Terran Science Vessel", 100, 225, 1200, 2);
	units.emplace_back(UnitName::Terran_Battlecruiser, "Terran Battlecruiser", 400, 300, 2000, 6);
	units.emplace_back(UnitName::Terran_Command_Center, "Terran Command Center", 400, 0, 1800, 0, 10);
	units.emplace_back(UnitName::Terran_Supply_Depot, "Terran Supply Depot", 100, 0, 600, 0, 8);
	units.emplace_back(UnitName::Terran_Refinery, "Terran Refinery", 100, 0, 600);
	units.emplace_back(UnitName::Terran_Barracks, "Terran Barracks", 150, 0, 1200);
	units.emplace_back(UnitName::Terran_Engineering_Bay, "Terran Engineering Bay", 125, 0, 900);
	units.emplace_back(UnitName::Terran_Missile_Turret, "Terran Missile Turret", 75, 0, 450);
	units.emplace_back(UnitName::Terran_Academy, "Terran Academy", 150, 0, 1200);
	units.emplace_back(UnitName::Terran_Bunker, "Terran Bunker", 100, 0, 450);
	units.emplace_back(UnitName::Terran_Factory, "Terran Factory", 200, 100, 1200);
	units.emplace_back(UnitName::Terran_Armory, "Terran Armory", 100, 50, 1200);
	units.emplace_back(UnitName::Terran_Science_Facility, "Terran Science Facility", 100, 150, 900);
	units.emplace_back(UnitName::Terran_Starport, "Terran Starport", 150, 100, 1050);
}

#include <iostream>
#include <iomanip>

ostream& operator<<(ostream& os, const Unit& u) {
    os << u.get_name();
    return os;
}

int main() {
    UnitStats ul;
    for (int i=0; i <= (int)UnitName::Terran_Starport; i++) {
        Unit &u = ul[(UnitName)i];
        cout << setw(25) << u << setw(4) << u.get_min() << setw(4) << u.get_gas();
        cout << setw(5) << u.get_time() << setw(2) << u.get_sup() << setw(3) << u.get_sup_max() << endl;
    }
}
//Unit::Unit(UnitName u, string n, int m, int g, int s, int sm, int t)
