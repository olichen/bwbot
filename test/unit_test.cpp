#include "catch.hpp"
#include "unittree.h"

TEST_CASE("init") {
	UnitTree unittree;
	for(int i=0; i<UnitName::NUMBER_OF_UNITS; i++)
	{
		REQUIRE(unittree.unitList[UnitName::Terran_SCV].name == "Terran SCV");
	}
}
