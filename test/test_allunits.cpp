#include "catch.hpp"
#include "allunits.h"

TEST_CASE("allunits") {
	AllUnits allunits;
	const int MINE_RATE_T = 176;
	const int MINE_RATE_Z = 172;
	const int MINE_RATE_P = 169;
	const int TRAVEL_TIME_PROBE = 64;

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
		for(int i=0;i<MINE_RATE_T;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		REQUIRE(allunits.update().action==ActionName::Next_Frame);
		allunits.spawn(UnitName::Terran_SCV);
		for(int i=0;i<MINE_RATE_T-1;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
	}
	SECTION("check terran building update") {
		allunits.spawn(UnitName::Terran_Command_Center);
		REQUIRE(allunits.update().action==ActionName::Next_Frame);
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
	SECTION("check protoss building update") {
		allunits.spawn(UnitName::Protoss_Nexus);
		REQUIRE(allunits.update().action==ActionName::Next_Frame);
		allunits.build(UnitName::Protoss_Probe);
		for(int i=0;i<300;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Build);
		REQUIRE(allunits.update().action==ActionName::Being_Built);
		for(int i=0;i<MINE_RATE_P;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		allunits.build(UnitName::Protoss_Pylon);
		for(int i=0;i<TRAVEL_TIME_PROBE;i++)
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
		REQUIRE(allunits.update().action==ActionName::Build);
		for(int i=0;i<(520-TRAVEL_TIME_PROBE);i++) {
			REQUIRE(allunits.update().action==ActionName::Next_Frame);
			if((i+1)%MINE_RATE_P==0 && i>1) {
				printf("here");
				REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
			}
		}
		REQUIRE(allunits.update().action==ActionName::Being_Built);
	}
	SECTION("check zerg building update") {
		//allunits.spawn(UnitName::Zerg_Larva);
		//REQUIRE(allunits.update().action==ActionName::Next_Frame);
		//allunits.build(UnitName::Zerg_Larva);
		//for(int i=0;i<300;i++)
		//	REQUIRE(allunits.update().action==ActionName::Next_Frame);
		//REQUIRE(allunits.update().action==ActionName::Build);
		//REQUIRE(allunits.update().action==ActionName::Being_Built);
		//for(int i=0;i<MINE_RATE_P;i++)
		//	REQUIRE(allunits.update().action==ActionName::Next_Frame);
		//REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		//allunits.build(UnitName::Protoss_Pylon);
		//for(int i=0;i<TRAVEL_TIME_PROBE;i++)
		//	REQUIRE(allunits.update().action==ActionName::Next_Frame);
		//REQUIRE(allunits.update().action==ActionName::Build);
		//for(int i=0;i<(520-TRAVEL_TIME_PROBE);i++) {
		//	REQUIRE(allunits.update().action==ActionName::Next_Frame);
		//	if((i+1)%MINE_RATE_P==0 && i>1) {
		//		printf("here");
		//		REQUIRE(allunits.update().action==ActionName::Gather_Minerals);
		//	}
		//}
		//REQUIRE(allunits.update().action==ActionName::Being_Built);
	}
}
