#pragma once

#include <map>
#include <unordered_map>
#include <deque>
#include "unit.h"
#include "resource_handler.h"

class BuildHandler {
public:
    BuildHandler() { }

    void add_unit(Unit::UnitName);

    void run();
    void clear();
    void next_frame();
    void print(); // DEBUG

private:
    bool can_build(Unit::UnitName);
    void build_unit(Unit::UnitName);
    void spawn_unit(Unit::UnitName);
    void try_to_build();

    ResourceHandler resource_handler;
    std::deque <Unit::UnitName> build_order;
    std::multimap <Unit::UnitName, int> units; // units to current task
    std::multimap <Unit::UnitName, int> queue; // unit, build time
};
