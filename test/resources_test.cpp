#include <catch.hpp>
#include "resources.h"

TEST_CASE("resources") {
	Resources resources;

	//init
	REQUIRE(resources.getMinerals() == 0);
	REQUIRE(resources.getGas() == 0);
	REQUIRE(resources.getSupply() == 0);
	REQUIRE(resources.getSupplyMax() == 0);
	REQUIRE(resources.getFrame() == 0);
	REQUIRE(resources.getMineralPatches() == 9);
	REQUIRE(resources.getGasGeysers() == 1);
	REQUIRE(resources.getRace() == 't');

	//minerals
	resources.addMinerals();
	REQUIRE(resources.getMinerals() == 8);
	resources.addMinerals(10);
	REQUIRE(resources.getMinerals() == 18);
	resources.useMinerals(7);
	REQUIRE(resources.getMinerals() == 11);

	//gas
	resources.addGas();
	REQUIRE(resources.getGas() == 8);
	resources.addGas(10);
	REQUIRE(resources.getGas() == 18);
	resources.useGas(7);
	REQUIRE(resources.getGas() == 11);

	//supply
	resources.addSupplyMax();
	REQUIRE(resources.getSupplyMax() == 8);
	REQUIRE(resources.getAvailableSupply() == 8);
	resources.useSupply(3);
	REQUIRE(resources.getSupply() == 3);
	REQUIRE(resources.getAvailableSupply() == 5);

	//frame
	resources.nextFrame();
	REQUIRE(resources.getFrame() == 1);
	resources.nextFrame(11);
	REQUIRE(resources.getFrame() == 12);

	//race
	resources.setRace('p');
	REQUIRE(resources.getRace() == 'p');

	//reset
	resources.clear();
	REQUIRE(resources.getMinerals() == 0);
	REQUIRE(resources.getGas() == 0);
	REQUIRE(resources.getSupply() == 0);
	REQUIRE(resources.getSupplyMax() == 0);
	REQUIRE(resources.getFrame() == 0);
	REQUIRE(resources.getMineralPatches() == 9);
	REQUIRE(resources.getGasGeysers() == 1);
	REQUIRE(resources.getRace() == 'p');
}
