#include "catch.hpp"
#include "units.h"

TEST_CASE("init") {
	Units units;
	
	SECTION("random tests to make sure unitnames are correct") {
		CHECK(units.getUnitFromId(UnitName::Terran_SCV).name == "Terran SCV");
		CHECK(units.getUnitFromId(UnitName::Protoss_Probe).name == "Protoss Probe");
		CHECK(units.getUnitFromId(UnitName::Zerg_Flyer_Carapace_3).name == "Zerg Flyer Carapace 3");
	}
	SECTION("check workers, expansions, and gas") {
		CHECK(units.getRaceWorker('t').name == "Terran SCV");
		CHECK(units.getRaceWorker('p').name == "Protoss Probe");
		CHECK(units.getRaceWorker('z').name == "Zerg Drone");
		CHECK(units.getRaceExpansion('t').name == "Terran Command Center");
		CHECK(units.getRaceExpansion('p').name == "Protoss Nexus");
		CHECK(units.getRaceExpansion('z').name == "Zerg Hatchery");
		CHECK(units.getRaceGas('t').name == "Terran Refinery");
		CHECK(units.getRaceGas('p').name == "Protoss Assimilator");
		CHECK(units.getRaceGas('z').name == "Zerg Extractor");
	}
	SECTION("make sure zerg unit/buildings morph") {
		for(int i=0; i<UnitName::UNIT_TOTAL; i++)
		{
			UnitStatBlock unit = units.getUnitFromId(i);
			if(unit.name == "Zerg Larva" || unit.name == "Zerg Larva Spawner")
				continue;
			INFO(unit.name);
			if(unit.race=='z' && (unit.type=='b' || unit.type=='u'))
				CHECK(unit.isMorph()==true);
			else
				CHECK(unit.isMorph()==false);
		}
	}
	SECTION("exceptions for out of range") {
		CHECK_THROWS(units.getUnitFromId(UnitName::UNIT_TOTAL));
	}
	SECTION("exceptions for wrong race") {
		for(char c='A'; c<'z'; c++)
		{
			if(c=='t'||c=='p'||c=='z')
				continue;
			CHECK_THROWS(units.getRaceWorker(c));
			CHECK_THROWS(units.getRaceExpansion(c));
			CHECK_THROWS(units.getRaceGas(c));
		}
	}
}
