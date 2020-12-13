#include "unit_handler.h"

UnitHandler::UnitHandler() {
    // DEBUG
    units.push_back(UnitName::Terran_SCV);
    units.push_back(UnitName::Terran_SCV);
    units.push_back(UnitName::Terran_SCV);
    units.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_Supply_Depot);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_SCV);
    build_order.push_back(UnitName::Terran_Barracks);
}

void UnitHandler::next_frame() {
    UnitName next_unit = build_order.front();
    if (resource_handler.can_build(next_unit)) {
        build_order.pop_front();
        resource_handler.build_unit(next_unit);
        queue.emplace(next_unit, resource_handler.get_build_time(next_unit));
    }
    for (auto it = queue.begin(); it != queue.end();) {
        it->second--;
        if (it->second == 0) {
            units.push_back(it->first);
            queue.erase(it++);
        } else {
            it++;
        }
    }
    resource_handler.next_frame();
}

// DEBUG

#include <iostream>
#include <iomanip>

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
    for (const auto& u : units)
        cout << (int)u << ' ';
}
