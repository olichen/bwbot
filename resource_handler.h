#pragma once

#include <vector>
#include "unit.h"

// invariant: always positive?
class Resources {
public:
    int get_min() const { return min; }
    void use_min(int m) { min -= m; }
    void add_min(int m = 8) { min += m; }

    int get_gas() const { return gas; }
    void use_gas(int g) { gas -= g; }
    void add_gas(int g = 8) { gas += g; }

    int get_sup() const { return sup; }
    void use_sup(int s) { sup += s; }

    int get_sup_max() const { return sup_max; }
    void add_sup_max(int s) { sup_max += s; }
private:
    int min = 50, gas = 0;
    int sup = 4, sup_max = 0;
};

class ResourceHandler {
public:
    ResourceHandler();
    void next_frame();

    void add_min_worker(int delay = 0) { min_workers.push_back(get_mineral_frames() + delay); }
    void rem_min_worker();

    void add_gas_worker();
    void rem_gas_worker();

    void print(); //DEBUG

    bool can_build(Unit u);
    void build_unit(Unit u);
    void spawn_unit(Unit u);
    int get_build_time(Unit u);
private:
    void pop_highest(std::vector<int>& v);

    UnitCosts unit_costs;
    Resources resources;
    int min_count = 9;
    std::vector <int> min_workers;
    std::vector <int> gas_workers;
    int get_mineral_frames();
};
