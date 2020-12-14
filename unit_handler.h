#pragma once

#include <map>
#include <unordered_map>
#include <deque>
#include "unit.h"
#include "unit_tree.h"
#include "resource_handler.h"
using namespace std;

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
    deque <Unit> build_order;
    unordered_multimap <Unit, int> units; // units to current task
    multimap <Unit, int> queue; // unit, build time
    UnitTree unit_tree;
};
