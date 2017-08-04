#include "catch.hpp"
#include "allunits.h"

TEST_CASE("allunits") {
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
	SECTION("check building units") {
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==false);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==false);
		CHECK_THROWS(allunits.build(UnitName::Terran_SCV));
		CHECK_THROWS(allunits.build(UnitName::Terran_Command_Center));
		allunits.spawn(UnitName::Terran_Command_Center);
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==true);
		allunits.build(UnitName::Terran_SCV);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==false);
		CHECK_THROWS(allunits.build(UnitName::Terran_Command_Center));
	}
	SECTION("check morphing units") {
		CHECK(allunits.canBuild(UnitName::Zerg_Drone)==false);
		CHECK(allunits.canBuild(UnitName::Zerg_Hatchery)==false);
		CHECK_THROWS(allunits.build(UnitName::Zerg_Drone));
		CHECK_THROWS(allunits.build(UnitName::Zerg_Hatchery));
		allunits.spawn(UnitName::Zerg_Drone);
		CHECK(allunits.canBuild(UnitName::Zerg_Hatchery)==true);
		allunits.build(UnitName::Zerg_Hatchery);
		CHECK(allunits.canBuild(UnitName::Zerg_Hatchery)==false);
		CHECK_THROWS(allunits.build(UnitName::Zerg_Hatchery));
	}
	SECTION("check mining update") {
		allunits.spawn(UnitName::Terran_SCV);
		for(int i=0;i<176;i++)
			REQUIRE(allunits.update()==ActionName::Next_Frame);
		REQUIRE(allunits.update()==ActionName::Gather_Minerals);
		REQUIRE(allunits.update()==ActionName::Next_Frame);
		allunits.spawn(UnitName::Terran_SCV);
		for(int i=0;i<175;i++)
			REQUIRE(allunits.update()==ActionName::Next_Frame);
		REQUIRE(allunits.update()==ActionName::Gather_Minerals);
		REQUIRE(allunits.update()==ActionName::Next_Frame);
		REQUIRE(allunits.update()==ActionName::Gather_Minerals);
	}
	SECTION("check building update") {
		allunits.spawn(UnitName::Terran_Command_Center);
		REQUIRE(allunits.update()==ActionName::Next_Frame);
		allunits.build(UnitName::Terran_SCV);
		for(int i=0;i<300;i++)
			REQUIRE(allunits.update()==ActionName::Next_Frame);
		REQUIRE(allunits.update()==ActionName::Build);
		REQUIRE(allunits.update()==ActionName::Being_Built);
		allunits.build(UnitName::Terran_SCV);
		for(int i=0;i<176;i++)
			REQUIRE(allunits.update()==ActionName::Next_Frame);
		REQUIRE(allunits.update()==ActionName::Gather_Minerals);
		for(int i=0;i<(300-176);i++)
			REQUIRE(allunits.update()==ActionName::Next_Frame);
		REQUIRE(allunits.update()==ActionName::Build);
		REQUIRE(allunits.update()==ActionName::Being_Built);
		for(int i=0;i<(176*2-300);i++)
			REQUIRE(allunits.update()==ActionName::Next_Frame);
		REQUIRE(allunits.update()==ActionName::Gather_Minerals);
	}
}
