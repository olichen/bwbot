#include "unit_stats.h"

UnitStats::UnitStats() {
    uc.emplace_back(Unit::Terran_SCV, "Terran SCV", 50, 0, 300, 1);
    uc.emplace_back(Unit::Terran_Marine, "Terran Marine", 50, 0, 360, 1);
	uc.emplace_back(Unit::Terran_Firebat, "Terran Firebat", 50, 25, 360, 1);
	uc.emplace_back(Unit::Terran_Ghost, "Terran Ghost", 25, 75, 750, 1);
	uc.emplace_back(Unit::Terran_Medic, "Terran Medic", 50, 25, 450, 1);
	uc.emplace_back(Unit::Terran_Vulture, "Terran Vulture", 75, 0, 450, 2);
	uc.emplace_back(Unit::Terran_Goliath, "Terran Goliath", 100, 50, 600, 2);
	uc.emplace_back(Unit::Terran_Siege_Tank, "Terran Siege Tank", 150, 100, 750, 2);
	uc.emplace_back(Unit::Terran_Wraith, "Terran Wraith", 150, 100, 900, 2);
	uc.emplace_back(Unit::Terran_Dropship, "Terran Dropship", 100, 100, 750, 2);
	uc.emplace_back(Unit::Terran_Valkyrie, "Terran Valkyrie", 250, 125, 750, 3);
	uc.emplace_back(Unit::Terran_Science_Vessel, "Terran Science Vessel", 100, 225, 1200, 2);
	uc.emplace_back(Unit::Terran_Battlecruiser, "Terran Battlecruiser", 400, 300, 2000, 6);
	uc.emplace_back(Unit::Terran_Command_Center, "Terran Command Center", 400, 0, 1800, 0, 10);
	uc.emplace_back(Unit::Terran_Supply_Depot, "Terran Supply Depot", 100, 0, 600, 0, 8);
	uc.emplace_back(Unit::Terran_Refinery, "Terran Refinery", 100, 0, 600);
	uc.emplace_back(Unit::Terran_Barracks, "Terran Barracks", 150, 0, 1200);
	uc.emplace_back(Unit::Terran_Engineering_Bay, "Terran Engineering Bay", 125, 0, 900);
	uc.emplace_back(Unit::Terran_Missile_Turret, "Terran Missile Turret", 75, 0, 450);
	uc.emplace_back(Unit::Terran_Academy, "Terran Academy", 150, 0, 1200);
	uc.emplace_back(Unit::Terran_Bunker, "Terran Bunker", 100, 0, 450);
	uc.emplace_back(Unit::Terran_Factory, "Terran Factory", 200, 100, 1200);
	uc.emplace_back(Unit::Terran_Armory, "Terran Armory", 100, 50, 1200);
	uc.emplace_back(Unit::Terran_Science_Facility, "Terran Science Facility", 100, 150, 900);
	uc.emplace_back(Unit::Terran_Starport, "Terran Starport", 150, 100, 1050);
	uc.emplace_back(Unit::Terran_Machine_Shop, "Terran Machine Shop", 50, 50, 600);
	uc.emplace_back(Unit::Terran_Control_Tower, "Terran Control Tower", 50, 50, 600);
	uc.emplace_back(Unit::Terran_Comsat_Station, "Terran Comsat Station", 50, 50, 600);
	uc.emplace_back(Unit::Terran_Nuclear_Silo, "Terran Nuclear Silo", 100, 100, 1200);
	uc.emplace_back(Unit::Terran_Physics_Lab, "Terran Physics Lab", 50, 50, 600);
	uc.emplace_back(Unit::Terran_Covert_Ops, "Terran Covert Ops", 50, 50, 600);
	uc.emplace_back(Unit::Terran_Nuclear_Missile, "Terran Nuclear Missile", 200, 200, 1500, 8);
	uc.emplace_back(Unit::Terran_U238_Shells, "Terran U-238 Shells", 150, 150, 1500);
	uc.emplace_back(Unit::Terran_Stim_Pack, "Terran Stim Pack", 100, 100, 1200);
	uc.emplace_back(Unit::Terran_Restoration, "Terran Restoration", 100, 100, 1200);
	uc.emplace_back(Unit::Terran_Optical_Flare, "Terran Optical Flare", 100, 100, 1200);
	uc.emplace_back(Unit::Terran_Caduceus_Reactor, "Terran Caduceus Reactor", 150, 150, 2500);
	uc.emplace_back(Unit::Terran_Ion_Thrusters, "Terran Ion Thrusters", 100, 100, 1500);
	uc.emplace_back(Unit::Terran_Spider_Mines, "Terran Spider Mines", 100, 100, 1200);
	uc.emplace_back(Unit::Terran_Siege_Tech, "Terran Siege Tech", 150, 150, 1200);
	uc.emplace_back(Unit::Terran_Charon_Boosters, "Terran Charon Boosters", 100, 100, 2000);
	uc.emplace_back(Unit::Terran_Cloaking_Field, "Terran Cloaking Field", 150, 150, 1500);
	uc.emplace_back(Unit::Terran_Apollo_Reactor, "Terran Apollo Reactor", 200, 200, 2500);
	uc.emplace_back(Unit::Terran_EMP_Shockwave, "Terran EMP Shockwave", 200, 200, 1800);
	uc.emplace_back(Unit::Terran_Irradiate, "Terran Irradiate", 200, 200, 1200);
	uc.emplace_back(Unit::Terran_Titan_Reactor, "Terran Titan Reactor", 150, 150, 2500);
	uc.emplace_back(Unit::Terran_Lockdown, "Terran Lockdown", 200, 200, 1500);
	uc.emplace_back(Unit::Terran_Personnel_Cloaking, "Terran Personnel Cloaking", 100, 100, 1200);
	uc.emplace_back(Unit::Terran_Ocular_Implants, "Terran Ocular Implants", 100, 100, 2500);
	uc.emplace_back(Unit::Terran_Moebius_Reactor, "Terran Moebius Reactor", 150, 150, 2500);
	uc.emplace_back(Unit::Terran_Yamato_Gun, "Terran Yamato Gun", 100, 100, 1800);
	uc.emplace_back(Unit::Terran_Colossus_Reactor, "Terran Colossus Reactor", 150, 150, 2500);
	uc.emplace_back(Unit::Terran_Infantry_Weapons_1, "Terran Infantry Weapons 1", 100, 100, 4000);
	uc.emplace_back(Unit::Terran_Infantry_Weapons_2, "Terran Infantry Weapons 2", 175, 175, 4480);
	uc.emplace_back(Unit::Terran_Infantry_Weapons_3, "Terran Infantry Weapons 3", 250, 250, 4960);
	uc.emplace_back(Unit::Terran_Infantry_Armor_1, "Terran Infantry Armor 1", 100, 100, 4000);
	uc.emplace_back(Unit::Terran_Infantry_Armor_2, "Terran Infantry Armor 2", 175, 175, 4480);
	uc.emplace_back(Unit::Terran_Infantry_Armor_3, "Terran Infantry Armor 3", 250, 250, 4960);
	uc.emplace_back(Unit::Terran_Vehicle_Weapons_1, "Terran Vehicle Weapons 1", 100, 100, 4000);
	uc.emplace_back(Unit::Terran_Vehicle_Weapons_2, "Terran Vehicle Weapons 2", 175, 175, 4480);
	uc.emplace_back(Unit::Terran_Vehicle_Weapons_3, "Terran Vehicle Weapons 3", 250, 250, 4960);
	uc.emplace_back(Unit::Terran_Vehicle_Plating_1, "Terran Vehicle Plating 1", 100, 100, 4000);
	uc.emplace_back(Unit::Terran_Vehicle_Plating_2, "Terran Vehicle Plating 2", 175, 175, 4480);
	uc.emplace_back(Unit::Terran_Vehicle_Plating_3, "Terran Vehicle Plating 3", 250, 250, 4960);
	uc.emplace_back(Unit::Terran_Ship_Weapons_1, "Terran Ship Weapons 1", 100, 100, 4000);
	uc.emplace_back(Unit::Terran_Ship_Weapons_2, "Terran Ship Weapons 2", 175, 175, 4480);
	uc.emplace_back(Unit::Terran_Ship_Weapons_3, "Terran Ship Weapons 3", 250, 250, 4960);
	uc.emplace_back(Unit::Terran_Ship_Plating_1, "Terran Ship Plating 1", 100, 100, 4000);
	uc.emplace_back(Unit::Terran_Ship_Plating_2, "Terran Ship Plating 2", 175, 175, 4480);
	uc.emplace_back(Unit::Terran_Ship_Plating_3, "Terran Ship Plating 3", 250, 250, 4960);
}
