#include "catch.hpp"
#include "larvahandler.h"

TEST_CASE("larvahandler") {
	LarvaHandler larvahandler;
	const int LARVA_SPAWN_TIME = 342;

	SECTION("check that spawning larva works properly") {
		larvahandler.addHatch();
		for(int i=0; i<LARVA_SPAWN_TIME; i++) {
			CHECK(larvahandler.updateLarva() == 0);
		}
		CHECK(larvahandler.updateLarva() == 1);
		larvahandler.addHatch();
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
}
