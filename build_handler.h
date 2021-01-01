#pragma once

#include <map>
#include <list>
#include <vector>
#include "unit.h"
#include "resource_handler.h"
#include "unit_handler.h"

class BuildHandler {
public:
    enum class Race : uint8_t { Terran, Protoss, Zerg };

    BuildHandler(Race r = Race::Terran) : race{r} { reset(); }
    void set_race(Race r) { race = r; clear(); }
    void run();
    void reset();
    void clear() { reset(); build_order.clear(); }

    void add_unit(Unit::UnitName un) { build_order.push_back(un); }
    void rem_unit() { build_order.pop_back(); reset(); }

    void next_frame();
    void print(); // DEBUG

private:
    bool can_build(Unit::UnitName u);
    void build_unit(Unit::UnitName);
    void spawn_unit(Unit::UnitName);

    void update_queue();
    void try_to_build();

    ResourceHandler resource_handler;
    UnitHandler unit_handler;
    Race race;
    std::vector <Unit::UnitName> build_order;
    int build_step, frame;

    std::list <std::pair<Unit::UnitName, int>> queue; // unit, build time
};
