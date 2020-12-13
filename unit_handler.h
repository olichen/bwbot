#pragma once

#include <map>
#include <deque>
#include <vector>
#include "unit_name.h"
#include "unit_tree.h"
#include "resource_handler.h"
using namespace std;

class UnitHandler {
public:
    UnitHandler();

    void next_frame();
    void print();

private:
    ResourceHandler resource_handler;
    deque <UnitName> build_order;
    vector <UnitName> units;
    multimap <UnitName, int> queue;
    UnitTree unit_tree;
};
