#pragma once

#include <string>
#include <vector>
#include <map>
#include "unit_name.h"

namespace Unit {
    enum UnitName : unsigned char;
    namespace {
        struct UnitCost {
            UnitCost(UnitName u, std::string n, int m, int g, int t, int s = 0, int sm = 0);

            UnitName un;
            std::string name;
            int min, gas, time, sup, sup_max;
        };
        extern std::vector<UnitCost> unit_costs;
        extern std::map <UnitName, UnitName> unit_builder;
        extern std::multimap <UnitName, UnitName> unit_prereq;
    }

    bool is_worker(UnitName u);
    bool is_gas(UnitName u);
    bool is_addon(UnitName u);
    bool req_addon(UnitName u);
    bool is_upgrade(UnitName u);
    bool is_action(UnitName u) { return u > UNIT_NULL; }

    std::string get_name(UnitName u) { return unit_costs[u].name; }
    int get_min(UnitName u) { return unit_costs[u].min; }
    int get_gas(UnitName u) { return unit_costs[u].gas; }
    int get_sup(UnitName u) { return unit_costs[u].sup; }
    int get_time(UnitName u) { return unit_costs[u].time; }
    int get_sup_max(UnitName u) { return unit_costs[u].sup_max; }
    UnitName get_builder(UnitName u) { return unit_builder.find(u)->second; }

};
