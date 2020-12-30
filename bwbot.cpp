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
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Barracks);
    bh.run();

    bh.set_race(BuildHandler::Race::Protoss);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Pylon);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Gateway);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Assimilator);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Cybernetics_Core);
    bh.run();
}
