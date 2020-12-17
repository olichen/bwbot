#include "unit_handler.h"

#include <iostream> // DEBUG
#include <iomanip> // DEBUG

UnitHandler::UnitHandler() {
    // DEBUG
    spawn_unit(Unit::Terran_SCV);
    spawn_unit(Unit::Terran_SCV);
    spawn_unit(Unit::Terran_SCV);
    spawn_unit(Unit::Terran_SCV);
    spawn_unit(Unit::Terran_Command_Center);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Supply_Depot);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Barracks);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Refinery);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::SEARCH);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Supply_Depot);
    build_order.push_back(Unit::Terran_Factory);
    build_order.push_back(Unit::OFF_GAS);
    build_order.push_back(Unit::OFF_GAS);
    build_order.push_back(Unit::OFF_GAS);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Marine);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Marine);
    build_order.push_back(Unit::Terran_Command_Center);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Vulture);
    build_order.push_back(Unit::ON_GAS);
    build_order.push_back(Unit::ON_GAS);
    build_order.push_back(Unit::ON_GAS);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Supply_Depot);
    build_order.push_back(Unit::Terran_Machine_Shop);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Factory);
}

void UnitHandler::next_frame() {
    resource_handler.next_frame();
    // update unit queue
    for (auto it = queue.begin(); it != queue.end();) {
        it->second--;
        if (it->second == 0) {
            spawn_unit(it->first);
            queue.erase(it++);
        } else {
            it++;
        }
    }
    // try to build
    try_to_build();
    // update busy units
    for (auto it = units.begin(); it != units.end(); it++) {
        if (it->second == 1 && Unit::is_worker(it->first))
            resource_handler.add_min_worker(64); // 64 is time to return to mins
        if (it->second > 0)
            it->second--;
    }
}

void UnitHandler::try_to_build() {
    if (build_order.empty()) return;
    // get next unit from build order
    Unit::UnitName next_unit = build_order.front();
    if (Unit::is_action(next_unit)) {
        if (next_unit == Unit::SEARCH) {
            resource_handler.rem_min_worker();
        }
        else if (next_unit == Unit::OFF_GAS) {
            resource_handler.rem_gas_worker();
            resource_handler.add_min_worker();
        }
        else if (next_unit == Unit::ON_GAS) {
            resource_handler.rem_min_worker();
            resource_handler.add_gas_worker();
        }
        build_order.pop_front();
    }
    else if (can_build(next_unit)) {
        build_order.pop_front();
        build_unit(next_unit);
    }
}

bool UnitHandler::can_build(Unit::UnitName un) {
    if (!resource_handler.can_build(un))
        return false;
    Unit::UnitName builder = Unit::get_builder(un);
    for (auto [start, end] = units.equal_range(builder); start != end; start++)
        if (start->second == 0)
            return true;
    return false;
}

void UnitHandler::build_unit(Unit::UnitName un) {
    resource_handler.build_unit(un);
    Unit::UnitName builder = Unit::get_builder(un);
    for (auto [start, end] = units.equal_range(builder); start != end; start++) {
        if (start->second == 0) {
            start->second = Unit::get_time(un);
            break;
        }
    }
    if (Unit::is_worker(builder))
        resource_handler.rem_min_worker();
    queue.emplace(un, Unit::get_time(un));
}

void UnitHandler::spawn_unit(Unit::UnitName un) {
    resource_handler.spawn_unit(un);
    if (Unit::is_worker(un)) resource_handler.add_min_worker(32);
    if (Unit::is_gas(un)) {
        for (int i = 0; i < 3; i++) {
            resource_handler.add_gas_worker();
            resource_handler.rem_min_worker();
        }
    }
    units.emplace(un, 0);
}

// DEBUG

int main() {
    UnitHandler uh;
    for (int f = 0; f < 10000; f++) {
        int s = f * 42 / 1000;
        std::cout << std::setw(4) << f << std::setw(4) << s << " : ";
        uh.print();
        std::cout << std::endl;
        uh.next_frame();
    }
    return 0;
}

void UnitHandler::print() {
    resource_handler.print();
    for (const auto [u, t] : units)
        std::cout << ' ' << u;
}
