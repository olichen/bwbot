#pragma once

#include <vector>
#include "unit.h"
#include "unit_name.h"
using namespace std;

class UnitHandler {
public:

private:
    vector <UnitName> build_order;
    vector <UnitName> units;
    UnitLibrary ul;
};
