#include "buildhandler.h"

BuildHandler::BuildHandler() {
	unitListIterator = unitList.begin();
}

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
	useBuilder(unitStats);
}

void BuildHandler::spawn(UnitName unitName, ActionName actionName, int timer) {
	int i = unitListIterator - unitList.begin();
	unitList.push_back(ActiveUnit(unitName, actionName, timer));
	//in case the vector resizes
	unitListIterator = unitList.begin() + i;
}

void BuildHandler::useBuilder(UnitStatBlock unit) {
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

vector<ActiveUnit>::iterator BuildHandler::findAvailableUnit(UnitName unitName) {
	if(unitData.getUnitFromId(unitName).isWorker())
		return findAvailableMiner(unitName);

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

vector<ActiveUnit>::iterator BuildHandler::findAvailableMiner(UnitName unitName) {
	return findMinerByAction(&ActiveUnit::isAvailable, unitName);
}

vector<ActiveUnit>::iterator BuildHandler::findMineralMiner() {
	return findMinerByAction(&ActiveUnit::isMiningMinerals);
}

vector<ActiveUnit>::iterator BuildHandler::findGasMiner() {
	return findMinerByAction(&ActiveUnit::isMiningGas);
}

vector<ActiveUnit>::iterator BuildHandler::findMinerByAction(bool (ActiveUnit::*function)(), UnitName unitName) {
	vector<ActiveUnit>::iterator miningWorker;
	int miningTimer = -1;

	vector<ActiveUnit>::iterator unitIterator = unitList.begin();
	for(;unitIterator != unitList.end();unitIterator++) {
		ActiveUnit activeUnit = *unitIterator;
		if(unitName != UnitName::UNIT_NULL && activeUnit.unit != unitName)
			continue;
		if((activeUnit.*function)() && activeUnit.timer > miningTimer) {
			miningWorker = unitIterator;
			miningTimer = activeUnit.timer;
		}
	}
	if(miningTimer != -1)
		return miningWorker;
	throw UnitNotFound();
}

void BuildHandler::onGas() {
	int miningTime = expansionHandler.getGasRate();
	if(getGasMinerCount()>0)
		miningTime = (*findGasMiner()).timer + 37;
	(*findMineralMiner()).setActionGatherGas(miningTime);
}

void BuildHandler::offGas() {
	ActiveUnit gasMiner = (*findGasMiner());
	gasMiner.setActionGatherMinerals(getMineralRate(gasMiner.unit));
}

int BuildHandler::getMineralRate(UnitName unitname) const {
	return getMineralRate(unitData.getUnitFromId(unitname).race);
}

int BuildHandler::getMineralRate(char race) const {
	return expansionHandler.getMineralRate(getMineralMinerCount(), race);
}

int BuildHandler::getMineralMinerCount() const {
	return countUnitByAction(&ActiveUnit::isMiningMinerals);
}

int BuildHandler::getGasMinerCount() const {
	return countUnitByAction(&ActiveUnit::isMiningGas);
}

int BuildHandler::countUnitByAction(bool (ActiveUnit::*function)()) const {
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

//updates the states of all larva spawners and spawns larva
void BuildHandler::updateLarva() {
	int numLarvaSpawned = larvaHandler.updateLarva();
	for(int i=0; i<numLarvaSpawned; i++)
		spawn(UnitName::Zerg_Larva);
}

void BuildHandler::updateUnitAction(ActiveUnit &activeUnit) {
	UnitStatBlock unitStats = unitData.getUnitFromId(activeUnit.unit);
	if(unitStats.isWorker())
		updateWorkerAction(activeUnit);
	else {
		if(unitStats.isGas() && activeUnit.action==ActionName::Being_Built) {
			for(int i=0;i<3;i++)
				onGas();
		}
		//if(activeUnit.action==ActionName::Expand)
			//expansionHandler.expand();
		else if(activeUnit.unit==UnitName::Zerg_Hatchery) {
			if(activeUnit.action==ActionName::Spawning) {
				larvaHandler.addHatch();
				activeUnit.setActionIdle();
				spawn(UnitName::Zerg_Larva);
			}
		}
		else
			activeUnit.setActionIdle();
	}
}

void BuildHandler::updateWorkerAction(ActiveUnit &activeWorker) {
	if(activeWorker.isMiningGas())
		activeWorker.setActionGatherGas(expansionHandler.getGasRate());
	else if(activeWorker.isBuilding())
		activeWorker.setActionTravelling();
	else
		activeWorker.setActionGatherMinerals(getMineralRate(activeWorker.unit));
}

void BuildHandler::clear() {
	unitList.clear();
	unitListIterator = unitList.begin();
	expansionHandler.init();
	larvaHandler.clear();
}
