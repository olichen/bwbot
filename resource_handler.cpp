#include "resource_handler.h"

void ResourceHandler::remove_worker() {
    int max = 0;
    for (int i=1; i < min_workers.size(); i++) {
        if (min_workers[i] > min_workers[max])
            max = i;
    }
    min_workers[max] = min_workers.back();
    min_workers.pop_back();
}

void ResourceHandler::next_frame() {
    for (int &w : min_workers) {
        w--;
        if (w == 0) {
            resources.add_min();
            w = get_mineral_frames();
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
    add_worker();
    add_worker();
    add_worker();
    add_worker();
}

bool ResourceHandler::can_build(UnitName un) {
    const Unit &u = unit_stats[un];
    return (resources.get_min() >= u.get_min()
            && resources.get_gas() >= u.get_gas()
            && (resources.get_sup_max() - resources.get_sup()) >= u.get_sup());
}

void ResourceHandler::build_unit(UnitName un) {
    const Unit &u = unit_stats[un];
    resources.use_min(u.get_min());
    resources.use_gas(u.get_gas());
    resources.use_sup(u.get_sup());
}

//DEBUG below
#include <iostream>
#include <iomanip>

int main() {
    int worker_queue = -1;
    ResourceHandler rh;
    for (int f = 0; f < 1500; f++) {
        int s = f * 42 / 1000;
        cout << setw(4) << f << setw(4) << s << " : ";
        rh.print();
        cout << endl;
        rh.next_frame();
        if (worker_queue-- == 0)
            rh.add_worker();
        if (rh.can_build(UnitName::Terran_SCV) && worker_queue <= 0) {
            rh.build_unit(UnitName::Terran_SCV);
            worker_queue = 300;
        }
        if (f == 750) {
            rh.remove_worker();
        }
    }
}

void ResourceHandler::print() {
    cout << "M" << setw(5) << resources.get_min() << " | G" << setw(5) << resources.get_gas();
    cout << " | S" << setw(3) << resources.get_sup() << "/" << setw(3) << resources.get_sup_max();
}
std::ostream& operator<<(std::ostream& os, ResourceHandler& rh) {
    rh.print();
    return os;
}
