#pragma once

#include <vector>
#include "unit.h"
#include "unit_name.h"

class UnitLibrary {
public:
    UnitLibrary();
    Unit &operator[](UnitName);

    // operator overload on unitname

private:
    std::vector <Unit> units;
};
