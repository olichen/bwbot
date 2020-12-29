#include "build_handler.h"

void BuildHandler::reset() {
    resource_handler.reset();
    build_step = 0;
    frame = 0;
    spawn_unit(Unit::Terran_SCV);
    spawn_unit(Unit::Terran_SCV);
    spawn_unit(Unit::Terran_SCV);
    spawn_unit(Unit::Terran_SCV);
    spawn_unit(Unit::Terran_Command_Center);
}

void BuildHandler::next_frame() {
    frame++;
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

void BuildHandler::try_to_build() {
    if (build_step == build_order.size()) return;
    // get next unit from build order
    Unit::UnitName next_unit = build_order[build_step];
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
        build_step++;
    }
    else if (can_build(next_unit)) {
        build_step++;
        build_unit(next_unit);
    }
}

bool BuildHandler::can_build(Unit::UnitName un) {
    if (!resource_handler.can_build(un))
        return false;
    Unit::UnitName builder = Unit::get_builder(un);
    for (auto [start, end] = units.equal_range(builder); start != end; start++)
        if (start->second == 0)
            return true;
    return false;
}

void BuildHandler::build_unit(Unit::UnitName un) {
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

void BuildHandler::spawn_unit(Unit::UnitName un) {
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
#include <iostream> // DEBUG
#include <iomanip> // DEBUG

/*
int main() {
    BuildHandler uh;
    for (int f = 0; f < 10000; f++) {
        int s = f * 42 / 1000;
        std::cout << std::setw(4) << f << std::setw(4) << s << " : ";
        uh.print();
        std::cout << std::endl;
        uh.next_frame();
    }
    return 0;
}
*/
void BuildHandler::run() {
    while (build_step < build_order.size()) {
        print();
        next_frame();
    }
    print();
}

void BuildHandler::print() {
    int s = frame * 42 / 1000;
    std::cout << std::setw(4) << frame << std::setw(4) << s << " : ";
    resource_handler.print();
    for (const auto [u, t] : units)
        std::cout << ' ' << u;
    std::cout << std::endl;
}
