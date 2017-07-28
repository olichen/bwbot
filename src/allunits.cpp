#include "allunits.h"

bool AllUnits::canBuild(UnitName unitname) const {
	UnitStatBlock unit = unitdata.getUnitFromId(unitname);

	if(hasUnit(unit.buildsFrom) == false)
		return false;
	if(hasUnit(unit.prerequisite[0]) == false)
		return false;
	if(isNonNullUnit(unit.prerequisite[1]))
		if(hasUnit(unit.prerequisite[1]) == false)
			return false;
	return true;
}

bool AllUnits::hasUnit(UnitName unitname) const {
	return hasUnit(unitname, &ActiveUnit::exists);
}

bool AllUnits::hasIdleUnit(UnitName unitname) const {
	return hasUnit(unitname, &ActiveUnit::isIdle);
}

bool AllUnits::hasUnit(UnitName unitname, bool (ActiveUnit::*function)()) const {
	for(ActiveUnit activeunit : unitList) {
		if(activeunit.unit == unitname && (activeunit.*function)())
			return true;
	}
	return false;
}

bool AllUnits::isNonNullUnit(UnitName unitname) const {
	return unitname != UnitName::UNIT_NULL;
}

void AllUnits::build(UnitName unitname) {
	UnitStatBlock unittoconstruct = unitdata.getUnitFromId(unitname);
	UnitName buildername = unittoconstruct.buildsFrom;
	int builderunit = findIdleUnit(buildername);
	unitList[builderunit].action = ActionName::Build;
	unitList[builderunit].timer = unittoconstruct.buildTime;
}

//finds an idle unit, including workers mining minerals
int AllUnits::findIdleUnit(UnitName unitname) const {
	int idleunit = -1;
	int timer = -1;
	for(unsigned int i=0; i<unitList.size(); i++) {
		ActiveUnit activeunit = unitList[i];
		if(activeunit.unit != unitname)
			continue;
		if(activeunit.action == ActionName::Idle)
			return i;
		if(activeunit.isMiningMinerals() && activeunit.timer > timer) {
			idleunit = i;
			timer = activeunit.timer;
		}
	}
	if(idleunit != -1)
		return idleunit;
	throw UnitNotFound();
}

void AllUnits::spawn(UnitName unitname, ActionName action, int timer) {
	UnitStatBlock unit = unitdata.getUnitFromId(unitname);
	if(unit.isWorker()) {
		action = ActionName::Gather_Minerals;
		timer = getMineralRate(unit.race);
	}
	unitList.push_back(ActiveUnit(unitname, action, timer));
}

int AllUnits::getMineralRate(char race) const {
	return expansion.getMineralRate(getMineralMinerCount(), race);
}

int AllUnits::getGasRate() const {
	return expansion.getGasRate();
}

int AllUnits::getMineralMinerCount() const {
	return countUnit(&ActiveUnit::isMiningMinerals);
}

int AllUnits::getGasMinerCount() const {
	return countUnit(&ActiveUnit::isMiningGas);
}

int AllUnits::countUnit(bool (ActiveUnit::*function)()) const {
	int count = 0;
	for(ActiveUnit activeunit : unitList) {
		if((activeunit.*function)())
			count++;
	}
	return count;
}

ActionName AllUnits::update() {
	return ActionName::Next_Frame;
}

void AllUnits::clear() {
	unitList.clear();
	expansion.init();
}
