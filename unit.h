#pragma once

#include <string>
#include "unit_name.h"

class Unit {
public:
    Unit(UnitName u, std::string n, int m, int g, int s, int sm, int t);

private:
    UnitName unit;
	std::string name;
	int min;
	int gas;
	int sup;
	int sup_max;
	int time;
	UnitName prereq[2];
	UnitName build_from;
	bool req_addon;
	bool morph;
};
