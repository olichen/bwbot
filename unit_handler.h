#pragma once

#include <vector>
#include "unit.h"
#include "unit_name.h"
using namespace std;

class UnitHandler {
public:
    UnitHandler();

private:
    vector <UnitName> build_order;
    vector <UnitName> units;
    UnitStats ul;
    UnitTree ut;

};
