#include "resource_handler.h"

void ResourceHandler::reset() {
    resources.reset();
    min_workers.clear();
    gas_workers.clear();
    busy_workers.clear();
}

void ResourceHandler::next_frame() {
    for (int &w : min_workers) {
        if (--w == 0) {
            resources.min += 8;
            w = get_min_frames();
        }
    }
    for (int &g : gas_workers) {
        if (--g == 0) {
            resources.gas += 8;
            g = get_gas_frames();
        }
    }
    for (auto it = busy_workers.begin(); it != busy_workers.end();) {
        if (--(*it) == 0) {
            add_min_worker();
            busy_workers.erase(it++);
        } else {
            it++;
        }
    }
}

void ResourceHandler::use_worker(int delay) {
    pop_highest(min_workers);
    busy_workers.push_back(delay);
}

void ResourceHandler::expand(int min, int gas) {
    int transfer_count = (min_workers.size() * min) / (min_count + min);
    int TRANSFER_TIME = 240; // roughly 10 seconds
    for (int i = 0; i < transfer_count; i++)
        min_workers[i] += TRANSFER_TIME;
    min_count += min;
    gas_count += gas;
}

int ResourceHandler::get_min_frames() {
    int worker_count = min_workers.size();
    if (worker_count <= min_count) return mineral_rate;
    if (worker_count <= min_count * 3) {
        return mineral_rate + (240 - mineral_rate) * (worker_count - min_count) / min_count;
    }
    return 240 * (worker_count / (min_count * 3));
}

int ResourceHandler::get_gas_frames() {
    int max = -1;
    for (const int& g : gas_workers) {
        if (g > max) max = g;
    }
    if (max + 37 > 111) return max + 37;
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
    std::cout << "M" << std::setw(3) << resources.min << "|G" << std::setw(3) << resources.gas;
    std::cout << "|S" << std::setw(2) << resources.sup << "/" << std::setw(2) << resources.sup_max;
    std::cout << "|W" << std::setw(2) << min_workers.size() << "|G" << std::setw(2) << gas_workers.size();
    std::cout << "|";
    for (auto w : min_workers)
        std::cout << " " << w;
    std::cout << "|";
}
