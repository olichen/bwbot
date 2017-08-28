#include "allunits.h"

bool AllUnits::canBuild(UnitName unitName) const {
	UnitStatBlock unit = unitData.getUnitFromId(unitName);

	if(hasAvailableUnit(unit.buildsFrom) == false)
		return false;
	if(hasUnit(unit.prerequisite[0]) == false)
		return false;
	if(isNonNullUnit(unit.prerequisite[1]))
		if(hasUnit(unit.prerequisite[1]) == false)
			return false;
	return true;
}

bool AllUnits::hasUnit(UnitName unitName) const {
	return hasUnit(unitName, &ActiveUnit::exists);
}

bool AllUnits::hasAvailableUnit(UnitName unitName) const {
	return hasUnit(unitName, &ActiveUnit::isAvailable);
}

bool AllUnits::hasUnit(UnitName unitName, bool (ActiveUnit::*function)()) const {
	for(ActiveUnit activeunit : unitList) {
		if(activeunit.unit == unitName && (activeunit.*function)())
			return true;
	}
	return false;
}

bool AllUnits::isNonNullUnit(UnitName unitName) const {
	return unitName != UnitName::UNIT_NULL;
}

void AllUnits::build(UnitName unitBeingBuiltName) {
	UnitStatBlock unitBeingBuilt = unitData.getUnitFromId(unitBeingBuiltName);
	UnitName unitBuilderName = unitBeingBuilt.buildsFrom;
	int buildTime = getBuildTime(unitBeingBuilt);

	vector<ActiveUnit>::iterator builderunitit = findAvailableUnit(unitBuilderName);
	ActiveUnit &builderunit = *findAvailableUnit(unitBuilderName);
	
	if(unitBeingBuilt.isMorph())
		unitList.erase(builderunitit);
	else if (unitBeingBuilt.isWarp()) {
		builderunit.action = ActionName::Travelling;
		builderunit.timer = 64;
	}
	else {
		builderunit.action = ActionName::Build;
		builderunit.timer = buildTime;
	}
	spawn(unitBeingBuiltName, ActionName::Being_Built, buildTime);
}

int AllUnits::getBuildTime(UnitStatBlock unit) {
	if(unit.isMorph())
		return unit.buildTime + 18;
	if(unit.isWarp())
		return unit.buildTime + 70;
	return unit.buildTime;
}

//finds an available unit, including workers mining minerals
vector<ActiveUnit>::iterator AllUnits::findAvailableUnit(UnitName unitName) {
	vector<ActiveUnit>::iterator miningWorker;
	int miningTimer = -1;

	vector<ActiveUnit>::iterator unitIterator = unitList.begin();
	for(;unitIterator != unitList.end();unitIterator++) {
		ActiveUnit activeUnit = *unitIterator;
		if(activeUnit.unit != unitName)
			continue;
		if(activeUnit.isIdle())
			return unitIterator;
		if(activeUnit.isMiningMinerals() && activeUnit.timer > miningTimer) {
			miningWorker = unitIterator;
			miningTimer = activeUnit.timer;
		}
	}
	if(miningTimer != -1)
		return miningWorker;
	throw UnitNotFound();
}

void AllUnits::spawn(UnitName unitName, ActionName actionName, int timer) {
	UnitStatBlock unit = unitData.getUnitFromId(unitName);
	if(unit.isWorker() && actionName==ActionName::Idle) {
		actionName = ActionName::Gather_Minerals;
		timer = getMineralRate(unit.race);
	}
	unitList.push_back(ActiveUnit(unitName, actionName, timer));
	unitListIterator = unitList.begin();
	if(unitName==UnitName::Zerg_Hatchery) {
		unitList.push_back(ActiveUnit(UnitName::Zerg_Larva_Spawner, actionName, timer, 1));
		unitList.push_back(ActiveUnit(UnitName::Zerg_Larva, actionName, timer));
	}
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

ActiveUnit AllUnits::update() {
	for(;unitListIterator != unitList.end();unitListIterator++) {
		ActiveUnit &activeUnit = *unitListIterator;
		if(activeUnit.timer == 0) {
			ActiveUnit activeUnitCopy = activeUnit;
			updateUnitAction(activeUnit);
			return activeUnitCopy;
		}
		activeUnit.timer--;
	}
	unitListIterator = unitList.begin();
	return ActiveUnit(UnitName::UNIT_NULL,ActionName::Next_Frame,0);
}

void AllUnits::updateUnitAction(ActiveUnit &activeUnit) {
	if(activeUnit.isMiningGas())
		activeUnit.timer = expansion.getGasRate();
	else if(activeUnit.isBuilding()) {
		activeUnit.action = ActionName::Travelling;
		activeUnit.timer = 64;
	}
	else if(unitData.getUnitFromId(activeUnit.unit).isWorker()) {
		activeUnit.action = ActionName::Gather_Minerals;
		activeUnit.timer = getMineralRate(unitData.getUnitFromId(activeUnit.unit).race);
	}
	else if(activeUnit.unit==UnitName::Zerg_Larva_Spawner) {
		//TODO:
	}
	else {
		activeUnit.action = ActionName::Idle;
		activeUnit.timer = -1;
	}
}

void AllUnits::clear() {
	unitList.clear();
	unitListIterator = unitList.begin();
	expansion.init();
}
