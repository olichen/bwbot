#pragma once

#include <string>
#include "unit_name.h"

class Unit {
public:
    Unit(UnitName u, std::string n, int m, int g, int t, int s = 0, int sm = 0);

    UnitName get_unit() const { return unit; }
    std::string get_name() const { return name; }
    int get_min() const { return min; }
    int get_gas() const { return gas; }
    int get_sup() const { return sup; }
    int get_time() const { return time; }
    int get_sup_max() const { return sup_max; }

private:
    UnitName unit;
	std::string name;
	int min;
	int gas;
	int sup;
	int time;
	int sup_max;
	UnitName prereq[2];
	UnitName build_from;
	bool req_addon;
	bool morph;
};
