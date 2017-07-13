#include <catch.hpp>
#include "resources.h"

TEST_CASE("resources initialize properly", "[init]") {
	Resources resources;

	SECTION("test a") {
		CHECK(resources.getMinerals() == 0);

	}
//#: mMinerals(0), mGas(0), mSupply(0), mSupplyMax(0), mFrame(0), mMineralPatches(mineralPatches), mGasGeysers(gasGeysers), mRace(race)
}

