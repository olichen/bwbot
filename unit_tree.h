#pragma once

#include <map>
#include "unit.h"
using namespace std;

class UnitTree {
public:
    UnitTree();

    Unit get_builder(Unit u) { return build[u]; }
    bool is_addon(Unit u);
    bool req_addon(Unit u);
    bool is_upgrade(Unit u);

private:
    map <Unit, Unit> build;
    multimap <Unit, Unit> prereq;
};
