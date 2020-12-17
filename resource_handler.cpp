#include "resource_handler.h"

void ResourceHandler::rem_min_worker() {
    pop_highest(min_workers);
}

void ResourceHandler::add_gas_worker() {
    int max = -1;
    for (const int& g : gas_workers) {
        if (g > max) max = g;
    }
    if (max > -1) gas_workers.push_back(max + 37);
    else gas_workers.push_back(111);
}

void ResourceHandler::rem_gas_worker() {
    pop_highest(gas_workers);
}

void ResourceHandler::next_frame() {
    for (int &w : min_workers) {
        w--;
        if (w == 0) {
            resources.add_min();
            w = get_mineral_frames();
        }
    }
    for (int &g : gas_workers) {
        g--;
        if (g == 0) {
            resources.add_gas();
            g = 111;
        }
    }
}

int ResourceHandler::get_mineral_frames() {
    int worker_count = min_workers.size();
    if (worker_count <= min_count) return 176;
    if (worker_count <= min_count * 3) {
        return 144 + 32 * worker_count / min_count;
    }
    return (240 * worker_count) / (min_count * 3);
}

ResourceHandler::ResourceHandler() {
}

bool ResourceHandler::can_build(Unit::UnitName un) {
    return (resources.get_min() >= Unit::get_min(un)
            && resources.get_gas() >= Unit::get_gas(un)
            && (resources.get_sup_max() - resources.get_sup()) >= Unit::get_sup(un));
}

void ResourceHandler::build_unit(Unit::UnitName un) {
    resources.use_min(Unit::get_min(un));
    resources.use_gas(Unit::get_gas(un));
    resources.use_sup(Unit::get_sup(un));
}

void ResourceHandler::spawn_unit(Unit::UnitName un) {
    resources.add_sup_max(Unit::get_sup_max(un));
}

void ResourceHandler::pop_highest(std::vector<int>& v) {
    int i_max = 0;
    for (int i = 1; i < v.size(); i++) {
        if (v[i] > v[i_max])
            i_max = i;
    }
    v[i_max] = v.back();
    v.pop_back();
}

// DEBUG below

#include <iostream> // DEBUG
#include <iomanip> // DEBUG

void ResourceHandler::print() {
    std::cout << "M" << std::setw(5) << resources.get_min() << " | G" << std::setw(5) << resources.get_gas();
    std::cout << " | S" << std::setw(3) << resources.get_sup() << "/" << std::setw(3) << resources.get_sup_max();
    std::cout << " | W" << std::setw(3) << min_workers.size() << " | G" << std::setw(3) << gas_workers.size();
    std::cout << " |";
}
