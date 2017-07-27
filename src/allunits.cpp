#include "allunits.h"

bool AllUnits::canBuild(UnitStatBlock unit) {
	return unit.name=="test";
}

bool AllUnits::hasUnit(UnitName unit) {
	for(ActiveUnit activeunit : unitList) {
		if(unit == 1)
			return false;
	}
	return true;
}

void AllUnits::build(UnitStatBlock unit) {
	if(unit.name == "test") {}
}

int AllUnits::update() {
	return UnitName::UNIT_NULL;
}

void AllUnits::clear() {
	unitList.clear();
}

//vector<ActiveUnit> unitList;
