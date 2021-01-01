#pragma once

#include <vector>
#include <list>
#include "unit.h"

struct Resources {
    Resources() : min{50}, gas{0}, sup{4}, sup_max{0} { }
    void reset() { min = 50; gas = 0; sup = 4; sup_max = 0; }

    int min, gas, sup, sup_max;
};

class ResourceHandler {
public:
    ResourceHandler() : min_count{9} { }
    void reset();
    void next_frame();
    void print(); //DEBUG

    void add_min_worker(int delay = 0) { min_workers.push_back(get_min_frames() + delay); }
    void rem_min_worker() { pop_highest(min_workers); }
    void use_worker(int delay);
    void min_to_gas() { rem_min_worker(); gas_workers.push_back(get_gas_frames()); }
    void gas_to_min() { add_min_worker(); pop_highest(gas_workers); }

    bool can_build(Unit::UnitName u);
    void build_unit(Unit::UnitName u);
    void spawn_unit(Unit::UnitName un) { resources.sup_max += Unit::get_sup_max(un); }
private:
    void pop_highest(std::vector<int>& v);
    int get_min_frames();
    int get_gas_frames(); // TODO: fix

    Resources resources;
    int min_count;
    std::vector<int> min_workers;
    std::vector<int> gas_workers;
    std::list<int> busy_workers;
};
