#include "catch.hpp"
#include "allunits.h"

TEST_CASE("allunits") {
	AllUnits allunits;
	const int MINE_RATE_T = 176;
	const int MINE_RATE_Z = 172;
	const int MINE_RATE_P = 169;
	const int TRAVEL_TIME = 64;

	SECTION("check that prerequisites work") {
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==false);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==false);
		allunits.spawn(UnitName::Terran_SCV);
		allunits.update();
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==true);
		allunits.spawn(UnitName::Terran_Command_Center);
		allunits.update();
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==true);
		allunits.clear();
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==false);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==false);
	}
	SECTION("check that workers begin mining") {
		CHECK(allunits.getMineralMinerCount() == 0);
		allunits.spawn(UnitName::Terran_SCV);
		allunits.update();
		CHECK(allunits.getMineralMinerCount() == 1);
		allunits.spawn(UnitName::Terran_SCV);
		allunits.update();
		CHECK(allunits.getMineralMinerCount() == 2);
		allunits.spawn(UnitName::Protoss_Probe);
		allunits.update();
		CHECK(allunits.getMineralMinerCount() == 3);
		allunits.spawn(UnitName::Zerg_Drone);
		allunits.update();
		CHECK(allunits.getMineralMinerCount() == 4);
	}
	SECTION("check that you can only build 1 unit at a time") {
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==false);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==false);
		CHECK_THROWS(allunits.build(UnitName::Terran_SCV));
		CHECK_THROWS(allunits.build(UnitName::Terran_Command_Center));
		allunits.spawn(UnitName::Terran_Command_Center);
		allunits.update();
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==true);
		allunits.build(UnitName::Terran_SCV);
		allunits.update();
		CHECK(allunits.canBuild(UnitName::Terran_SCV)==false);
		CHECK(allunits.canBuild(UnitName::Terran_Command_Center)==false);
		CHECK_THROWS(allunits.build(UnitName::Terran_SCV));
		CHECK_THROWS(allunits.build(UnitName::Terran_Command_Center));
	}
	SECTION("check mining update") {
		allunits.spawn(UnitName::Terran_SCV);
		REQUIRE(allunits.update().action==ActionName::Spawning);
		for(int i=0;i<MINE_RATE_T;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		REQUIRE(allunits.update().action==ActionName::Next_Frame);
		allunits.spawn(UnitName::Terran_SCV);
		REQUIRE(allunits.update().action==ActionName::Spawning);
		for(int i=0;i<MINE_RATE_T-1;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
	}
	SECTION("check building scv mining") {
		allunits.spawn(UnitName::Terran_Command_Center);
		REQUIRE(allunits.update().action==ActionName::Spawning);
		allunits.build(UnitName::Terran_SCV);
		for(int i=0;i<300;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Build);
		REQUIRE(allunits.update().action==ActionName::Being_Built);
		allunits.build(UnitName::Terran_SCV);
		for(int i=0;i<MINE_RATE_T;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		for(int i=0;i<(300-MINE_RATE_T);i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Build);
		REQUIRE(allunits.update().action==ActionName::Being_Built);
		for(int i=0;i<(MINE_RATE_T*2-300);i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
	}
	SECTION("check terran build building") {
		allunits.spawn(UnitName::Terran_SCV);
		REQUIRE(allunits.update().action==ActionName::Spawning);
		allunits.build(UnitName::Terran_Supply_Depot);
		for(int i=0;i<600;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Build);
		REQUIRE(allunits.update().action==ActionName::Being_Built);
		for(int i=0;i<TRAVEL_TIME;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Travelling);
	}
	SECTION("check protoss warp building") {
		allunits.spawn(UnitName::Protoss_Probe);
		REQUIRE(allunits.update().action==ActionName::Spawning);
		allunits.build(UnitName::Protoss_Pylon);
		for(int i=0;i<TRAVEL_TIME;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Travelling);
		for(int i=0;i<(520-TRAVEL_TIME);i++) {
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
			if((i+1)%MINE_RATE_P==0 && i>1) {
				REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
			}
		}
		REQUIRE(allunits.update().action==ActionName::Being_Built);
	}
	SECTION("check zerg building update") {
		allunits.spawn(UnitName::Zerg_Hatchery);
		REQUIRE(allunits.update().action==ActionName::Spawning);
		REQUIRE(allunits.update().action==ActionName::Spawning);
		REQUIRE(allunits.update().action==ActionName::Spawning);
		REQUIRE(allunits.update().action==ActionName::Next_Frame);
		allunits.build(UnitName::Zerg_Drone);
		for(int i=0;i<318;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Being_Built);
		for(int i=0;i<MINE_RATE_Z;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		//build creep
		//allunits.build(UnitName::Protoss_Pylon);
		//for(int i=0;i<TRAVEL_TIME;i++)
		//	REQUIRE(allunits.update().action==ActionName::Next_Frame);
		//REQUIRE(allunits.update().action==ActionName::Build);
		//for(int i=0;i<(520-TRAVEL_TIME);i++) {
		//	REQUIRE(allunits.update().action==ActionName::Next_Frame);
		//	if((i+1)%MINE_RATE_P==0 && i>1) {
		//		printf("here");
		//		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		//	}
		//}
		//REQUIRE(allunits.update().action==ActionName::Being_Built);
	}
}
