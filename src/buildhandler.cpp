#include "buildhandler.h"

bool BuildHandler::canBuild(UnitName unitName) const {
	UnitStatBlock unit = unitData.getUnitFromId(unitName);

	if(hasAvailableUnit(unit.buildsFrom) == false)
		return false;
	if(hasUnit(unit.prerequisite[0]) == false)
		return false;
	if(unit.prerequisite[1] != UnitName::UNIT_NULL)
		if(hasUnit(unit.prerequisite[1]) == false)
			return false;
	return true;
}

bool BuildHandler::hasUnit(UnitName unitName) const {
	return hasUnit(unitName, &ActiveUnit::exists);
}

bool BuildHandler::hasAvailableUnit(UnitName unitName) const {
	return hasUnit(unitName, &ActiveUnit::isAvailable);
}

bool BuildHandler::hasUnit(UnitName unitName, bool (ActiveUnit::*function)()) const {
	for(ActiveUnit activeunit : unitList) {
		if(activeunit.unit == unitName && (activeunit.*function)())
			return true;
	}
	return false;
}

void BuildHandler::build(UnitName unitName) {
	UnitStatBlock unitStats = unitData.getUnitFromId(unitName);
	spawn(unitName, ActionName::Being_Built, unitStats.getBuildTime());
	findAndUseBuilder(unitStats);
}

void BuildHandler::findAndUseBuilder(UnitStatBlock unit) {
	ActiveUnit &builderunit = *findAvailableUnit(unit.buildsFrom);
	if(unit.isMorph())
		removeMorphingUnit(unit.buildsFrom);
	else if (unit.isWarp())
		builderunit.setActionTravelling();
	else
		builderunit.setActionBuild(unit.getBuildTime());
}

void BuildHandler::removeMorphingUnit(UnitName unitname) {
	unitList.erase(findAvailableUnit(unitname));
	if(unitname == UnitName::Zerg_Larva)
		larvaHandler.useLarva();
}

//finds an available unit, including workers mining minerals
vector<ActiveUnit>::iterator BuildHandler::findAvailableUnit(UnitName unitName) {
	if(unitData.getUnitFromId(unitName).isWorker())
		return findMiner(unitName);

	return findIdleUnit(unitName);
}

vector<ActiveUnit>::iterator BuildHandler::findIdleUnit(UnitName unitName) {
	vector<ActiveUnit>::iterator unitIterator = unitList.begin();
	for(;unitIterator != unitList.end();unitIterator++) {
		ActiveUnit activeUnit = *unitIterator;
		if(activeUnit.unit == unitName && activeUnit.isIdle())
			return unitIterator;
	}
	throw UnitNotFound();
}

vector<ActiveUnit>::iterator BuildHandler::findMiner(UnitName unitName) {
	vector<ActiveUnit>::iterator miningWorker;
	int miningTimer = -1;

	vector<ActiveUnit>::iterator unitIterator = unitList.begin();
	for(;unitIterator != unitList.end();unitIterator++) {
		ActiveUnit activeUnit = *unitIterator;
		if(activeUnit.unit != unitName)
			continue;
		if(activeUnit.isMiningMinerals() && activeUnit.timer > miningTimer) {
			miningWorker = unitIterator;
			miningTimer = activeUnit.timer;
		}
	}
	if(miningTimer != -1)
		return miningWorker;
	throw UnitNotFound();
}

vector<ActiveUnit>::iterator BuildHandler::findMineralMiner() {
	return findUnitByAction(&ActiveUnit::isMiningMinerals);
}

vector<ActiveUnit>::iterator BuildHandler::findGasMiner() {
	return findUnitByAction(&ActiveUnit::isMiningGas);
}

