#include "catch.hpp"
#include "buildhandler.h"

TEST_CASE("buildhandler") {
	BuildHandler buildhandler;
	const int MINE_RATE_T = 176;
	const int MINE_RATE_Z = 172;
	const int MINE_RATE_P = 169;
	const int TRAVEL_TIME = 64;

	SECTION("check that prerequisites work") {
		CHECK(buildhandler.canBuild(UnitName::Terran_SCV)==false);
		CHECK(buildhandler.canBuild(UnitName::Terran_Command_Center)==false);
		buildhandler.spawn(UnitName::Terran_SCV);
		buildhandler.update();
		CHECK(buildhandler.canBuild(UnitName::Terran_Command_Center)==true);
		buildhandler.spawn(UnitName::Terran_Command_Center);
		buildhandler.update();
		CHECK(buildhandler.canBuild(UnitName::Terran_SCV)==true);
		buildhandler.clear();
		CHECK(buildhandler.canBuild(UnitName::Terran_SCV)==false);
		CHECK(buildhandler.canBuild(UnitName::Terran_Command_Center)==false);
	}
	SECTION("check that workers begin mining") {
		CHECK(buildhandler.getMineralMinerCount() == 0);
		buildhandler.spawn(UnitName::Terran_SCV);
		buildhandler.update();
		CHECK(buildhandler.getMineralMinerCount() == 1);
		buildhandler.spawn(UnitName::Terran_SCV);
		buildhandler.update();
		CHECK(buildhandler.getMineralMinerCount() == 2);
		buildhandler.spawn(UnitName::Protoss_Probe);
		buildhandler.update();
		CHECK(buildhandler.getMineralMinerCount() == 3);
		buildhandler.spawn(UnitName::Zerg_Drone);
		buildhandler.update();
		CHECK(buildhandler.getMineralMinerCount() == 4);
	}
	SECTION("check that you can only build 1 unit at a time") {
		CHECK(buildhandler.canBuild(UnitName::Terran_SCV)==false);
		CHECK(buildhandler.canBuild(UnitName::Terran_Command_Center)==false);
		CHECK_THROWS(buildhandler.build(UnitName::Terran_SCV));
		CHECK_THROWS(buildhandler.build(UnitName::Terran_Command_Center));
		buildhandler.spawn(UnitName::Terran_Command_Center);
		buildhandler.update();
		CHECK(buildhandler.canBuild(UnitName::Terran_SCV)==true);
		buildhandler.build(UnitName::Terran_SCV);
		buildhandler.update();
		CHECK(buildhandler.canBuild(UnitName::Terran_SCV)==false);
		CHECK(buildhandler.canBuild(UnitName::Terran_Command_Center)==false);
		CHECK_THROWS(buildhandler.build(UnitName::Terran_SCV));
		CHECK_THROWS(buildhandler.build(UnitName::Terran_Command_Center));
	}
	SECTION("check mining update") {
		buildhandler.spawn(UnitName::Terran_SCV);
		REQUIRE(buildhandler.update().action==ActionName::Spawning);
		for(int i=0;i<MINE_RATE_T;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Gather_Minerals);
		REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		buildhandler.spawn(UnitName::Terran_SCV);
		REQUIRE(buildhandler.update().action==ActionName::Spawning);
		for(int i=0;i<MINE_RATE_T-1;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Gather_Minerals);
		REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Gather_Minerals);
	}
	SECTION("check building scv mining") {
		buildhandler.spawn(UnitName::Terran_Command_Center);
		REQUIRE(buildhandler.update().action==ActionName::Spawning);
		buildhandler.build(UnitName::Terran_SCV);
		for(int i=0;i<300;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Build);
		REQUIRE(buildhandler.update().action==ActionName::Being_Built);
		REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		buildhandler.build(UnitName::Terran_SCV);
		for(int i=0;i<MINE_RATE_T-1;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Gather_Minerals);
		for(int i=0;i<(301-MINE_RATE_T);i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Build);
		REQUIRE(buildhandler.update().action==ActionName::Being_Built);
		for(int i=0;i<(MINE_RATE_T*2-301);i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Gather_Minerals);
	}
	SECTION("check terran build building") {
		buildhandler.spawn(UnitName::Terran_SCV);
		REQUIRE(buildhandler.update().action==ActionName::Spawning);
		buildhandler.build(UnitName::Terran_Supply_Depot);
		for(int i=0;i<600;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Build);
		REQUIRE(buildhandler.update().action==ActionName::Being_Built);
		for(int i=0;i<TRAVEL_TIME;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Travelling);
	}
	SECTION("check protoss warp building") {
		buildhandler.spawn(UnitName::Protoss_Probe);
		REQUIRE(buildhandler.update().action==ActionName::Spawning);
		buildhandler.build(UnitName::Protoss_Pylon);
		for(int i=0;i<TRAVEL_TIME;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Travelling);
		for(int i=0;i<(520-TRAVEL_TIME);i++) {
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
			if((i+1)%MINE_RATE_P==0 && i>1) {
				REQUIRE(buildhandler.update().action==ActionName::Gather_Minerals);
			}
		}
		REQUIRE(buildhandler.update().action==ActionName::Being_Built);
	}
	SECTION("check zerg basic hatch activity") {
		buildhandler.spawn(UnitName::Zerg_Hatchery);
		REQUIRE(buildhandler.update().action==ActionName::Spawning);
		REQUIRE(buildhandler.update().action==ActionName::Spawning);
		REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		buildhandler.build(UnitName::Zerg_Drone);
		for(int i=0;i<318;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Being_Built);
		for(int i=0;i<24;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		//larva spawns
		REQUIRE(buildhandler.update().action==ActionName::Spawning);
		for(int i=0;i<MINE_RATE_Z-24;i++)
			REQUIRE(buildhandler.update().action==ActionName::Next_Frame);
		REQUIRE(buildhandler.update().action==ActionName::Gather_Minerals);
	}
}
