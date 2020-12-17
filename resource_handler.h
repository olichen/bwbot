#pragma once

#include <vector>
#include "unit.h"

struct Resources {
    Resources() : min{50}, gas{0}, sup{4}, sup_max{} { }
    void reset() { min = 50; gas = 0; sup = 4; sup_max = 0; }

    int min, gas, sup, sup_max;
};

class ResourceHandler {
public:
    ResourceHandler() { }
    void next_frame();

    void add_min_worker(int delay = 0) { min_workers.push_back(get_mineral_frames() + delay); }
    void rem_min_worker() { pop_highest(min_workers); }

    void add_gas_worker();
    void rem_gas_worker() { pop_highest(gas_workers); }

    void print(); //DEBUG

    bool can_build(Unit::UnitName u);
    void build_unit(Unit::UnitName u);
    void spawn_unit(Unit::UnitName u);
private:
    void pop_highest(std::vector<int>& v);
    int get_mineral_frames();

    Resources resources;
    int min_count = 9;
    std::vector <int> min_workers;
    std::vector <int> gas_workers;
};
