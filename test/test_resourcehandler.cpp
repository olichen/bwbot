#include "catch.hpp"
#include "resourcehandler.h"
#include "activeunit.h"

TEST_CASE("resourcehandler") {
	ResourceHandler resourcehandler;

	SECTION("check that canBuild correctly checks supply") {
		CHECK(resourcehandler.canBuild(UnitName::Terran_SCV)==false);
		ActiveUnit spawnCC(UnitName::Terran_Command_Center, ActionName::Spawning, 0);
		resourcehandler.update(spawnCC);
		CHECK(resourcehandler.canBuild(UnitName::Terran_SCV)==true);
		ActiveUnit startSCV(UnitName::Terran_SCV, ActionName::Start_Build, 0);
		resourcehandler.update(startSCV);
		CHECK(resourcehandler.canBuild(UnitName::Terran_SCV)==false);
		ActiveUnit gatherMinerals(UnitName::Terran_SCV, ActionName::Gather_Minerals, 0);
		for(int i=0;i<8;i++) {
			resourcehandler.update(gatherMinerals);
		}
		CHECK(resourcehandler.canBuild(UnitName::Terran_SCV)==true);
		ActiveUnit spawnSCV(UnitName::Terran_SCV, ActionName::Spawning, 0);
		for(int i=0;i<9;i++) {
			resourcehandler.update(spawnSCV);
		}
		CHECK(resourcehandler.canBuild(UnitName::Terran_SCV)==false);
	}
}
