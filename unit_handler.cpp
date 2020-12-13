#include "unit_handler.h"

UnitHandler::UnitHandler() {
    // DEBUG
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
    resource_handler.next_frame();
}

// DEBUG

#include <iostream>
#include <iomanip>

int main() {
    UnitHandler uh;
    for (int f = 0; f < 1000; f++) {
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
}
