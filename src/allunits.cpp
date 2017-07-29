#include "allunits.h"

bool AllUnits::canBuild(UnitName unitname) const {
	UnitStatBlock unit = unitdata.getUnitFromId(unitname);

	if(hasIdleUnit(unit.buildsFrom) == false)
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
	int buildtime = unittoconstruct.buildTime;

	vector<ActiveUnit>::iterator builderunitit = findIdleUnit(buildername);
	ActiveUnit &builderunit = *builderunitit;

	if(unittoconstruct.isMorph()) {
		buildtime += 18;
		unitList.erase(builderunitit);
	}
	else {
		if(unittoconstruct.isWarp()) {
			buildtime += 70;
			builderunit.timer = 100;
		}
		else {
			builderunit.timer = buildtime;
		}
		builderunit.action = ActionName::Build;
	}
	unitList.push_back(ActiveUnit(unitname, ActionName::Being_Built, buildtime));
}

//finds an idle unit, including workers mining minerals
vector<ActiveUnit>::iterator AllUnits::findIdleUnit(UnitName unitname) {
	vector<ActiveUnit>::iterator idleunit = unitList.end();
	int timer = -1;
	vector<ActiveUnit>::iterator unititerator = unitList.begin();
	for(;unititerator != unitList.end(); ++unititerator) {
		ActiveUnit activeunit = *unititerator;
		if(activeunit.unit != unitname)
			continue;
		if(activeunit.action == ActionName::Idle)
			return unititerator;
		if(activeunit.isMiningMinerals() && activeunit.timer > timer) {
			idleunit = unititerator;
			timer = activeunit.timer;
		}
	}
	if(idleunit != unitList.end())
		return unititerator;
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
	for(int i=0;i<5;i++) {
	}
	return ActionName::Next_Frame;
}

void AllUnits::clear() {
	unitList.clear();
	expansion.init();
}
