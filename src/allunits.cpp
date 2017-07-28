#include "allunits.h"

bool AllUnits::canBuild(UnitName unit) {
	return unit == 1;
}

bool AllUnits::hasUnit(UnitName unit) {
	for(ActiveUnit activeunit : unitList) {
		if(activeunit.unit == unit)
			return true;
	}
	return false;
}

void AllUnits::build(UnitName unit) {
	if(unit == 1) {}
}

int AllUnits::update() {
	return UnitName::UNIT_NULL;
}

void AllUnits::clear() {
	unitList.clear();
}

//vector<ActiveUnit> unitList;
