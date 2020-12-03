#include "catch.hpp"
#include "unitdata.h"

TEST_CASE("unitdata") {
	UnitData unitdata;
	
	SECTION("make sure the correct unit ids are pulled from names") {
		CHECK(unitdata.getUnitIdFromName("Terran SCV") == UnitName::Terran_SCV);
		CHECK(unitdata.getUnitIdFromName("Protoss Probe") == UnitName::Protoss_Probe);
		CHECK(unitdata.getUnitIdFromName("Zerg Drone") == UnitName::Zerg_Drone);
		CHECK(unitdata.getUnitIdFromName("Zerg Flyer Carapace 3") == UnitName::Zerg_Flyer_Carapace_3);
		CHECK_THROWS(unitdata.getUnitIdFromName("garbage name"));
	}
	SECTION("make sure the correct units are pulled from ids") {
		CHECK(unitdata.getUnitFromId(UnitName::Terran_SCV).name == "Terran SCV");
		CHECK(unitdata.getUnitFromId(UnitName::Protoss_Probe).name == "Protoss Probe");
		CHECK(unitdata.getUnitFromId(UnitName::Zerg_Drone).name == "Zerg Drone");
		CHECK(unitdata.getUnitFromId(UnitName::Zerg_Flyer_Carapace_3).name == "Zerg Flyer Carapace 3");
		CHECK_THROWS(unitdata.getUnitIdFromName("garbage name"));
		CHECK_THROWS(unitdata.getUnitFromId(UnitName::UNIT_TOTAL));
	}
	SECTION("check workers, expansions, and gas") {
		CHECK(unitdata.getRaceWorker('t').name == "Terran SCV");
		CHECK(unitdata.getRaceWorker('p').name == "Protoss Probe");
		CHECK(unitdata.getRaceWorker('z').name == "Zerg Drone");
		CHECK(unitdata.getRaceExpansion('t').name == "Terran Command Center");
		CHECK(unitdata.getRaceExpansion('p').name == "Protoss Nexus");
		CHECK(unitdata.getRaceExpansion('z').name == "Zerg Hatchery");
		CHECK(unitdata.getRaceGas('t').name == "Terran Refinery");
		CHECK(unitdata.getRaceGas('p').name == "Protoss Assimilator");
		CHECK(unitdata.getRaceGas('z').name == "Zerg Extractor");
		for(char c='A'; c<'z'; c++)
		{
			if(c=='t'||c=='p'||c=='z')
				continue;
			CHECK_THROWS(unitdata.getRaceWorker(c));
			CHECK_THROWS(unitdata.getRaceExpansion(c));
			CHECK_THROWS(unitdata.getRaceGas(c));
		}
	}
	SECTION("make sure zerg unit/buildings morph") {
		for(int i=0; i<UnitName::UNIT_TOTAL; i++)
		{
			UnitStatBlock unit = unitdata.getUnitFromId((UnitName)i);
			if(unit.name == "Zerg Larva" || unit.name == "Zerg Larva Spawner")
				continue;
			INFO(unit.name);
			if(unit.race=='z' && (unit.type=='b' || unit.type=='u'))
				CHECK(unit.isMorph()==true);
			else
				CHECK(unit.isMorph()==false);
		}
	}
}
