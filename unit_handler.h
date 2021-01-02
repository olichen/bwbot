#pragma once

#include <vector>
#include "unit.h"

class UnitHandler {
public:
    UnitHandler() : units (Unit::UNIT_NULL) {}
    void reset();
    bool can_build(Unit::UnitName);
    void build_unit(Unit::UnitName);
    void spawn_unit(Unit::UnitName);

    void next_frame();
    void print(); // DEBUG

private:
    std::vector<std::vector<int>> units; // unitname to current task

    bool enough_addon_parents(Unit::UnitName);
};
