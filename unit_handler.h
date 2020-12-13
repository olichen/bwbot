#pragma once

#include <map>
#include <unordered_map>
#include <deque>
#include "unit_name.h"
#include "unit_tree.h"
#include "resource_handler.h"
using namespace std;

class UnitHandler {
public:
    UnitHandler();

    void next_frame();
    void print();

    bool can_build(UnitName);
    void build_unit(UnitName);
    void spawn_unit(UnitName);

private:
    ResourceHandler resource_handler;
    deque <UnitName> build_order;
    unordered_multimap <UnitName, int> units; // units to current task
    multimap <UnitName, int> queue; // unit, build time
    UnitTree unit_tree;
};
