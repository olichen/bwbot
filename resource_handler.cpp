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

bool ResourceHandler::can_build(Unit u) {
    const UnitCost &uc = unit_costs[u];
    return (resources.get_min() >= uc.get_min()
            && resources.get_gas() >= uc.get_gas()
            && (resources.get_sup_max() - resources.get_sup()) >= uc.get_sup());
}

void ResourceHandler::build_unit(Unit u) {
    const UnitCost &uc = unit_costs[u];
    resources.use_min(uc.get_min());
    resources.use_gas(uc.get_gas());
    resources.use_sup(uc.get_sup());
}

void ResourceHandler::spawn_unit(Unit u) {
    const UnitCost &uc = unit_costs[u];
    resources.add_sup_max(uc.get_sup_max());
    if (u == Unit::Terran_SCV) add_min_worker(32);
}

int ResourceHandler::get_build_time(Unit u) {
    return unit_costs[u].get_time();
}

void pop_highest(vector<int>& v) {
    int i_max = 0;
    for (int i = 1; i < v.size(); i++) {
        if (v[i] > v[i_max])
            i_max = i;
    }
    v[i_max] = v.back();
    v.pop_back();
}

// DEBUG below

void ResourceHandler::print() {
    cout << "M" << setw(5) << resources.get_min() << " | G" << setw(5) << resources.get_gas();
    cout << " | S" << setw(3) << resources.get_sup() << "/" << setw(3) << resources.get_sup_max();
    cout << " | W" << setw(3) << min_workers.size() << " | G" << setw(3) << gas_workers.size();
    cout << " |";
}
