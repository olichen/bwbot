#pragma once

#include <map>
#include "unit_name.h"
using namespace std;

class UnitTree {
public:
    UnitTree();

    UnitName get_builder(UnitName u) { return build[u]; }
    bool is_addon(UnitName u);
    bool req_addon(UnitName u);
    bool is_upgrade(UnitName u);

private:
    map <UnitName, UnitName> build;
    multimap <UnitName, UnitName> prereqs;
};
