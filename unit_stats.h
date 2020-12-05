#pragma once

#include <vector>
#include "unit.h"
#include "unit_name.h"
using namespace std;

class UnitStats {
public:
    UnitStats();
    Unit& operator[](UnitName u) { return units[(int)u]; }

    // operator overload on unitname

private:
    vector <Unit> units;
};
