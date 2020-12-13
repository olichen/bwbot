#pragma once

#include <vector>
#include "unit.h"
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
    vector <UnitName> build_order;
    vector <UnitName> units;
    UnitTree unit_tree;
};
