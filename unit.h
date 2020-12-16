#pragma once

#include <string>
#include <vector>
#include <map>

struct UnitCost {
    UnitCost(int i, std::string n, int m, int g, int t, int s = 0, int sm = 0)
        : id{i}, name{n}, min{m}, gas{g}, time{t}, sup{s}, sup_max{sm}
    {}

    int id;
    std::string name;
	int min, gas, time, sup, sup_max;
};

class Unit {
public:
    enum UnitName : unsigned char {
        Terran_SCV, Terran_Marine, Terran_Firebat, Terran_Ghost, Terran_Medic,
        Terran_Vulture, Terran_Goliath, Terran_Siege_Tank, Terran_Wraith, Terran_Dropship,
        Terran_Valkyrie, Terran_Science_Vessel, Terran_Battlecruiser, Terran_Command_Center, Terran_Supply_Depot,
        Terran_Refinery, Terran_Barracks, Terran_Engineering_Bay, Terran_Missile_Turret, Terran_Academy,
        Terran_Bunker, Terran_Factory, Terran_Armory, Terran_Science_Facility, Terran_Starport,
        Terran_Machine_Shop, Terran_Control_Tower, Terran_Comsat_Station, Terran_Nuclear_Silo, Terran_Physics_Lab,
        Terran_Covert_Ops, Terran_Nuclear_Missile, Terran_U238_Shells, Terran_Stim_Pack, Terran_Restoration,
        Terran_Optical_Flare, Terran_Caduceus_Reactor, Terran_Ion_Thrusters, Terran_Spider_Mines, Terran_Siege_Tech,
        Terran_Charon_Boosters, Terran_Cloaking_Field, Terran_Apollo_Reactor, Terran_EMP_Shockwave, Terran_Irradiate,
        Terran_Titan_Reactor, Terran_Lockdown, Terran_Personnel_Cloaking, Terran_Ocular_Implants, Terran_Moebius_Reactor,
        Terran_Yamato_Gun, Terran_Colossus_Reactor, Terran_Infantry_Weapons_1, Terran_Infantry_Weapons_2, Terran_Infantry_Weapons_3,
        Terran_Infantry_Armor_1, Terran_Infantry_Armor_2, Terran_Infantry_Armor_3, Terran_Vehicle_Weapons_1, Terran_Vehicle_Weapons_2,
        Terran_Vehicle_Weapons_3, Terran_Vehicle_Plating_1, Terran_Vehicle_Plating_2, Terran_Vehicle_Plating_3, Terran_Ship_Weapons_1,
        Terran_Ship_Weapons_2, Terran_Ship_Weapons_3, Terran_Ship_Plating_1, Terran_Ship_Plating_2, Terran_Ship_Plating_3,
        Protoss_Probe, Protoss_Zealot, Protoss_Dragoon, Protoss_High_Templar, Protoss_Dark_Templar,
        Protoss_Archon, Protoss_Dark_Archon, Protoss_Reaver, Protoss_Scarab, Protoss_Scout,
        Protoss_Corsair, Protoss_Arbiter, Protoss_Carrier, Protoss_Interceptor, Protoss_Observer,
        Protoss_Shuttle, Protoss_Nexus, Protoss_Pylon, Protoss_Assimilator, Protoss_Gateway,
        Protoss_Forge, Protoss_Photon_Cannon, Protoss_Cybernetics_Core, Protoss_Shield_Battery, Protoss_Robotics_Facility,
        Protoss_Robotics_Support_Bay, Protoss_Observatory, Protoss_Stargate, Protoss_Fleet_Beacon, Protoss_Arbiter_Tribunal,
        Protoss_Citadel_Of_Adun, Protoss_Templar_Archives, Protoss_Singularity_Charge, Protoss_Leg_Enhancements, Protoss_Scarab_Damage,
        Protoss_Reaver_Capacity, Protoss_Gravitic_Drive, Protoss_Sensor_Array, Protoss_Gravitic_Boosters, Protoss_Psionic_Storm,
        Protoss_Hallucination, Protoss_Khaydarin_Amulet, Protoss_Maelstrom, Protoss_Mind_Control, Protoss_Argus_Talisman,
        Protoss_Apial_Sensors, Protoss_Gravitic_Thrusters, Protoss_Carrier_Capacity, Protoss_Disruption_Web, Protoss_Argus_Jewel,
        Protoss_Recall, Protoss_Stasis_Field, Protoss_Khaydarin_Core, Protoss_Ground_Weapons_1, Protoss_Ground_Weapons_2,
        Protoss_Ground_Weapons_3, Protoss_Ground_Armor_1, Protoss_Ground_Armor_2, Protoss_Ground_Armor_3, Protoss_Plasma_Shields_1,
        Protoss_Plasma_Shields_2, Protoss_Plasma_Shields_3, Protoss_Air_Weapons_1, Protoss_Air_Weapons_2, Protoss_Air_Weapons_3,
        Protoss_Air_Armor_1, Protoss_Air_Armor_2, Protoss_Air_Armor_3, Zerg_Drone, Zerg_Larva,
        Zerg_Zergling, Zerg_Hydralisk, Zerg_Lurker, Zerg_Ultralisk, Zerg_Defiler,
        Zerg_Overlord, Zerg_Mutalisk, Zerg_Scourge, Zerg_Queen, Zerg_Guardian,
        Zerg_Devourer, Zerg_Hatchery, Zerg_Extractor, Zerg_Spawning_Pool, Zerg_Evolution_Chamber,
        Zerg_Hydralisk_Den, Zerg_Creep_Colony, Zerg_Sunken_Colony, Zerg_Spore_Colony, Zerg_Lair,
        Zerg_Hive, Zerg_Spire, Zerg_Queens_Nest, Zerg_Nydus_Canal, Zerg_Ultralisk_Cavern,
        Zerg_Defiler_Mound, Zerg_Greater_Spire, Zerg_Burrowing, Zerg_Ventral_Sacs, Zerg_Antennae,
        Zerg_Pneumatized_Carapace, Zerg_Metabolic_Boost, Zerg_Adrenal_Glands, Zerg_Muscular_Augments, Zerg_Grooved_Spines,
        Zerg_Lurker_Aspect, Zerg_Spawn_Broodling, Zerg_Ensnare, Zerg_Gamete_Meiosis, Zerg_Anabolic_Synthesis,
        Zerg_Chitinous_Plating, Zerg_Plague, Zerg_Consume, Zerg_Metasynaptic_Node, Zerg_Melee_Attacks_1,
        Zerg_Melee_Attacks_2, Zerg_Melee_Attacks_3, Zerg_Missile_Attacks_1, Zerg_Missile_Attacks_2, Zerg_Missile_Attacks_3,
        Zerg_Carapace_1, Zerg_Carapace_2, Zerg_Carapace_3, Zerg_Flyer_Attacks_1, Zerg_Flyer_Attacks_2,
        Zerg_Flyer_Attacks_3, Zerg_Flyer_Carapace_1, Zerg_Flyer_Carapace_2, Zerg_Flyer_Carapace_3, UNIT_NULL
    };

    Unit(UnitName un) : u{un} { if (unit_costs.size() == 0) init(); }

    bool is_worker() const;
    bool is_gas() const;
    bool is_addon() const;
    bool req_addon() const;
    bool is_upgrade() const;

    UnitName get_unit_name() const { return u; }
    int get_id() const { return static_cast<int>(u); }
    std::string get_name() const { return unit_costs[u].name; }
    int get_min() const { return unit_costs[u].min; }
    int get_gas() const { return unit_costs[u].gas; }
    int get_sup() const { return unit_costs[u].sup; }
    int get_time() const { return unit_costs[u].time; }
    int get_sup_max() const { return unit_costs[u].sup_max; }
    Unit get_builder() const { return build.find(u)->second; }

    bool operator==(Unit uu) const { return u == uu.get_unit_name(); }
    bool operator<(Unit uu) const { return u < uu.get_unit_name(); }

private:
    void init();

    UnitName u;
    static std::vector <UnitCost> unit_costs;
    static std::map <Unit, Unit> build;
    static std::multimap <Unit, Unit> prereq;
};
