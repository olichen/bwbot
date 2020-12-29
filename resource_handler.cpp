#include "resource_handler.h"

void ResourceHandler::reset() {
    resources.reset();
    min_workers.clear();
    gas_workers.clear();
}

void ResourceHandler::next_frame() {
    for (int &w : min_workers) {
        w--;
        if (w == 0) {
            resources.min += 8;
            w = get_min_frames();
        }
    }
    for (int &g : gas_workers) {
        g--;
        if (g == 0) {
            resources.gas += 8;
            g = get_gas_frames();
        }
    }
}

int ResourceHandler::get_min_frames() {
    int worker_count = min_workers.size();
    if (worker_count <= min_count) return 176;
    if (worker_count <= min_count * 3) {
        return 144 + 32 * worker_count / min_count;
    }
    return (240 * worker_count) / (min_count * 3);
}

int ResourceHandler::get_gas_frames() {
    int max = -1;
    for (const int& g : gas_workers) {
        if (g > max) max = g;
    }
    if (max > -1) return max + 37;
    return 111;
}

bool ResourceHandler::can_build(Unit::UnitName un) {
    return (resources.min >= Unit::get_min(un)
            && resources.gas >= Unit::get_gas(un)
            && (resources.sup_max - resources.sup) >= Unit::get_sup(un));
}

void ResourceHandler::build_unit(Unit::UnitName un) {
    resources.min -= Unit::get_min(un);
    resources.gas -= Unit::get_gas(un);
    resources.sup += Unit::get_sup(un);
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
    std::cout << "M" << std::setw(5) << resources.min << " | G" << std::setw(5) << resources.gas;
    std::cout << " | S" << std::setw(3) << resources.sup << "/" << std::setw(3) << resources.sup_max;
    std::cout << " | W" << std::setw(3) << min_workers.size() << " | G" << std::setw(3) << gas_workers.size();
    std::cout << " |";
}
