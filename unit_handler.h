#pragma once

#include <map>
#include <unordered_map>
#include <deque>
#include "unit.h"
#include "resource_handler.h"

class UnitHandler {
public:
    UnitHandler();

    void next_frame();
    void print();

    bool can_build(Unit::UnitName);
    void build_unit(Unit::UnitName);
    void spawn_unit(Unit::UnitName);
    void try_to_build();

private:
    ResourceHandler resource_handler;
    std::deque <Unit::UnitName> build_order;
    std::multimap <Unit::UnitName, int> units; // units to current task
    std::multimap <Unit::UnitName, int> queue; // unit, build time
};
