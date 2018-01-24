#include "catch.hpp"
#include "larvahandler.h"

TEST_CASE("larvahandler") {
	LarvaHandler larvahandler;
	const int LARVA_SPAWN_TIME = 342;

	SECTION("check that spawning larva works properly") {
		larvahandler.buildHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == true);
		larvahandler.buildHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == true);
		CHECK(larvahandler.updateLarva() == true);
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == true);
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == false);
	}
	SECTION("check that using larva works properly") {
		larvahandler.buildHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == true);
		larvahandler.buildHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == true);
		CHECK(larvahandler.updateLarva() == true);
		larvahandler.useLarva();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == true);
		CHECK(larvahandler.updateLarva() == true);
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == false);
		larvahandler.useLarva();
		CHECK(larvahandler.updateLarva() == false);
		larvahandler.useLarva();
		for(int i=0; i<LARVA_SPAWN_TIME-1; i++) {
			CHECK(larvahandler.updateLarva() == false);
		}
		CHECK(larvahandler.updateLarva() == true);
		CHECK(larvahandler.updateLarva() == false);
		CHECK(larvahandler.updateLarva() == true);
	}
}
