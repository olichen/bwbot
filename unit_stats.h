#pragma once

#include <vector>
#include <string>
#include "unit.h"
using namespace std;

class UnitCost {
public:
    UnitCost(Unit u, std::string n, int m, int g, int t, int s = 0, int sm = 0)
        : unit{u}, name{n}, min{m}, gas{g}, time{t}, sup{s}, sup_max{sm}
    {}

    Unit get_unit() const { return unit; }
    string get_name() const { return name; }
    int get_min() const { return min; }
    int get_gas() const { return gas; }
    int get_sup() const { return sup; }
    int get_time() const { return time; }
    int get_sup_max() const { return sup_max; }

private:
    Unit unit;
	string name;
	int min;
	int gas;
	int time;
	int sup;
	int sup_max;
	Unit prereq[2];
	Unit build_from;
	bool req_addon;
	bool morph;
};

class UnitStats {
public:
    UnitStats();
    UnitCost& operator[](Unit u) { return uc[(int)u]; }

private:
    vector <UnitCost> uc;
};
