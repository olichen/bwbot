#include "catch.hpp"
#include "unittree.h"
#include "unitname.h"

TEST_CASE("init") {
	UnitTree unittree;
	
	SECTION("random tests to make sure unitnames are correct") {
		REQUIRE(unittree.getUnit(UnitName::Terran_SCV).name == "Terran SCV");
		REQUIRE(unittree.getUnit(UnitName::Protoss_Probe).name == "Protoss Probe");
		REQUIRE(unittree.getUnit(UnitName::Zerg_Flyer_Carapace_3).name == "Zerg Flyer Carapace 3");
	}
	SECTION("check workers, expansions, and gas") {
		REQUIRE(unittree.getWorker('t').name == "Terran SCV");
		REQUIRE(unittree.getWorker('p').name == "Protoss Probe");
		REQUIRE(unittree.getWorker('z').name == "Zerg Drone");
		REQUIRE(unittree.getExpansion('t').name == "Terran Command Center");
		REQUIRE(unittree.getExpansion('p').name == "Protoss Nexus");
		REQUIRE(unittree.getExpansion('z').name == "Zerg Hatchery");
		REQUIRE(unittree.getGas('t').name == "Terran Refinery");
		REQUIRE(unittree.getGas('p').name == "Protoss Assimilator");
		REQUIRE(unittree.getGas('z').name == "Zerg Extractor");
	}
}
