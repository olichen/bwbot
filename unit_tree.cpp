#include "unit_tree.h"

UnitTree::UnitTree() {
    build[UnitName::Terran_SCV] = UnitName::Terran_Command_Center;
}

#include <iostream>

int main() {
    UnitTree ut;
    cout << (int) ut[UnitName::Terran_SCV] << endl;
    return 0;
}
