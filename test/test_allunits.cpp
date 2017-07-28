#include "catch.hpp"
#include "allunits.h"

TEST_CASE("allunitss") {
	AllUnits allunits;

	SECTION("check spawning and prerequisites") {
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==false);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==false);
		allunits.spawn(UnitName::Terran_SCV);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==true);
		allunits.spawn(UnitName::Terran_Command_Center);
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==true);
		allunits.clear();
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==false);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==false);
	}

	SECTION("check that workers spawn mining") {
		CHECK(allunits.getMineralMinerCount() == 0);
		allunits.spawn(UnitName::Terran_SCV);
		CHECK(allunits.getMineralMinerCount() == 1);
		allunits.spawn(UnitName::Terran_SCV);
		CHECK(allunits.getMineralMinerCount() == 2);
		allunits.spawn(UnitName::Protoss_Probe);
		CHECK(allunits.getMineralMinerCount() == 3);
		allunits.spawn(UnitName::Zerg_Drone);
		CHECK(allunits.getMineralMinerCount() == 4);
	}

}
