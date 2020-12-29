#include "bwbot.h"

int main() {
    BuildHandler bh;
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Supply_Depot);
    bh.add_unit(Unit::Terran_SCV);
    bh.run();
}
