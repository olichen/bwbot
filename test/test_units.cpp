#include "catch.hpp"
#include "units.h"

TEST_CASE("init") {
	Units units;
	
	SECTION("random tests to make sure unitnames are correct") {
		REQUIRE(units.getUnitFromId(UnitName::Terran_SCV).name == "Terran SCV");
		REQUIRE(units.getUnitFromId(UnitName::Protoss_Probe).name == "Protoss Probe");
		REQUIRE(units.getUnitFromId(UnitName::Zerg_Flyer_Carapace_3).name == "Zerg Flyer Carapace 3");
	}
	SECTION("check workers, expansions, and gas") {
		REQUIRE(units.getRaceWorker('t').name == "Terran SCV");
		REQUIRE(units.getRaceWorker('p').name == "Protoss Probe");
		REQUIRE(units.getRaceWorker('z').name == "Zerg Drone");
		REQUIRE(units.getRaceExpansion('t').name == "Terran Command Center");
		REQUIRE(units.getRaceExpansion('p').name == "Protoss Nexus");
		REQUIRE(units.getRaceExpansion('z').name == "Zerg Hatchery");
		REQUIRE(units.getRaceGas('t').name == "Terran Refinery");
		REQUIRE(units.getRaceGas('p').name == "Protoss Assimilator");
		REQUIRE(units.getRaceGas('z').name == "Zerg Extractor");
	}
	SECTION("make sure zerg unit/buildings morph") {
		for(int i=0; i<UnitName::UNIT_TOTAL; i++)
		{
			UnitStats unit = units.getUnitFromId(i);
			if(unit.name == "Zerg Larva" || unit.name == "Zerg Larva Spawner")
				continue;
			INFO(unit.name);
			if(unit.race=='z' && (unit.type=='b' || unit.type=='u'))
				REQUIRE(unit.isMorph()==true);
			else
				REQUIRE(unit.isMorph()==false);
		}
	}
	SECTION("exceptions for out of range") {
		REQUIRE_THROWS(units.getUnitFromId(UnitName::UNIT_TOTAL));
	}
	SECTION("exceptions for wrong race") {
		for(char c='A'; c<'z'; c++)
		{
			if(c=='t'||c=='p'||c=='z')
				continue;
			REQUIRE_THROWS(units.getRaceWorker(c));
			REQUIRE_THROWS(units.getRaceExpansion(c));
			REQUIRE_THROWS(units.getRaceGas(c));
		}
	}
}
