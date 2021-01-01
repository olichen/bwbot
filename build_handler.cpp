#include "build_handler.h"

void BuildHandler::reset() {
    queue.clear();
    resource_handler.reset();
    unit_handler.reset();

    build_step = 0;
    frame = 0;
    if (race == Race::Terran) {
        spawn_unit(Unit::Terran_Command_Center);
        spawn_unit(Unit::Terran_SCV);
        spawn_unit(Unit::Terran_SCV);
        spawn_unit(Unit::Terran_SCV);
        spawn_unit(Unit::Terran_SCV);
    }
    if (race == Race::Protoss) {
        spawn_unit(Unit::Protoss_Nexus);
        spawn_unit(Unit::Protoss_Probe);
        spawn_unit(Unit::Protoss_Probe);
        spawn_unit(Unit::Protoss_Probe);
        spawn_unit(Unit::Protoss_Probe);
    }
    if (race == Race::Zerg) {
        spawn_unit(Unit::Zerg_Hatchery);
        spawn_unit(Unit::Zerg_Overlord);
        spawn_unit(Unit::Zerg_Drone);
        spawn_unit(Unit::Zerg_Drone);
        spawn_unit(Unit::Zerg_Drone);
        spawn_unit(Unit::Zerg_Drone);
    }
}

void BuildHandler::next_frame() {
    frame++;
    resource_handler.next_frame();
    unit_handler.next_frame();
    update_queue();
    while (build_next_unit())
        ;
}

void BuildHandler::update_queue() {
    for (auto it = queue.begin(); it != queue.end();) {
        it->second--;
        if (it->second == 0) {
            spawn_unit(it->first);
            queue.erase(it++);
        } else {
            it++;
        }
    }
}

bool BuildHandler::build_next_unit() {
    if (build_step == build_order.size()) return false;

    Unit::UnitName next_unit = build_order[build_step];
    if (Unit::is_action(next_unit)) {
        Unit::UnitName next_unit = build_order[build_step];
        if (next_unit == Unit::SEARCH)
            resource_handler.use_worker(9999);
        else if (next_unit == Unit::OFF_GAS)
            resource_handler.gas_to_min();
        else if (next_unit == Unit::ON_GAS)
            resource_handler.min_to_gas();
        build_step++;
        return true;
    }
    else if (can_build(next_unit)) {
        build_unit(next_unit);
        build_step++;
        return true;
    }
    return false;
}

bool BuildHandler::can_build(Unit::UnitName u) {
    return resource_handler.can_build(u) && unit_handler.can_build(u);
}

void BuildHandler::build_unit(Unit::UnitName u) {
    resource_handler.build_unit(u);
    unit_handler.build_unit(u);
    queue.push_back({u, Unit::get_time(u)});

    Unit::UnitName builder = Unit::get_builder(u);
    // no build time for probe; pull and return a probe
    if (builder == Unit::Protoss_Probe)
        resource_handler.use_worker(64);
    // scv sits out
    if (builder == Unit::Terran_SCV)
        resource_handler.use_worker(Unit::get_time(u) + 64);
}

void BuildHandler::spawn_unit(Unit::UnitName u) {
    resource_handler.spawn_unit(u);
    unit_handler.spawn_unit(u);
    if (Unit::is_worker(u))
        resource_handler.add_min_worker(32);
    if (Unit::is_gas(u)) {
        for (int i = 0; i < 3; i++) {
            resource_handler.min_to_gas();
        }
    }
}

// DEBUG
#include <iostream> // DEBUG
#include <iomanip> // DEBUG

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
    unit_handler.print();
    std::cout << std::endl;
}
