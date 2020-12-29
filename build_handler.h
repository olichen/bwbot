#pragma once

#include <map>
#include <unordered_map>
#include <deque>
#include "unit.h"
#include "resource_handler.h"

class BuildHandler {
public:
    BuildHandler() : build_step{0}, frame{0} { reset(); }
    void run();
    void reset();
    void clear() { reset(); build_order.clear(); units.clear(); queue.clear(); }

    void add_unit(Unit::UnitName un) { build_order.push_back(un); }
    void rem_unit() { build_order.pop_back(); reset(); }

    void next_frame();
    void print(); // DEBUG

private:
    bool can_build(Unit::UnitName);
    void build_unit(Unit::UnitName);
    void spawn_unit(Unit::UnitName);
    void try_to_build();

    ResourceHandler resource_handler;
    std::deque <Unit::UnitName> build_order;
    int build_step, frame;
    std::multimap <Unit::UnitName, int> units; // units to current task
    std::multimap <Unit::UnitName, int> queue; // unit, build time
};
