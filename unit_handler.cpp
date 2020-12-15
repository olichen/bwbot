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
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Supply_Depot);
    build_order.push_back(Unit::Terran_Factory);
    build_order.push_back(Unit::Terran_SCV);
    build_order.push_back(Unit::Terran_Marine);
}

void UnitHandler::next_frame() {
    resource_handler.next_frame();
    // get next unit from build order
    Unit next_unit = build_order.front();
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
    if (!build_order.empty() && can_build(next_unit)) {
        build_order.pop_front();
        build_unit(next_unit);
    }
    // update busy units
    for (auto it = units.begin(); it != units.end(); it++) {
        if (it->second == 1 && it->first == Unit::Terran_SCV)
            resource_handler.add_min_worker(64); // 64 is time to return to mins
        if (it->second > 0)
            it->second--;
    }
}

bool UnitHandler::can_build(Unit un) {
    if (!resource_handler.can_build(un))
        return false;
    Unit builder = unit_tree.get_builder(un);
    for (auto [start, end] = units.equal_range(builder); start != end; start++)
        if (start->second == 0)
            return true;
    return false;
}

void UnitHandler::build_unit(Unit un) {
    resource_handler.build_unit(un);
    Unit builder = unit_tree.get_builder(un);
    for (auto [start, end] = units.equal_range(builder); start != end; start++) {
        if (start->second == 0) {
            start->second = resource_handler.get_build_time(un);
            break;
        }
    }
    if (builder == Unit::Terran_SCV)
        resource_handler.rem_min_worker();
    queue.emplace(un, resource_handler.get_build_time(un));
}

void UnitHandler::spawn_unit(Unit un) {
    resource_handler.spawn_unit(un);
    if (un == Unit::Terran_Refinery) {
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
    for (int f = 0; f < 4000; f++) {
        int s = f * 42 / 1000;
        cout << setw(4) << f << setw(4) << s << " : ";
        uh.print();
        cout << endl;
        uh.next_frame();
    }
    return 0;
}

void UnitHandler::print() {
    resource_handler.print();
    cout << ' ';
    for (const auto [u, t] : units)
        cout << (int)(u) << ' ';
}
