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
    // check addon
    if (Unit::req_addon(u)) {
        Unit::UnitName addon = Unit::get_addon(builder);
        for (int i = 0; i < units[addon].size(); i++)
            if (units[builder][i] == 0)
                return true;
        return false;
    }
    // check parent of addon
    if (Unit::is_addon(u) && !enough_addon_parents(u))
        return false;
    for (const auto t : units[builder])
        if (t == 0)
            return true;
    return false;
}

bool UnitHandler::enough_addon_parents(Unit::UnitName u) {
    int addon_count = units[u].size();
    if (Unit::get_addon_sibling(u) != Unit::UNIT_NULL)
        addon_count += units[Unit::get_addon_sibling(u)].size();
    int parent_count = units[Unit::get_addon_parent(u)].size();
    return parent_count > addon_count;
}

void UnitHandler::build_unit(Unit::UnitName u) {
    // use unit builder
    Unit::UnitName builder = Unit::get_builder(u);
    // addon units build from front
    if (Unit::req_addon(u)) {
        for (auto &t : units[builder]) {
            if (t == 0) {
                t = Unit::get_time(u);
                return;
            }
        }
    }
    // non addon units build from back
    for (int i = units[builder].size() - 1; i >= 0; i--) {
        if (units[builder][i] == 0) {
            units[builder][i] = Unit::get_time(u);
            return;
        }
    }
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
        if (units[i].size() > 0)
            std::cout << i << ":" << units[i].size() << " ";
}
