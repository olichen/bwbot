#include "catch.hpp"
#include "larvahandler.h"

TEST_CASE("larvahandler") {
	LarvaHandler larvahandler;
	const int LARVA_SPAWN_TIME = 342;

	SECTION("check that spawning larva works properly") {
		larvahandler.buildHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 1);
		larvahandler.buildHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 2);
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 1);
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 0);
	}
	SECTION("check that using larva works properly") {
		larvahandler.buildHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 1);
		larvahandler.buildHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 2);
		larvahandler.useLarva();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 2);
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 0);
		larvahandler.useLarva();
		CHECK(larvahandler.updateLarva() == 0);
		larvahandler.useLarva();
		for(int i=0; i<LARVA_SPAWN_TIME-1; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 1);
		CHECK(larvahandler.updateLarva() == 1);
	}
}
