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

    bool can_build(Unit);
    void build_unit(Unit);
    void spawn_unit(Unit);

private:
    ResourceHandler resource_handler;
    std::deque <Unit> build_order;
    std::multimap <Unit, int> units; // units to current task
    std::multimap <Unit, int> queue; // unit, build time
    UnitTree unit_tree;
};
