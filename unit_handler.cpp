#include "unit_handler.h"

#include <iostream> // DEBUG
#include <iomanip> // DEBUG

UnitHandler::UnitHandler() {
    // DEBUG
    spawn_unit(UnitName::Terran_SCV);
    spawn_unit(UnitName::Terran_SCV);
    spawn_unit(UnitName::Terran_SCV);
    spawn_unit(UnitName::Terran_SCV);
    spawn_unit(UnitName::Terran_Command_Center);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_Supply_Depot);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_Barracks);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_Refinery);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
}

void UnitHandler::next_frame() {
    resource_handler.next_frame();
    UnitName next_unit = build_order.front();
    for (auto it = queue.begin(); it != queue.end();) {
        it->second--;
        if (it->second == 0) {
            spawn_unit(it->first);
            queue.erase(it++);
        } else {
            it++;
        }
    }
    if (can_build(next_unit)) {
        build_order.pop_front();
        build_unit(next_unit);
    }
    for (auto it = units.begin(); it != units.end(); it++) {
        if (it->second == 1 && it->first == UnitName::Terran_SCV)
            resource_handler.add_worker(64);
        if (it->second > 0)
            it->second--;
    }
}

bool UnitHandler::can_build(UnitName un) {
    if (!resource_handler.can_build(un))
        return false;
    UnitName builder = unit_tree.get_builder(un);
    for (auto [start, end] = units.equal_range(builder); start != end; start++)
        if (start->second == 0)
            return true;
    return false;
}

void UnitHandler::build_unit(UnitName un) {
    resource_handler.build_unit(un);
    UnitName builder = unit_tree.get_builder(un);
    for (auto [start, end] = units.equal_range(builder); start != end; start++)
        if (start->second == 0)
            start->second = resource_handler.get_build_time(un);
    if (builder == UnitName::Terran_SCV)
        resource_handler.remove_worker();
    queue.emplace(un, resource_handler.get_build_time(un));
}

void UnitHandler::spawn_unit(UnitName un) {
    resource_handler.spawn_unit(un);
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
