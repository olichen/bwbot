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
    bh.add_unit(Unit::SEARCH);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Command_Center);
    bh.add_unit(Unit::EXPAND);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Barracks);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Supply_Depot);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Refinery);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Marine);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Marine);
    bh.add_unit(Unit::Terran_SCV);
    bh.add_unit(Unit::Terran_Factory);
    bh.run();

    bh.set_race(BuildHandler::Race::Protoss);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Pylon);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Nexus);
    bh.add_unit(Unit::EXPAND);
    bh.add_unit(Unit::Protoss_Forge);
    bh.add_unit(Unit::SEARCH);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Photon_Cannon);
    bh.add_unit(Unit::Protoss_Gateway);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Assimilator);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Cybernetics_Core);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Zealot);
    bh.add_unit(Unit::Protoss_Pylon);
    bh.add_unit(Unit::Protoss_Probe);
    bh.add_unit(Unit::Protoss_Ground_Weapons_1);
    bh.add_unit(Unit::Protoss_Citadel_Of_Adun);
    bh.run();
}
