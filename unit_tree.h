#pragma once

#include <map>
#include "unit_name.h"
using namespace std;

class UnitTree {
public:
    UnitTree();

    UnitName operator[](UnitName u) { return build[u]; }

private:
    map <UnitName, UnitName> build;
    multimap <UnitName, UnitName> prereqs;
};