vector<ActiveUnit>::iterator BuildHandler::findUnitByAction(bool (ActiveUnit::*function)()) {
	vector<ActiveUnit>::iterator miningWorker;
	int miningTimer = -1;

	vector<ActiveUnit>::iterator unitIterator = unitList.begin();
	for(;unitIterator != unitList.end();unitIterator++) {
		ActiveUnit activeUnit = *unitIterator;
		if((activeUnit.*function)() && activeUnit.timer > miningTimer) {
			miningWorker = unitIterator;
			miningTimer = activeUnit.timer;
		}
	}
	if(miningTimer != -1)
		return miningWorker;
	throw UnitNotFound();
}

void BuildHandler::spawn(UnitName unitName, ActionName actionName, int timer) {
	unitList.push_back(ActiveUnit(unitName, actionName, timer));
	if(unitName==UnitName::Zerg_Hatchery) {
		//TODO: three larva for spawned
		larvaHandler.addHatch();
		unitList.push_back(ActiveUnit(UnitName::Zerg_Larva, actionName, timer));
	}
	unitListIterator = unitList.begin();
}

int BuildHandler::getMineralRate(UnitName unitname) const {
	return getMineralRate(unitData.getUnitFromId(unitname).race);
}

int BuildHandler::getMineralRate(char race) const {
	return expansion.getMineralRate(getMineralMinerCount(), race);
}

int BuildHandler::getMineralMinerCount() const {
	return countUnit(&ActiveUnit::isMiningMinerals);
}

int BuildHandler::getGasMinerCount() const {
	return countUnit(&ActiveUnit::isMiningGas);
}

int BuildHandler::countUnit(bool (ActiveUnit::*function)()) const {
	int count = 0;
	for(ActiveUnit activeunit : unitList) {
		if((activeunit.*function)())
			count++;
	}
	return count;
}

//iterates through units and returns an action if it is completed
//updates larva and returns next frame if all units have been iterated through
ActiveUnit BuildHandler::update() {
	for(;unitListIterator != unitList.end();unitListIterator++) {
		ActiveUnit &activeUnit = *unitListIterator;
		if(activeUnit.timer == 0) {
			ActiveUnit activeUnitCopy = activeUnit;
			updateUnitAction(activeUnit);
			return activeUnitCopy;
		}
		activeUnit.timer--;
	}
	updateLarva();
	unitListIterator = unitList.begin();
	return ActiveUnit(UnitName::UNIT_NULL,ActionName::Next_Frame,0);
}

void BuildHandler::onGas() {
	(*findMineralMiner()).setActionGatherGas(expansion.getGasRate());
}

void BuildHandler::offGas() {
	ActiveUnit gasMiner = (*findGasMiner());
	gasMiner.setActionGatherMinerals(getMineralRate(gasMiner.unit));
}

//updates the states of all larva spawners and spawns larva
void BuildHandler::updateLarva() {
	for(int i=0; i<larvaHandler.updateLarva(); i++)
		spawn(UnitName::Zerg_Larva);
}

void BuildHandler::updateUnitAction(ActiveUnit &activeUnit) {
	UnitStatBlock unitStats = unitData.getUnitFromId(activeUnit.unit);
	if(unitStats.isWorker())
		updateWorkerAction(activeUnit);
	else {
		if(unitStats.isGas() && activeUnit.action==ActionName::Being_Built) {
			for(int i=0;i<3;i++)
				(*findMineralMiner()).setActionGatherGas(((3+i)*expansion.getGasRate())/3);
		}
		if(activeUnit.action==ActionName::Expand)
			expansion.expand();
		activeUnit.setActionIdle();
	}
}

void BuildHandler::updateWorkerAction(ActiveUnit &activeWorker) {
	if(activeWorker.isMiningGas())
		activeWorker.setActionGatherGas(expansion.getGasRate());
	else if(activeWorker.isBuilding())
		activeWorker.setActionTravelling();
	else
		activeWorker.setActionGatherMinerals(getMineralRate(activeWorker.unit));
}

void BuildHandler::clear() {
	unitList.clear();
	unitListIterator = unitList.begin();
	expansion.init();
	larvaHandler.clear();
}
