#include "unit_handler.h"

void UnitHandler::reset() {
    for (auto& u : units)
        u.clear();
}

bool UnitHandler::can_build(Unit::UnitName u) {
    // check prereqs
    for (const auto& u : Unit::get_prereq(u))
        if (units[u].size() == 0)
            return false;
    // check builder
    Unit::UnitName builder = Unit::get_builder(u);
    for (const auto t : units[builder])
        if (t == 0)
            return true;
    return false;
}

void UnitHandler::build_unit(Unit::UnitName u) {
    // use unit builder
    Unit::UnitName builder = Unit::get_builder(u);
    for (auto& t : units[builder])
        if (t == 0)
            t = Unit::get_time(u);
}

void UnitHandler::spawn_unit(Unit::UnitName u) {
    // add to units
    units[u].push_back(0);
}

void UnitHandler::next_frame() {
    for (auto& v : units)
        for (auto& t : v)
            if (t > 0)
                t--;
}

// DEBUG
#include <iostream>

void UnitHandler::print() {
    for (int i = 0; i < Unit::UNIT_NULL; i++)
        for (const auto u : units[i])
            std::cout << ' ' << i;
}
